#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 100

/**
 * Concatènation des paramètres envoyés
 */
int main(int argc, char *argv[])
{
  char res[LENGTH + 1] = {0};
  int length = LENGTH;

  // construction de la chaîne de charactère
  for (int arg = 1; arg < argc && length > 0; arg++)
  {
    strncat(res, argv[arg], length);
    length -= strlen(argv[arg]);
  }

  printf("%s\n", res);
  return 0;
}