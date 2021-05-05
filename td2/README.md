TD2

# LP25 - C TD n°2

Ce TD est une brève initiation à l'utilisation de la commande make et l'écriture de fichiers Makefile pour définir les règles de compilation.

## Compilation séparée

Mais avant de se lancer dans ces outils, commençons par la compilation séparée en elle-même.

Il est possible et même souhaitable de décomposer un code complexe en plusieurs fichiers de code. Plusieurs impacts positifs à cette décomposition existent, parmi lesquels :

 - Vitesse de compilation : seuls les fichiers ayant été modifiés ont besoin d'être compilés
 - Modularité : en décomposant votre code en fichiers selon une logique de fonctionnalités ou de rôles, vous en facilitez la compréhension : il suffit de lire les entêtes pour utiliser une autre unité de compilation, seul le code pertinent au moment où vous y travaillez vous est visible.
 - Travail en équipe : en se répartissant les tâches sur des fichiers différents, vous réduisez les conflits lors de la fusion de vos travaux respectifs.

Prenons l'exemple suivant :

swap.h :
```c
#ifndef _SWAP_H_
#define _SWAP_H_

void swap(int *a, int *b);

#endif //_SWAP_H_
```

swap.c :
```c
#include "swap.h"

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
```

main.c :
```c
#include "swap.h"

int main() {
	int a=5, b=6;
	swap(&a, &b);
	return 0;
}
```

Dans cet exemple, `swap.h` expose la fonction `swap` à ses utilisateurs. `swap.c` définit le comportement de la fonction `swap`, et la fonction `main` utilise la fonction `swap`. Pour utiliser cette fonction, le fichier `main.c` doit notamment include le fichier d'entête `swap.h`.

Dans les étapes de la compilation, nous allons donc nous intéresser à la compilation proprement dite et à l'édition de liens (le reste des étapes étant moins concerné par la compilation séparée).

Tout d'abord, il faut générer le fichier objet du code des fichiers `swap.[hc]`. On utilise pour cela l'option `-c` de gcc, et on lui donne un fichier de sortie (option `-o`) suffixé par un `.o`. Puis on fait de même avec le main. On peut alors procéder à l'édition des liens, consistant ici à permettra au compilateur de lier l'appel à `swap` fait dans la fonction `main` à son adresse (obtenue par sa position dans le fichier binaire final). On procède à l'ensemble de ces opération avec les commandes suivantes :

```bash
gcc -c -o swap.o swap.c
gcc -c -o main.o main.c
gcc -o main main.o swap.o
```

**Pratique**

Tester l'exemple ci dessus puis parcourir et essayer de comprendre ce que vous retourne l'exécution de la commande `objdump -d` sur `swap.o`, `main.o` et `main`. Cette question ne nécessite pas de retour sur le dépôt de code.

**Exercice**

Séparer de la même manière que l'exemple, le code de résolution du polynôme du TP précédent, de celui du main. Pousser sur le dépôt git les fichiers créés ainsi qu'un fichier bash contenant les commandes pour compiler le programme.

## make et les Makefile

`make` est une commande permettant la compilation séparée grâce à des règles écrites dans un fichier nommé par défault `Makefile`. Ces règles peuvent être dédiées à un fichier, ou bien représenter des traitements suivant des motifs.

### Règles

Une règle est de la forme :
```
nom: dépendances
	commande
```
Par exemple, l'édition des liens de l'exemple précédent peut s'écrire de la manière suivante :

```
main: main.o swap.o
	gcc -o main main.o swap.o
```

Les dépendances signifient que la cible doit être construite si une de ses dépendances a changé.

**Exercice**

Écrire les règles pour produire les fichiers objet.

### Règles génériques

Imaginons maintenant que le main dépende de 10 autres fichiers, tous indépendants les uns des autres par ailleurs. Comment éviter de répéter la règle permettant de compiler le fichier objet ?

Il est possible d'utiliser des motifs dont :

 - `%` dans une cible ou une dépendance, remplace une séquence de caractères. Par exemple `%.o` signifie tous les .o
 - `$@` est le nom de la cible dans la commande qui lui correspond
 - `$<` est le nom du fichier de dépendance à compiler

**Exercice**

Modifiez votre Makefile pour le rendre générique pour la compilation des fichiers objet. Testez le et pousser le sur le dépôt git.

**Observation**

Supprimer les fichiers `main`, `main.o` et `swap.o`, puis lancez la commande `make main` et observez ce qu'il se passe.

### Paramétrage du Makefile

Vous pouvez également définir des variables dans votre Makefile pour faciliter son écriture et son évolution. Une variable se définit comme en shell `NOM_VAR=value_var`. Ces variables sont ensuite utilisées avec la syntaxe `$(NOM_VAR)`. Il est courant de rendre paramétrables le compilateur, les options de compilation, ainsi que les chemins de production des fichiers.

**Exercice**

En utilisant les variables, paramétrer le Makefile pour que les fichiers objet soient créés dans un répertoire nommé `objects` et que le fichier binaire soit créé dans le répertoire `bin`. Poussez cette dernière version du Makefile dans le dépôt git.

## Fin du TD

Une fois ce TD terminé et s'il vous reste du temps, vous pouvez ensuite reprendre votre travail ou commencer le TP.