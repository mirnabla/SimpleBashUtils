#ifndef CAT_H
#define CAT_H

#define _GNU_SOURCE

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct options {
  int b, E, n, s, T, v, error;
} options;

void options_parser(int argc, char *argv[], options *opt);
void output(options *opt, int argc, char *argv[]);

#endif  // CAT_H