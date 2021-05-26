# LP25 - C TD n°1

L'objectif de ce TD est de faire quelques rappels sur le langage C et notamment le processus de développement en C. Ces rappels seront utiles pour réaliser l'ensemble des TD et TP portant sur le C pendant la seconde moitié du semestre.

Le TP n°1 porte également sur des rappels. Il est à faire après le TD n°1. Pour cette raison, vous commencerez par le TD puis vous ferez le TP, même si vos sessions de TP sont avant les TD (dans ce cas, vous faites le TD pendant le TP, et le TP pendant le TD)

## Compilation

Le langage C est un langage compilé, c'est-à-dire qu'il est analysé pour être converti en langage machine (des instructions binaires dépendantes de l'architecture de la machine) avant de pouvoir être exécuté. Sur les machines de TP, le compilateur utilisé est le compilateur C de la GCC (GNU Compiler Collection). Il s'utilise de la manière suivante :
```
gcc fichier_source.c -o programme
```
où :

 - _fichier_source.c_ est le code du programme
 - _programme_ est le nom de l'exécutable.

D'autres options existent et seront abordées plus loin.

## Programme simple

Le premier programme que nous allons écrire est un simple _Hello, World!_ dont voici le code :

```c
#include <stdio.h>

int main() {
	printf("Hello, World!\n");
	return 0;
}
```

Ce programme inclut le fichier d'entête _stdio.h_ nécessaire à l'utilisation de la fonction _printf_, puis il déclare la fonction principale nommée _main_ du programme (il n'en existe qu'une et une seule par programme). Dans cette fonction, délimitée par des accolades, l'instruction _printf_ permet d'afficher sur la sortie standard (le terminal où sera exécuté le programme) la chaîne de caractères qui lui est passée en paramètre. Puis la fonction retourne la valeur 0, qui signifie que l'exécution s'est bien déroulée.

Pour compiler ce programme, que vous sauvegarderez dans le fichier _hello.c_, vous utiliserez la commande suivante : `gcc hello.c -Wall -o hello`, puis vous pouvez l'exécuter en vous plaçant dans le répertoire où se trouve le fichier exécutable _hello_, puis en saisissant la commande : `./hello` vous devriez voir sur le terminal la phrase `Hello, World!` s'afficher, puis votre prompt sur la ligne suivante.

## Passer un paramètre au programme

Nous allons maintenant changer la signature (le nom, le type de retour, et les paramètres de la fonction) pour lui permettre d'accepter des paramètres et de les traiter. Pour ce faire, `int main()` devient `int main(int argc, char *argv[])`. Ces deux paramètres ont des valeurs précises :

 - _argc_ est un entier dont la valeur est égale au nombre d'arguments du programme
 - _argv_ est un tableau de chaînes de caractères contenant les arguments, et dont la taille est égale à la valeur de _argc_

Attention ! le tableau _argv_ contient au minimum une valeur qui est à la première position (accessible avec l'indice zéro, donc _argv[0]_) et qui est le nom du programme lui même. Tous les autres arguments doivent être vérifiés avant utilisation pour éviter un accès à des valeurs inexistantes et une **erreur de segmentation** qui arrête le programme.

**Exercice**

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
	/*
	 Compléter ici pour vérifier qu'il y a un argument suivant le nom du programme.
	 Si l'argument n'est pas présent, renvoyer 1 (erreur du programme)
	 Sinon, afficher "Hello, %s!" en substituant %s par la valeur de l'argument n°2
	*/
	return 0;
}
```

Pour vous assurer du fonctionnement de votre programme et de sa valeur de retour, testez deux exécutions du programme, l'une sans argument, l'autre avec un argument, et faites afficher à chaque exécution le résultat de la commande précédente. Par exemple :
```bash
./hello
echo $? # Devrait afficher 1
./hello Bob
# Devrait afficher "Hello, Bob!"
echo $? # Devrait afficher 0
```

## Gérer le code source

La suite des exercices du semestre reposera sur l'outil git pour remettre votre production. Git est un gestionnaire de code source et de version qui permet de tracer les changements dans le code grâce à un système basé sur la commande _diff_. Plusieurs fonctions de git vous seront utiles :

 - **clone [URL]** : permet de cloner le dépôt de code pour commencer à y travailler. Cette commande n'est utilisée que pour créer une copie locale du projet dans un emplacement qui ne contient pas encore de code ni de documents gérés par git. Le projet copié est celui dont l'URL est passée en paramètre
 - **branch [nom de branche]** : crée une branche à partir de laquelle les modifications du code seront indépendantes des autres branches, jusqu'à une éventuelle fusion. Le nom de la branche ne doit pas encore exister. Il vous sera demander de créer une branche nommée d'après votre login pour remettre vos TD et TP.
 - **checkout [nom de branche]** : se place dans une branche pour y travailler. Cette branche doit déjà exister.
 - **commit** : une fois que vos modifications du code ont été faites, vous devez les entériner avec la commande commit. Auparavant, tous les fichiers ajoutés ou modifiés doivent être ajoutés au commit avec la commande **add [nom de fichier]**.
 - **push** : une fois vos modifications _commitées_, vous pouvez les pousser sur le serveur distance grâce à la commande **push**
 - **pull** : à l'inverse, vous pouvez télécharger toutes les dernières modifications du code sur le serveur distant en les _tirant_ dans votre copie locale.

Vous pourrez également consulter la playlist suivante avec des exemples des commandes git : [liste à propos de git](https://www.youtube.com/playlist?list=PLNgzB9uJ0Ss58ZdoPk1vueOMYYdfBkKoS)

## Rappels succincts du C

### Variables, types et opérateurs

En programmation C, les valeurs manipulées, appelées variables, sont nommées par un identifiant et leur type est déclaré avant tout usage. Les types de base les plus utilisés sont :

 - **int** : un entier sur 32 bits (4 octets)
 - **short** : un entier sur 16 bits (2 octets)
 - **float** : un nombre à virgule flottante
 - **double** : un grand nombre à virgule flottante
 - **char** : un caractère ASCII sur 1 octet (8 bits)
 - Propriété **unsigned** : la propriété non signée permet à une valeur d'être définie sur l'intervalle 0..MAX au lieu de -MAX/2..MAX-1

Exemple avec les entiers et les caractères :

| Type | Min signé | Max signé | Min non signé | Max non signé |
|------|-----------|-----------|----------------|----------------|
| int  |-2147483648| 2147483647| 0 | 4294967295 |
| short| -32768  | 32767 | 0 | 65535 |
| char | -128 | 127 | 0 | 255 |

La déclaration d'une variable se fait avec la syntaxe suivante : TYPE nom; (le point-virgule est obligatoire comme à la fin de toute instruction), où type est un des types existant en C, et nom est un identifiant défini suivant les règles suivantes :

 - le premier caractère est une lettre (minuscule ou majuscule), ou un _underscore_ `_`
 - le reste des caractères est composé de chiffres, de lettres minuscules et majuscules, et du caractère `_`
 - chaque identifiant est unique dans sa portée (un seul nom de variable donné ne peut exister à un moment donné)

Ces variables peuvent ensuite être manipulées avec des opérateurs pour modifier leurs valeurs. Par exemple, les opérateurs arithmétiques permettent d'appliquer `+ - / *` à des variables.

**Exercice**

Écrire un programme qui inverse les valeurs de deux variables de type identique. Ce programme s'appelle _inversion.c_.

### Fonctions

Il est souvent nécessaire de décomposer un programme en plusieurs sections de code, que ce soit parce que ce code va être utilisé depuis plusieurs segments du code, ou pour faciliter la maintenance et le découpage logique du code. Pour réaliser cet objectif, le C permet de définir des fonctions. Celles-ci, définies d'une manière analogue à la fonction _main_, peuvent avoir des signatures très différentes. Une fonction doit être déclarée avant sont usage, et il est possible de séparer sa signature (son "modèle", composé du type de retour, du nom et des paramètres de la fonction) de sa définition (le code qu'elle contient).

Voici quelques signatures de fonctions :

```c
void do_something(void); // Fonction sans paramètre ni retour
void do_something_else(int v); // Fonction sans retour mais avec un paramètre entier v
char do_something_2(double v); // Fonction avec retour et paramètre décimal v
```

Des définitions de ces fonctions pourraient être :

```c
void do_something(void) {
	printf("Toujours ça\n");
}

void do_something_else(int v) {
	if (v == 0)
		printf("C'est zéro\n");
	else
		printf("Valeur non nulle\n");
}

char do_something_2(double v) {
	if (v != 0.0) {
		return '1';
	} else {
		return '0';
	}
}
```

On les appellerait alors depuis une autre fonction (le _main_ par exemple) de la manière suivante :

```c
int main() {
	do_something();
	do_something_else(4);
	do_something_2(0.0);
	return 0;
}
```

**Exercice**

Écrire un programme nommé **swap.c** qui comporte une fonction dont la signature est `void swap(int *a, int *b)` et qui permet d'échanger les valeurs contenues par les variables `a` et `b`. Les `*` dans la signature signifient que les variables a et b sont des pointeurs, donc des adresses mémoire. En déréférençant le pointeur `a` grâce à la syntaxe `*a`, on obtient la valeur de la variable pointée. Par exemple :

```c
int main() {
	int a = 5;
	int *p = &a; // p est un pointeur qui pointe sur a, donc son adresse est &a
	printf("%p\n", p); // Affiche 0x.... l'adresse de a en mémoire
	printf("%d\n", *p); // Affiche la valeur de a : 5
	int b = *p * 2; // b est égal à 2*a, donc 10
	return 0;
}
```

### Tableaux et chaînes de caractères

Les tableaux sont des séquences contigües d'élément du même type, accessibles par leur position dans le tableau, commençant à l'indice 0. Il existe deux types de tableaux : les tableaux statiques, et les tableaux dynamiques. Les tableaux statiques ont une taille définie à l'écriture du programme alors que les tableaux dynamiques reposent sur une allocation mémoire dynamique.

```c
int tableau1[10]; // Tableau de 10 entiers
int tableau2[] = {1, 2, 3, 4}; // Tableau de 4 entiers initialisés
int *tableau_dynamique = malloc(sizeof(int) * 15); // Tableau dynamique avec 15 entiers
// ...
// Utilisation de tableau_dynamique
// ...
free(tableau_dynamique); // Il faut toujours penser à désallouer un tableau dynamique
```

Les chaînes de caractères (qui définissent des séquences de caractères de type `char`) sont également des tableaux, dont les éléments sont des caractères. Les chaînes de caractères doivent terminer par le caractère nul dont le code est `'\0'`. Il est donc toujours nécessaire qu'une chaîne de caractère prévoit un caractère de plus que le mot de taille maximale qu'elle devra contenir.

```c
char chaine1[] = "Bob"; // initialisée avec le mot "Bob"
char chaine2[50]; // Peut contenir 49 caractères + fin de chaîne (caractère '\0')
char *chaine3 = "Bob2"; // Initialisée à Bob2
```

Contrairement à d'autres langages plus abstraits (C++, Java, Python), les chaînes de caractères ne s'utilisent pas avec des opérateurs arithmétiques mais par des fonctions (en effet, il s'agit de tableaux, et pas de types standard). Les plus utiles des fonctions sont :

 - **strcmp** permet la comparaison de deux chaînes de caractères. Renvoie 0 en cas d'égalité, une valeur inférieure à zéro si la première chaîne est avant la seconde (ordre des codes ASCII), une valeur supérieure à zéro dans le cas contraire.
 - **strncmp** fait comme **strcmp** mais sur **n** caractères au maximum
 - **strlen** retourne la taille de la chaîne de caractères passée en paramètre
 - **strcpy** copie la chaîne source (second paramètre) dans la chaîne destinatation (premier paramètre)
 - **strncpy** fait comme **strcpy** mais copie au maximum **n** caractères
 - **strcat** ajoute le contenu du second paramètre à la chaîne du premier paramètre et renvoie un pointeur sur la chaîne résultante
 - **strncat** fait comme **strcat** mais ajoute au maximum **n** caractères.

Leur utilisation est définie en détail dans les manuels accessibles avec la commande `man strcmp` pour **strcmp**, etc.

**Exercice**

Écrire un programme nommé _concat.c_ qui permet de parcourir tous les paramètres passés au _main_ et de les concaténer dans une chaîne de caractères d'une taille maximale de 100 caractères (incluant le caractère nul de fin de chaîne). Afficher la chaîne résultante.

### Gestion de la mémoire

La mémoire peut être acquise avec les fonctions **malloc** et **realloc** pour obtenir ou redimensionnée de la mémoire préalablement acquise. Tout allocation avec **malloc** doit être ensuite libérée par la fonction **free**. Des exemples d'allocations sont définis ci-dessus avec les tableaux dynamiques.

**Exercice**

À partir du programme précédent (_concat.c_), modifier le comportement pour créer une chaîne de caractères qui pourra contenir tous les paramètres passés au programme.

## Rendu du TD

Pour rendre votre travail, vous devrez créer une branche dans le dépôt du TD (nommée selon votre login à l'UTBM), commiter dans cette branche et la pousser sur le serveur de l'UTBM une fois votre travail terminé.
La liste des commandes à exécuter est la suivante :

```bash
git clone https://git-info.utbm.fr/lp25p21/td1.git
cd td1
git branch <votre nom de branche>
git checkout <votre nom de branche>
# Créer vos programmes, les compiler, les tester
git add *.c
git commit -m "Envoi du TD fini" # Vous pouvez utiliser un autre message de commit
git push -u origin <votre nom de branche>
```