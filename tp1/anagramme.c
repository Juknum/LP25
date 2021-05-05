#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// BE CAREFULL : case sensitive -> e != E

/**
 * Concat given string together
 * @param int argc
 * @param char *argv[] (const)
 */
char* fixString(int argc, char const *argv[])
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
      return "";
    }

    res = tmp;
    strcat(res, argv[arg]);
  }

  return res;
}

/**
 * Reverse the given string
 * @param char*
 */
void reverseString(char *str) {
  size_t len = strlen(str);
  char *buffer = malloc(sizeof(char)*(len+1));

  strcpy(buffer, str);
  for (size_t n = 0; n < len; n++)
  {
    str[len - n - 1] = buffer[n];
  }
  free(buffer);
}

/**
 * Return true if the given string is an anagram
 * @param char* str
 */
bool isAnagram(int argc, char const *str[])
{
  char *string = fixString(argc, str);
  char *stringReversed = fixString(argc, str);
  reverseString(stringReversed);

  bool res = true;

  for (size_t n = 0; string[n] && stringReversed[n]; n++) {
    if (string[n] != stringReversed[n])
    {
      res = false;
      break;
    }
  }

  return res;
}

int main(int argc, char const *argv[])
{
  if (argc < 2) return 1;

  switch (isAnagram(argc, argv))
  {
  case true:
    printf("That's an anagram!");
    break;
  
  default:
    printf("That's not an anagram :(");
    break;
  }

  return 0;
}