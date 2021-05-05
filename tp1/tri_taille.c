#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Compare two string together, return true if the first string is longer than the second one
 * If string make the same size, return true if the first string is before the second one (alphabetically)
 * @param char *str1
 * @param char *str1
 * @return boolean
 */
bool compare(char *str1, char *str2)
{
  if (strlen(str1) > strlen(str2))
    return true;

  if (strlen(str1) == strlen(str2))
  {
    size_t i = 0;
    while (i < strlen(str1) && str1[i] == str2[i])
      i++;

    if (i != strlen(str1) && str1[i] > str2[i])
      return true;
  }

  return false;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
    return 1; // needs args to works

  char **results = (char **)malloc(sizeof(char *) * (argc - 1));
  for (int i = 1; i < argc; i++)
  {
    results[i - 1] = argv[i];
  }

  bool changed = true;
  char *tmp;

  while (changed)
  {
    changed = false;

    for (int i = 0; i < argc - 2; i++)
    {
      if (compare(results[i], results[i + 1]))
      {
        tmp = results[i + 1];
        results[i + 1] = results[i];
        results[i] = tmp;
        changed = true;
      }
    }
  }

  for (int i = 0; i < argc - 1; i++)
  {
    printf("%s ", results[i]);
  }

  free(results);
  return 0;
}