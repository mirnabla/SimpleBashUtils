#include "cat.h"

struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                {"snow-ends", 0, 0, 'E'},
                                {"number", 0, 0, 'n'},
                                {"squeeze-blank", 0, 0, 's'},
                                {"snow-tabs", 0, 0, 'T'},
                                {"non-printing", 0, 0, 'v'},
                                {0, 0, 0, 0}};

void options_parser(int argc, char *argv[], options *opt) {
  int opts = 0;
  while ((opts = getopt_long(argc, argv, "+beEnstTv", long_options, 0)) != -1) {
    switch (opts) {
      case 'b':
        opt->b = 1;
        break;
      case 'e':
        opt->E = 1;
        opt->v = 1;
        break;
      case 'E':
        opt->E = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 's':
        opt->s = 1;
        break;
      case 't':
        opt->T = 1;
        opt->v = 1;
        break;
      case 'T':
        opt->T = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      default:
        opt->error = 1;
        printf("usage: cat [-beEnstTv] [file ...]");
        break;
    }
  }
  if (opt->b) opt->n = 0;
}