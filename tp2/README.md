# LP25 - TP C n°2

Dans ce TP, nous allons faire quelques manipulations de la mémoire et des pointeurs, et les exploiter pour des usages particuliers.

## Exercice 1 - allocation dynamique

Écrire un programme `dyn_alloc.c` qui prend en paramètre une valeur numérique entière que l'on appellera `n` (vérifier la validité du paramètre pour le convertir), qui crée un tableau d'entiers de taille égale à `n`, et le remplit des valeurs `1` à `n`.

## Exercice 2 - décomposition d'une chaîne de caractères

Écrire un programme nommé `split.c` qui prend en paramètre une chaîne de caractères au format CSV (des valeurs séparées par des points-virgule).
Pour passer la chaîne de caractères au programme, si elle contient des espaces, l'encadrer par des doubles quotes.

Le programme doit séparer cette chaîne en un tableau de sous-chaînes délimitées par les `;`. Pour cela, le travail se décompose en 2 étapes :

- parcourir la chaîne pour y compter le nombre `s` de séparateurs (i.e. le nombre de `;` contenus par la chaîne de caractères)
- créer un tableau de `char *` d'une taille égale à `s+1`.
- parcourir la chaîne pour en extraire les éléments entre les `;`. Vous pouvez utiliser l'arithmétique des pointeurs et la fonction `strncpy` pour réaliser cette étape.

Le programme doit afficher les éléments ligne par ligne et se terminer.

## Exercice 3 - union et mémoire

Écrire un programme nommé `split-union.c` qui va reprendre le principe de l'exercice précédent, mais avec quelques différences.
Les éléments de la chaîne de caractères devront être si possible convertis en variables numériques et stockés dans des structures assortie.
Ces structures devront être au nombre maximum de 16, toutes allouées statiquement au début du programme.

Pour cela, utilisez le modèle suivant :

```c
#define STR_MAX 50
#define PARAMETER_BUFFER_SIZE 16

typedef enum {
    IS_INT, /* Data is integer or derived */
    IS_DEC, /* Data is float or double */
    IS_STRING /* Data is a string */
} e_data_type;

typedef union {
    long long integer;
    double decimal;
    char str[STR_MAX];
} data_wrapper;

typedef struct {
    e_data_type data_type;
    data_wrapper data;
} s_any_data;

int main(int argc, char *argv[]) {
    s_any_data my_parameters[PARAMETER_BUFFER_SIZE];
    /* Do stuff here */
    return 0;
}
```

## Exercice 4 - buffers circulaires

Dans cet exercice nommé `circular.c`, nous allons écrire le code d'un buffer circulaire avec un masque d'accès.
L'objectif est de lire au clavier des phrases écrites par l'utilisateur et de les traiter pour mettre les caractères en majuscules.
Pour cela, le programme entre dans une boucle infinie, dans laquelle il demande à l'utilisateur de saisir du texte.
Puis il copie ce texte caractère par caractère dans le buffer circulaire.
Quand la saisie est terminée, le programme lit tout ce qui peut être lu dans le buffer et l'affiche en mettant si possible (i.e. quand les caractères sont des lettres) le caractère en majuscule.

Un buffer circulaire est un buffer de taille fixe qui se remplit en avançant un index d'écriture et se vide dans la même direction (index croissant) en avançant un index de lecture.
La lecture est impossible quand le buffer est vide (`index lecture == index écriture`).
L'écriture est impossible quand le buffer est plein (`index écriture + 1 == index lecture`).
Les index "bouclent", c'est-à-dire qu'arrivé au bout de la mémoire du buffer, un index repart à zéro.

Le bouclage peut être fait de deux manières : soit avec un calcul de modulo, soit avec un masque.
Le calcul de modulo est un peu plus complexe (il faut tester la valeur du modulo du nouvel index) mais permet de traiter n'importe quelle taille de buffer.
Le bouclage avec masque est plus simple mais il ne fonctionne que sur des tailles de buffers en puissances de 2 (i.e. 2, 4, 8, 16, 32, 64, etc.).
C'est ce deuxième choix que nous allons utiliser.

Le principe des indices avec masques est d'utiliser le dépassement de taille des variables à notre avantage.
En prenant par exemple une taille de buffer de 16, représentable par 4 bits et des indices de 0 (soit 0x0 ou 0000b) à 15 (soit 0xf ou 1111b), il est facile de revenir de 15 à zéro par une incrémentation assortie d'un masque.
En effet, `15 + 1` étant égale à 16, soit 10000b, appliquer un masque de 15, soit 1111b à cette valeur (avec l'opération `index & 0x0f`) retournera zéro.
Ceci fonctionne même en atteignant les limites en mémoire de la variable qui contient l'index.
Par exemple, avec un `unsigned short`, et toujours un buffer de taille 16, lorsque la valeur atteint 65535, soit 11111111 11111111b, l'incrémentation de la valeur va créer un dépassement de valeur et réinitialiser la valeur de l'indice à 0 (car `(unsigned short) (65535 + 1)` est égal à zéro).

Vous vous appuierez sur le code suivant pour réaliser cet exercice :

```c
#define MASK 0x7f // Index mask from 0 to 127, i.e. 128 elements
#define BUFFER_SIZE 128
unsigned char read_index = 0;
unsigned char write_index = 0;
char circular_buffer[BUFFER_SIZE];

int write_char(char c);
int read_char(char *c);

int main(int argc, char *argv[]) {
    /* Do stuff here */
    return 0;
}

/*!
 * \brief function write_char writes c to circular buffer unless it is full
 * \param c the character to be appended to circular buffer
 * \return 1 if insertion is successful, 0 if buffer is full
 */
int write_char(char c) {
    /* Implement function here */
    return 1;
}

/*!
 * \brief function read_char reads a character from circular
 * \param c a pointer to the character to be read
 * \return 1 if successful, 0 if buffer is empty
 */
int read_char(char *c) {
    /* Implement function here */
    return 1;
}
```
