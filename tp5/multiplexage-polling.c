#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

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

  int fifo1_desc = open(argv[1], O_RDWR | O_NONBLOCK);
  int fifo2_desc = open(argv[2], O_RDWR | O_NONBLOCK);

  sigint_trigerred = 0;

  struct sigaction sa;
  sa.sa_handler  = sigint_handler;
  sa.sa_flags    = SA_RESETHAND;
  sa.sa_restorer = NULL;

  sigaction(SIGINT, &sa, NULL);

  char buffer[BUFFER_SIZE];

  while (!sigint_trigerred) {
    if (read(fifo1_desc, buffer, BUFFER_SIZE) > 0) printf("%s\n", buffer);
    if (read(fifo2_desc, buffer, BUFFER_SIZE) > 0) printf("%s\n", buffer);
  }

  return 0;
}