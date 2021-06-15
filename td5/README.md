# LP25 TD C n°5 : getopt

Dans ce TP, vous allez utiliser `getopt` et `getopt_long` pour paramétrer le lancement d'un programme avec des options passées au programme.

## Partie 1 : `getopt`

Dans cette partie, nous allons voir comment utiliser `getopt`, fonction qui n'admet que des options à un caractère (en plus du `-` qui les précède). La fonction getopt s'utilise en spécifiant les caractères d'options possibles, ainsi que la présence ou non d'un argument accompagnant l'option. La syntaxe est similaire au shell avec une chaîne de caractères contenant toutes les options éventuellement suivies de `:` en cas d'argument attendu.

Par exemple, le code suivant permet d'attendre l'option `-o` sans paramètre et l'option `-a` avec un paramètre. On y passe à `getopt` le nombre d'arguments à analyser, le tableau des arguments (souvent, ces deux paramètres sont ceux transmis au `main`), puis la chaîne de caractère qui définit les options attendues.

```c
int result = getopt(argc, argv, "oa:");
```

La fonction `getopt` retourne la valeur du caractère de l'option quand celle ci est rencontrée, et -1 si aucune option n'est rencontrée. Pour exploiter les options ci dessus, il est nécessaire de boucler sur l'appel à `getopt` tant que sa valeur de retour n'est pas nulle.

```c
#include <unistd.h>

int main(int argc, char *argv[]) {
	int opt = 0;
	while((opt = getopt(argc, argv, "oa:")) != -1) {
		switch (opt) {
			case 'o':
				/* Do something with 'o' flag */
				break;
				
			case 'a':
				/* Do something with 'a' and the argument pointed by optarg */
				break;
		}
	}
	return 0;
}
```

**Exercice**

Écrire un programme `simple-getopt.c` qui reprend le main ci-dessus et affiche les options qui ont été passées au programme (et leurs arguments éventuels le cas échéant). Jouer un peu avec les options (entrer des options non prévues, ne pas mettre d'argument là où il est requis, etc.) et observer le comportement du programme.

Il est également possible de spécifier un argument facultatif avec le caractère de l'option suivi de `::`. Dans ce cas, soit l'argument n'existe pas, soit il est dans le même argument (exemple : `-barg` pour l'option `b` et la valeur d'argument `arg`), soit il suit l'option (élément suivant de `argv`) mais il faut alors tester soi même la valeur existante dans argv (grâce à l'indice interne `optind`, en s'assurant auparavant qu'il ne dépassera pas les indices autorisés pour `argv`, i.e. `argc-1`)

**Exercice**

Écrire le programme `getopt-optionalarg.c` qui reprend les options de `simple-getopt.c` et y ajoute l'option `b` avec un argument facultatif. Tester les cas suivants pour vous assurer que l'implémentation est correcte :

```bash
 ./getopt-optionalarg -o -a azer -b 5214
 ./getopt-optionalarg -o -a azer -b
 ./getopt-optionalarg -breza -a 123
 ./getopt-optionalarg -b qsdf -o
```

Et assurez vous que les valeurs pour `b` sont :

 - "_5214_"
 - rien
 - "_reza_"
 - "_qsdf_"

## Partie 2 : `getopt_long`

Il est également possible de fournir au programme des options longues préfixées par un double tiret `--`. Dans ce cas, la configuration passe par un tableau de structures de type `struct option`. Pour bien comprendre le fonctionnement, lire attentivement le manuel de la fonction `getopt_long`.

Pour expliciter son fonctionnement, nous allons remplacer les options courtes des exercices précédents par des options longues que nous nommerons `org` pour le `-o`, `app` pour le `-a` et `binary` pour le `-b` (ne cherchez pas un sens aux options, il n'y en a en l'occurrence absolument aucun). Le programme deviendrait ceci :

```c
#include <unistd.h>

int main(int argc, char *argv[]) {
	int opt = 0;
	struct option my_opts[] = {
		{.name="org",.has_arg=0,.flag=0,.val='o'},
		{.name="app",.has_arg=1,.flag=0,.val='a'},
		{.name="binary",.has_arg=2,.flag=0,.val='b'},
		{.name=0,.has_arg=0,.flag=0,.val=0}, // last element must be zero
	};
	while((opt = getopt_long(argc, argv, "", my_opts, NULL)) != -1) {
		switch (opt) {
			case 'o':
				/* Do something with 'o' flag */
				break;
				
			case 'a':
				/* Do something with 'a' and the argument pointed by optarg */
				break;
				
			case 'b':
				/* Do something with 'a' and the optional argument pointed by optarg */
				break;
		}
	}
	return 0;
}
```

**Exercice**

Écrire un programme `blinky-apploader-cli.c` qui utilise des options longues pour configurer un programme de contrôle de robots avec les possibilités suivantes (vous en simulerez le comportement avec des affichages du type "_Robot is < ACTION >_") :

 - Option `color` qui prend en paramètre (optionnel) le code rgb d'une couleur devant être affichée par le robot. Si le paramètre n'existe pas, la couleur est noire.
 - Option `tree` sans paramètre pour générer un arbre couvrant (un graphe sans cycle qui passe une fois par chaque noeud) entre les robots.
 - Option `config` sans argument pour obtenir la configuration du robot connecté.
 - Option `set` avec argument pour définir la valeur d'une option de configuration du robot.
 - Option `jump` avec argument optionnel pour lancer une application secondaire sur le robot. Le paramètre optionnel définit l'adresse en mémoire du programme. Par défaut, l'adresse hexadécimale `0x8010000` sera utilisée.
 - Option `reboot` sans argument pour redémarrer le robot.
 - Option `program` avec un argument pour déployer dans la structure de robots le programme en paramètre de l'option.

Tester votre programme avec toutes les options d'abord seules, puis en les combinant entre elles.
