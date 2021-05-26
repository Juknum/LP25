#include <stdio.h>
#include <signal.h>
#include <string.h>

#define BUFFER_SIZE 128
volatile sig_atomic_t sigint_triggered;

void sigint_handler(int signal) {
  sigint_triggered = 1;
}

int main(int argc, char* argv[]) {
  FILE* f = fopen("./dump.txt", "w");
  if (!f) return 1;
  
  sigint_triggered = 0;

  struct sigaction sa;
  sa.sa_handler = sigint_handler;
  sa.sa_flags = SA_RESETHAND;
  sa.sa_restorer = NULL;

  sigaction(SIGINT, &sa, NULL);

  char buffer[BUFFER_SIZE];
  do {
    fgets(buffer, BUFFER_SIZE, stdin);

    if (strcmp(buffer, "END\n") == 0) raise(SIGINT);
    else if (!sigint_triggered) fprintf(f, "%.*s", BUFFER_SIZE, buffer);
    
  } while (!sigint_triggered);

  fclose(f);
  return 0;
}