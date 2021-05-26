# TP C n°3 : les fichiers

Dans ce TP, vous allez manipuler des fichiers en lecture et en écriture.

## Exercice 1

Cet exercice consiste à lire dans un fichier texte et à afficher ce qui est lu. Le programme pour réaliser l'exercice s'appellera `my-cat.c`. Vous pouvez lui joindre des fichiers entête et code additionnels à la condition de fournir également un Makefile pour pouvoir compiler toute votre production de ce TP.

Le nom du fichier à lire est passé en argument du programme.

Pour rappel, utiliser un fichier se fait de la manière suivante :

```c
#include <stdio.h>

#define BUFFER_SIZE 150

int main() {
	FILE *f = fopen("path_to_file", "r"); // Open in text mode, for reading
	if (!f) return 1;
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, f)) {
		// Do something with buffer content
	}
	fclose(f); // Do not forget that to free file handle resources
	return 0;
}
```

## Exercice 2

Cet exercice sera nommé `write-text.c` et consistera à écrire dans un fichier texte. Le programme prend en argument un entier `s` au moins égal à 4 (si le paramètre manque, ou est invalide, la valeur 4 sera utilisée) pour écrire dans le fichier de sortie un losange de `1 + 2 * (s - 1)` de haut et de large, de la manière suivante (exemple pour la valeur 4) :

```text
   *
  ***
 *****
*******
 *****
  ***
   *
```

## Exercice 3

Cet exercice consiste à lire dans un fichier binaire. Le programme se nomme `checksum.c` et prend en argument le chemin vers un fichier binaire. Il en extrait le checksum BSD calculé de la manière suivante et il affiche le résultat à l'écran (en hexadécimal) :

```c
#include <stdint.h>

uint16_t bsd_checksum(uint8_t byte, uint16_t current_checksum) {
	uint16_t checksum = current_checksum;
	checksum = (checksum >> 1) + ((checksum & 1) << 15);
	checksum += byte;
	return checksum;
}
```

Pour rappel, l'ouverture d'un fichier en lecture binaire se fait avec le mode `"rb"`, et la lecture avec la fonction `fread`.

## Exercice 4

Cet exercice consiste à lire dans un fichier texte et à écrire dans un fichier binaire. Le programme s'appelle `ihex2bin.c` et vous permettra de convertir un programme compilé et stocké au format iHex (Intel Hex) en fichier binaire. Les deux fichiers sont passés en paramètres du programme dans l'ordre suivant : fichier hex, fichier bin.

Le format iHex représente en hexadécimal un fichier binaire ainsi que son adresse d'origine. Il est fréquemment utilisé dans les systèmes embarqués pour programmer un microcontrôleur en lui envoyant son programme au format iHex.

Pour simplifier le problème, vous ne lirez que les enregistrements iHex de type `00` (8ème et 9ème caractères d'une ligne).

Chaque ligne est de la forme `:SSAAAAFFVV...VVVCC` où :

 - les `:` signifient un début de ligne;
 - les deux caractères `SS` définissent sur un octet représenté en hexadécimal la longueur nommée `size` de la valeur sur la ligne courante;
 - les 4 caractères `AAAA` définissent sur 2 octets l'adresse du segment courant à partir de l'adresse de départ (non traitée dans cet exercice);
 - les 2 caractères `FF` définissent sur un octet le type de ligne. Nous ne traiterons que les lignes de type `00`;
 - la séquence de `2 * size` caractères suivants définissent le contenu du segment de fichier binaire;
 - les 2 caractères `CC` définissent sur un octet une somme de contrôle de la ligne. Nous ne traiterons pas cette somme de contrôle dans ce TP.

L'ouverture d'un fichier binaire en écriture se fait avec le mode `"wb"` et l'écriture se fait avec la fonction `fwrite`.

Un fichier .hex vous est fourni, ainsi que le .bin correspondant. Une fois votre programme fonctionnel, comparez le résultat produit avec le contenu du fichier binaire qui vous a été fourni avec ce sujet. Vous utiliserez pour cela la commande : `diff mon_fichier.bin Appli-ng.bin` qui ne devrait rien retourner à l'écran (signifiant qu'aucune différence n'existe entre les deux fichiers).
