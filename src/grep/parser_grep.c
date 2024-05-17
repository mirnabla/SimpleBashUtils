#include "grep.h"

void options_parser(int argc, char *argv[], options *opt) {
  int opts = 0;
  while ((opts = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, 0)) != -1) {
    switch (opts) {
      case 'e':
        opt->e = 1;
        opt->flag_counter++;
        opt->flag_counter_e++;
        strcat(opt->pattern, optarg);
        strcat(opt->pattern, "|");
        break;
      case 'i':
        opt->i = 1;
        opt->flag_counter++;
        break;
      case 'v':
        opt->v = 1;
        opt->flag_counter++;
        break;
      case 'c':
        opt->c = 1;
        opt->flag_counter++;
        break;
      case 'l':
        opt->l = 1;
        opt->flag_counter++;
        break;
      case 'n':
        opt->n = 1;
        opt->flag_counter++;
        break;
      case 'h':
        opt->h = 1;
        opt->flag_counter++;
        break;
      case 's':
        opt->s = 1;
        opt->flag_counter++;
        break;
      case 'f':
        opt->f = 1;
        opt->flag_counter++;
        options_f(opt);
        break;
      case 'o':
        opt->o = 1;
        opt->flag_counter++;
        break;
      default:
        opt->error = 1;
        printf("usage: grep [-e:ivclnhsf:o] [pattern] [file ...]");
        break;
    }
  }
  options_f_e(argc, argv, opt);
}