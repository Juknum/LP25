#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define BUFFER_SIZE 128

volatile sig_atomic_t sigint_trigerred;

void sigint_handler(int signal) {
  sigint_trigerred = 1;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Enter a file path please!\n");
    return 1;
  }

  FILE* f = fopen(argv[1], "r");
  if (!f) return 1;

  FILE* f2 = fopen(argv[2], "r");
  if (!f2) return 1;

  int desc  = fileno(f);
  int desc2 = fileno(f2);

  sigint_trigerred = 0;

  struct sigaction sa;
  sa.sa_handler  = sigint_handler;
  sa.sa_flags    = SA_RESETHAND;
  sa.sa_restorer = NULL;

  sigaction(SIGINT, &sa, NULL);

  char buffer[BUFFER_SIZE];

  while (!sigint_trigerred) {
    read(desc, buffer, BUFFER_SIZE);
    printf("%s\n", buffer);
    read(desc2, buffer, BUFFER_SIZE);
    printf("%s\n", buffer);
  }

  fclose(f); fclose(f2);
  return 0;
}