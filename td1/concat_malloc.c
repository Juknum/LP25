#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Concatènation des paramètres envoyés de façon dynamique
 */
int main(int argc, char const *argv[])
{
  char *res = (char *)malloc(sizeof(char));
  *res = 0;
  size_t length = 1;

  for (int arg = 1; arg < argc; arg++)
  {
    length += strlen(argv[arg]);
    char *tmp = (char *)realloc(res, sizeof(char) * length);

    if (tmp == NULL)
    {
      free(res);
      return 1;
    }

    res = tmp;
    strcat(res, argv[arg]);
  }

  printf("%s\n", res);
  free(res);
  return 0;
}
