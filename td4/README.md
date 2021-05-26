# LP25 TD C n°4 : interagir avec le shell

Dans ce TP, l'objectif est d'écrire des programmes capables d'interagir avec le système, notamment en lisant en entrée des données envoyée par un `pipe` à partir de la sortie de la commande précédente.

## Ouvrir la sortir d'un pipe depuis un programme

Pour ouvrir le pipe en lecture (donc réceptionner le données qui y ont été envoyées), il est nécessaire de lire l'entrée standard, par exemple en appelant la fonction `fgets` sur le descripteur `stdin`.

## Exercice 1

Le programme de cet exercice sera nommé `pipe-cat.c` et pourra soit lire et afficher un fichier passé en argument du programme, soit afficher ce qui lui est transmis par un pipe.

## Exercice 2

Ce second programme est nommé `pipe-maj.c` et reprend le principe du premier exercice, en transformant toutes les minuscules en majuscules avant l'affichage. Ce programme peut également lire et afficher un fichier passé en argument.

## Exercice 3

Cet exercice vise à intercepter le signal d'interruption du programme pour terminer ce dernier correctement en libérant les ressources du programme. Pour cela, nous utiliserons l'API C permettant de manipuler les signaux.

Le programme que vous devez écrire est un programme qui ouvre un fichier texte en écriture, puis boucle indéfiniment sur le comportement suivant :

 - demander à l'utilisateur de saisir une phrase
 - écrire la phrase dans le fichier

Le programme s'arrête quand l'utilisateur presse la combinaison de touches `Ctrl-c`, ce qui envoie le signal `SIGINT` au programme pour lui demander de se fermer.

### Étape 1 : pas de gestion du signal

Pour débuter, copier dans my-signal.c, compiler et exécuter le programme suivant :

```c
#include <stdio.h>

#define BUFFER_SIZE 150

int main(int argc, char *argv[]) {
	FILE *f = fopen("dump.txt", "w");
	if (f) {
		char buffer[BUFFER_SIZE];
		while (1) {
			scanf("%s", buffer);
			fprintf(f, "%s", buffer);
		}
	}
	fclose(f);
	return 0;
}
```

Saisir quelques lignes de texte, puis quitter le programme avec la combinaison de touches `Ctrl-c`. Lire le contenu du fichier dump.txt. Qu'observez-vous ?

### Étape 2 : gérer le signal avec `signal`

Ajouter au programme une variable globale nommée `sigint_trigerred` et de type et qualificateur `volatile sig_atomic_t` qui servira de condition de continuation de la boucle (vous remplacerez donc `while (1)` par `while (!sigint_triggered)`).

Écrire une fonction pour gérer le signal `SIGINT`, qui basculera la valeur de `sigint_triggered` de 0 à 1. le prototype de cette fonction sera `void sigint_handler(int signal)`.

Lier cette fonction au signal `SIGINT` à l'aide de la fonction `signal`. Tester à nouveau le programme. Qu'observez-vous ?

### Étape 3 : utiliser `sigaction`

La dernière modification consiste à utiliser sigaction pour résoudre les écueils observés dans les deux premières étapes. Pour cela vous devez créer une structure de type `struct sigaction` qui appliquera la fonction `sigint_handler` précédemment définie au signal `SIGINT`. Vous devrez également affecter le flag `SA_RESETHAND` au champ `sa_flags` de la structure, et la valeur `NULL` à son champ `sa_restorer`.

Vous remplacerez ensuite l'appel à `signal` par un appel à la fonction `sigaction` (cf. `man sigaction` pour plus d'informations).

Testez cette nouvelle version du programme et observez le résultat. Il reste un dernier défaut (la dernière phrase entrée est écrite deux fois dans le fichier de sortie)

### Étape 4 : ne pas écrire deux fois la même phrase

Implémenter une des solutions suivantes avant de pousser l'exercice sur le serveur :

 - remplacer la boucle `while` par une boucle `do...while`
 - tester la valeur de `sigint_triggered` avant de faire le fprintf
 - affecter le caractère nul au premier caractère de `buffer` après l'avoir écrit dans le fichier.

Par ailleurs, le programme actuel n'est pas très fiable car il permet facilement de l'attaquer en débordant le buffer de lecture. Remplacer `scanf` et `fprintf` par des fonctions qui limitent la taille des données lues/écrites.

## Exercice 4

Copier `my-signal.c` sous le nom `my-raise.c`. Quand l'utilisateur a saisi sa phrase, tester si celle ci est égale à `"END"`. Si c'est le cas, générer le signal `SIGINT` à l'aide de la fonction `raise` pour terminer le programme.

Pour éviter toute remarque, il s'agit d'un usage pédagogique de la fonction `raise`. Il serait bien sûr plus simple que la saisie du mot `"END"` par l'utilisateur modifie la valeur de `sigint_triggered` mais ceci ne permettrait pas de manipuler la fonction qui émet un signal à partir d'un programme.
