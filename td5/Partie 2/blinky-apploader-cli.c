#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char* argv[]) {
  int opt = 0;
  char* optional = NULL;

  struct option my_opts[] = {
    { .name = "tree",    .has_arg = 0, .flag = 0, .val = 't' },
    { .name = "config",  .has_arg = 0, .flag = 0, .val = 'f' },
    { .name = "reboot",  .has_arg = 0, .flag = 0, .val = 'r' },
    { .name = "set",     .has_arg = 0, .flag = 0, .val = 's' },
    { .name = "program", .has_arg = 1, .flag = 0, .val = 'p' },
    { .name = "color",   .has_arg = 2, .flag = 0, .val = 'c' },
    { .name = "jump",    .has_arg = 2, .flag = 0, .val = 'j' },
    { .name = 0,         .has_arg = 0, .flag = 0, .val =  0  } // last element must be zero
  };

  while ((opt = getopt_long(argc, argv, "", my_opts, NULL)) != -1) {
    switch (opt) {
    case 'c':
      optional = get_optarg(argc, argv);
      printf("Robot's color is:\t");
      if (optional) {
        for (size_t n = 0; optional[n]; n++) optional[n] = toupper(optional[n]);
        if      (strcmp(optional, "BLACK")   == 0) printf("\x1b[30m");
        else if (strcmp(optional, "RED")     == 0) printf("\x1b[31m");
        else if (strcmp(optional, "GREEN")   == 0) printf("\x1b[32m");
        else if (strcmp(optional, "BLUE")    == 0) printf("\x1b[34m");
        else if (strcmp(optional, "YELLOW")  == 0) printf("\x1b[93m");
        else if (strcmp(optional, "MAGENTA") == 0) printf("\x1b[95m");
        else if (strcmp(optional, "CYAN")    == 0) printf("\x1b[96m");

        printf("%s\x1b[0m\n", optional);
      } else printf("\x1b[30mBLACK\x1b[0m\n");
      break;
    
    case 't':
      printf("Creating the tree between robots");
      break;

    case 'f':
      printf("Display Robot's configuration:\n\tNAME:\tR2-D2\n\tTYPE:\tASTROMECH");
      break;
    
    case 's':
      char* isValid = strtok(NULL, "=");

      if (!isValid) {
        printf("\x1b[91mERROR: --set argument must be following this setup: \"--set option=value\"\x1b[0m\n");
        return 1;
      }
      else printf("Setting Robot's option:\t%s\n", optarg);
      break;

    case 'j':
      if (optarg != NULL) pritnf("Lauching App:\t%s");
      else if (optind <= argc - 1 && argv[optind][0] != '-') printf("Lauching App:\t%s\n", argv[optind]);
      else printf("Lauching App at 0x8010000\n")
      break;

    case 'r':
      printf("Rebooting Robot, please do not press shutdown while restarting...");
      break;

    case 'p':
      if (optarg[0] == '-') printf("\x1b[91mERROR: --program argument must be following this setup: \"--program option=value\"\x1b[0m\n");
      else printf("Sending program to Robot:\t%s\n", optarg);
      break;
    
    default:
      break;
    }
  }
}