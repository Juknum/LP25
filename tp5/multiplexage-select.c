#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/select.h>

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

  int fifo1_desc = fileno(f);
  int fifo2_desc = fileno(f2);

  sigint_trigerred = 0;

  struct sigaction sa;
  sa.sa_handler  = sigint_handler;
  sa.sa_flags    = SA_RESETHAND;
  sa.sa_restorer = NULL;

  sigaction(SIGINT, &sa, NULL);

  char buffer[BUFFER_SIZE];

  fd_set read_fds;

  while (!sigint_trigerred) {
    FD_ZERO(&read_fds);
    FD_SET(fifo1_desc, &read_fds);
    FD_SET(fifo2_desc, &read_fds);

    int max_fd = fifo1_desc > fifo2_desc ? fifo1_desc : fifo2_desc;
    struct timeval select_timeout = { .tv_sec = 1, .tv_usec = 0 };
    int select_result = select(max_fd + 1, &read_fs, NULL, NULL, &select_timeout);

    if (select_result == -1) break;
    else if (select_result != 0) {
      if (FD_ISSET(fifo1_desc, &read_fs))              // If FD has data available
        if (read(fifo1_desc, buffer, BUFFER_SIZE) > 0) // Try to read
          printf("%s", buffer);                        // You shall add a proper '\0' before printing since read doesn't do it

      if (FD_ISSET(fifo2_desc, &read_fds))
        if (read(fifo2_desc, buffer, BUFFER_SIZE) > 0)
          printf("%s", buffer);
    }
  }

  fclose(f); fclose(f2);
  return 0;
}