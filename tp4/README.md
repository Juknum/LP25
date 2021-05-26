# Manipulation du système de fichiers (suite)

Dans ce TP, nous allons poursuivre la manipulation du système de fichiers avec la création de répertoires, et la suppression de répertoires et de fichiers, ainsi que l'écriture non séquentielle de fichiers.

Le contexte sera une base de données gérée par votre programme. La base de données sera constituée de plusieurs tables, chacune gérée par des fichiers portant le nom de la table gérée et une extension en fonction du rôle du fichier (structure, index, contenu). La base de données sera dans un répertoire portant son nom, et chaque ensemble de fichiers d'une table sera dans un répertoire du même nom.

Le programme qui gère la base de données prend en argument le nom de la base de données (il faut l'exécuter dans le répertoire contenant le répertoire où devra être créée la base de données).

## Partie 1 : vérification de l'existence de la BDD

À partir de l'argument fourni au programme (dont vous vérifierez l'existence), écrire les deux fonctions suivantes :

 - `int check_db_directory(char *name)` qui cherche si le répertoire de la base de données existe. Cette fonction renvoie 1 si le répertoire existe, 0 sinon.
 - `void create_db_directory(char *name)` qui crée le répertoire de la base de données (il faut que cette dernière n'existe pas encore)

## Partie 2 : création d'une table

```c
#define TEXT_LENGTH 150

typedef enum {
	TYPE_INTEGER,
	TYPE_FLOAT,
	TYPE_TEXT
} e_field_type;

typedef struct {
	char column_name[TEXT_LENGTH];
	e_field_type column_type;
} s_field;
```

En prenant en compte les définitions ci dessus, écrire les fonctions suivantes :

 - `int table_exists(char *name)` qui renvoie 1 si la table `name` existe déjà, 0 sinon
 - `void create_table(char *name, s_field fields[], int fields_count)` qui crée la table (donc le répertoire) ainsi que les fichiers qui s'y réfèrent (dans le répertoire de la table) :
	 - `name.idx`, fichier d'index, de type binaire, vide au départ
	 - `name.def`, fichier de définition de table, de type texte, qui contient sa définition (décrite ci dessous)
	 - `name.data`, fichier de contenu de la table, de type binaire, vide au départ

Le fichier de description de la table contient la liste des champs (un par ligne avec leur type, défini par l'énumération e_field_type). Ce fichier permet de trouver où sont accessibles les informations d'une table.

Une ligne définissant un champ est écrite de la manière suivante : `N nom` où `N` est le numéro de type de champ issu de l'énumération e_field_type, et `nom` est le nom du champ. Une table comporte au plus 10 champs.

Tester le code avec la table suivante :

```c
s_field fields[MAX_FIELDS] = {
	{.column_name="id", .column_type=TYPE_INTEGER},
    {.column_name="label", .column_type=TYPE_TEXT}
};
char table_name[TEXT_LENGTH] = "my_table";

if (!table_exists(table_name)) {
    create_table(table_name, fields, 2);
}
```

## Partie 3 : écriture dans une table

Pour cette partie, vous aurez besoin du type suivant :

```c
#define BUFFER_SIZE (MAX_FIELDS * TEXT_LENGTH)

typedef struct {
	s_field field_definition;
	union {
		double float_value;
		long long int_value;
		char text_value[TEXT_LENGTH];
	} field_value;
} s_field_record;
```

L'accès à la valeur se fera par un `switch` sur le type de donnée.

Une fois une table créée, il va être possible d'y ajouter des données. Pour celà, vous implémenterez les fonctions suivantes :

 - `void add_row_to_table(char *table_name, s_field_record row[], int fields_count)` Cette fonction ajoute la ligne définie par les `fields_count` champs dans le tableau de structures `row` à la table nommée `table_name`. Cette fonction utilise les fonctions définies ci dessous.
 - `int format_row(char *buffer, char *table_name, s_field_record row[], int fields_count)` Cette fonction prépare un buffer qui contiendra toute la ligne telle qu'elle sera enregistrée dans le fichier .data. Elle retourne le nombre d'octets à écrire.
 - `int write_row(char *buffer, char *table_name, int size)` Cette fonction écrit la ligne dans le fichier .data de la table et renvoie la position du début de la ligne. Le texte est stocké tel quel avec du "padding" (complété par des zéros) jusqu'à la taille de texte (TEXT_LENGTH). Les données numériques sont copiées en binaire (donc on `memcpy` leur valeur dans le buffer).
 - `void insert_index(int position, char *table_name)` Cette fonction insère l'index d'une ligne (tel que renvoyé par la fonction `write_row`) dans le fichier .idx de la table.

Concernant l'index, il est composé de deux entiers par entrée, avec autant d'entrées que de lignes insérées dans la table. Ces entiers sont stockés en binaire (c'est une copie de leur mémoire qui est écrite dans le fichier). Le premier entier est un identifiant unique (que vous incrémentez à chaque nouvelle écriture), le second est la position des données dans le fichier .data (renvoyée par `write_row`). La valeur de l'identifiant unique débute à `1`.

Testez le code sur les données suivantes :

```c
s_field_record field_records[MAX_FIELDS] = {
		{
			.field_definition =
			{
				.column_name="id",
				.column_type=TYPE_INTEGER
			},
			.field_value.int_value=1
		},
		{
			.field_definition =
			{
				.column_name="label",
				.column_type=TYPE_TEXT
			},
			.field_value.text_value="hello world!"
		},
};
add_row_to_table(table_name, field_records, 2);
```

## Partie 4 : lecture dans une table

Pour la lecture dans une table, vous devez utiliser la structure écrite dans le fichier .def, l'index dans le fichier .idx qui vous permettront ensuite d'accéder et de récupérer correctement les données de la table dans le fichier .data.

Pour cela, vous aurez besoin des fonctions suivantes :

 - `int get_table_definition(char *table_name, s_field fields[])` Cette fonction lit le fichier de définition de la table dont le nom est pointé par `table_name`, en place les définitions des champs dans le tableau `fields` et retourne le nombre de champs existant dans la base de données.
 - `int get_row_length(s_field fields[], int fields_count)` Cette fonction calcule la longueur d'un buffer de ligne (pour permettre la lecture des données dans le fichier .data) en fonction de la description des `fields_count` champs décrits dans le tableau `fields`
 - `void get_line_buffer(char *table_name, int offset, int row_length, char *buffer)` Cette fonction va copier dans le buffer pointé par `buffer` (de taille `BUFFER_SIZE`) la ligne de la table dont le nom est pointé par `table_name`, qui est située au `offset`-ième octet du fichier .data, et dont la longueur (obtenue par le calcul de la fonction `get_row_length`) est `row_length`.
 - `void convert_row(char *buffer, s_field fields[], s_field_record field_records[], int fields_count)` Cette fonction convertit le buffer obtenu par `get_line_buffer` en un tableau de `s_field_record` dont les `fields_count` champs sont décrits dans le tableau `fields` (qui a été obtenu par `get_table_definition`)
 - `void display_row(s_field_record field_records[], int fields_count)` Cette fonction affiche une ligne stockée dans le tableau `records` obtenu par la fonction `convert_row` et dont la taille est `fields_count`.

Le test de cette étape peut être réalisé comme suit (les variables non définies dans cet extrait de code, telle que `table_name`, sont issues des parties précédentes) :

```c
s_field read_fields[MAX_FIELDS];
s_field_record read_records[MAX_FIELDS];
char line_buffer[BUFFER_SIZE];
int fields_count, row_length;

fields_count = get_table_definition(table_name, read_fields);
row_length = get_row_length(read_fields, fields_count);
get_line_buffer(table_name, 0, row_length, line_buffer); // offset=0: first line
convert_row(line_buffer, read_fields, read_records, fields_count);
display_row(read_records, fields_count);
```

En vous inspirant de cet enchaînement d'appels, écrire la fonction `void display_all(char *table_name)` qui exploite les informations d'index pour lire les lignes une à une et les afficher. C'est notamment ce fichier qui dictera combien de lignes seront affichées et quelle sera la valeur de l'offset (au lieu de zéro comme l'exemple ci dessus).

## Partie 5 : modification d'une table

Pour modifier une table, il est nécessaire de lui passer en paramètre les nouvelles valeurs de la même manière que vous le feriez pour une insertion. Par ailleurs, il est également nécessaire de lui passer un identifiant de ligne qui sera celui de la ligne à modifier. Pour réaliser ceci, vous avez besoin des fonctions suivantes :

 - `int get_offset_from_index(char *table_name, int index)` Cette fonction retourne la valeur de l'offset de la ligne dans le fichier .data de la table `table_name` à partir de son index (il faut donc trouver cet index dans le fichier .idx puis en extraire l'offset correspondant).
 - `void update_table(char *table_name, s_field_record row[], int fields_count, int offset)` Cette fonction va remplacer la ligne à l'offset spécifié par les valeurs stockées dans le tableau row contenant `fields_count` champs. Pour réaliser cette fonction, servez-vous de celles que vous avez définies dans la partie 3.

Vous testerez cette partie sur le code suivant :

```c
s_field_record new_row[MAX_FIELDS] = {
		{
			.field_definition =
			{
				.column_name="id",
				.column_type=TYPE_INTEGER
			},
			.field_value.int_value=2
		},
		{
			.field_definition =
			{
				.column_name="label",
				.column_type=TYPE_TEXT
			},
			.field_value.text_value="hello world modified!"
		},
};

int row_offset = get_offset_from_index(table_name, 1);
update_table(table_name, new_row, 2, row_offset);
display_all(table_name);
```

## Partie 6 : suppression d'une table

Pour supprimer une table, c'est assez simple, il suffit de supprimer les 3 fichiers qui s'y rapportent (index, définition et données), puis de supprimer le répertoire où ils étaient stockés. Vous devez donc écrire la fonction qui réalise ces opérations et dont le prototype est le suivant : `void drop_table(char *table_name)` et qui permet de supprimer la table dont le nom est transmis par le pointeur `table_name`.

Pour tester, vous pouvez utiliser l'instruction suivante :

```c
drop_table(table_name); // table_name from previous definitions.
```
