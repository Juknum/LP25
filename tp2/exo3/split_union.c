#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/***************/

#define STR_MAX 50
#define PARAMATER_BUFFER_SIZE 16

typedef enum {
  IS_INT,
  IS_DEC,
  IS_STRING
} e_data_type;

typedef union {
  long long integer;
  double decimal;
  char str[STR_MAX];
} data_wrapper;

typedef struct {
  e_data_type data_type;
  data_wrapper data;
} s_any_data;

/***************/

/**
 * Used token for the parsing phase
 */
struct token {
  char *begin;
  size_t length;
};
typedef struct token token_t;

/**
 * Return the number of the given char inside the given String
 * @param char* String
 * @param char Char
 */
size_t count_char(char *str, char s) {
  size_t res = 0;

  while (*str) {
    if (s == *str) res++;
    str++;
  }

  return res;
}

/**
 * Extracts all tokens from the given string
 * @param char* String
 * @param char Separator
 * @param size_t* Number of tokens
 */
token_t *get_tokens(char *str, char s, size_t *n_tokens) {
  size_t len = count_char(str, s);
  token_t *tokens = (token_t *)calloc(len + 1, sizeof(token_t));

  // handle missing memory
  if (!tokens) exit(2);

  size_t n = 0;
  char *begin = str;

  while (*str) {
    if (*str == s) {
      tokens[n].begin = begin;
      tokens[n].length = str >= begin ? str - begin : 0;
      begin = str + 1;
      n++;
    }

    str++;
  }

  if (str > begin) {
    tokens[n].begin = begin;
    tokens[n].length = str - begin;
  }

  *n_tokens = len + 1;

  return tokens;
}

/**
 * Set the array of string (array of array)
 * @param token_t* Tokens
 * @param size_t Number of tokens
 */
char **read_tokens(token_t *tokens, size_t n_tokens) {
  char **res = (char **)malloc(sizeof(char *) * n_tokens);

  for (size_t n = 0; n < n_tokens; n++) {
    res[n] = (char *)malloc(sizeof(char) * (tokens[n].length + 1));

    // handle missing memory
    if (!res[n])
      exit(2);

    strncpy(res[n], tokens[n].begin, tokens[n].length);
    res[n][tokens[n].length] = 0;
  }

  return res;
}

char **read_input(int argc, char *argv[], size_t *n_tokens) {
  char *str;
  if (argc >= 1) str = argv[1];
  else return 1;

  token_t* tokens = get_tokens(str, ';', n_tokens);
  char** elements = read_tokens(tokens, *n_tokens);

  free(tokens);
  return elements;
}

int main(int argc, char *argv[]) {
  s_any_data my_parameters[PARAMATER_BUFFER_SIZE];

  size_t n_tokens = 0;
  char **elements = read_input(argc, argv, &n_tokens);

  for (size_t n = 0; n < n_tokens && n < PARAMATER_BUFFER_SIZE; n++) {
    if (count_char(elements[n], '.') > 0) {
      double decimal;
      if (sscanf(elements[n], "%lf", &decimal) == 1) {
        my_parameters[n].data_type = IS_DEC;
        my_parameters[n].data.decimal = decimal;
        continue;
      }
    }
    else {
      long long integer;
      if (sscanf(elements[n], "%lld", &integer) == 1) {
        my_parameters[n].data_type = IS_INT;
        my_parameters[n].data.integer = integer;
        continue;
      }
    }

    // default:
    my_parameters[n].data_type = IS_STRING;
    strncpy(my_parameters[n].data.str, elements[n], STR_MAX - 1);
    my_parameters[n].data.str[STR_MAX - 1] = 0;
  }

  
  for (size_t n = 0; n < n_tokens && n < PARAMATER_BUFFER_SIZE; n++) {
    switch (my_parameters[n].data_type) {
      case IS_INT:
        printf("INT:\t%lld\n", my_parameters[n].data.integer);
        break;
      case IS_DEC:
        printf("DEC:\t%lf\n", my_parameters[n].data.decimal);
        break;
      case IS_STRING:
        printf("STRING:\t%s\n", my_parameters[n].data.str);
        break;

      default:
        break;
    }
    
    free(elements[n]);
  }
  free(elements);

  return 0;
}