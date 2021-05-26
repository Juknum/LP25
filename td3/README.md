# TD C n°3 : manipulation du système de fichiers

Dans ce TD, vous apprendrez à parcourir les répertoires et lire les informations des fichiers et dossiers qu'il s'y trouvent.

## Exercice 1

Ce programme, nommé `my-ls.c` a pour objectif d'afficher la liste des fichiers contenus par un répertoire dont le nom est passé en paramètre du programme. L'ensemble des fonctions et types nécessaires pour réaliser ce programme vous ont été décrits dans le cours.

## Exercice 2

En reprenant le programme précédent, et en le renommant `my-ext-ls.c`, vous devez maintenant afficher à côté de chaque fichier son type (répertoire, fichier standard, lien, etc.).

## Exercice 3

En reprenant le programme précédent, et en le renommant `my-size-ls.c`, vous devez maintenant afficher à côté de chaque fichier sa taille, en octets, puis en multiples binaires, ainsi qu'en multiples SI. Par exemple si un fichier nommé `a_file.txt` fait 1250 octets, il affichera les tailles comme suit :

```bash
a_file.txt 1250 1.22kio 1.25ko
```

Si au moins un kilo (binaire ou SI) n'est pas atteint, ne pas spécifier la taille pour ce multiplicateur. Pour les multiplicateurs plus importants (M, G, éventuellement T), tester que le résultat est supérieur à 1 avant de passer au multiple supérieur.

Arrondissez les tailles à 2 chiffres après la virgule.

## Exercice 4

Ce dernier exercice consiste à écrire un programme nommé `my-find.c` qui permet de chercher un fichier dont le nom est passé en second paramètre dans un dossier dont le nom est passé en premier paramètre. La recherche est récursive et simple (on cherche le nom exact du fichier)
