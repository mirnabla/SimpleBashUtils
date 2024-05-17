#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 10000

typedef struct options {
  int e, i, v, c, l, n, h, s, f, o, error;
  int flag_counter;
  int flag_counter_e;
  char pattern[BUF];
  char filestr[BUF];
} options;

void files_count(options *opt, int argc, int *files_counter);
void options_parser(int argc, char *argv[], options *opt);
int output(int argc, char *argv[], options *opt);
void options_f(options *opt);
void options_f_e(int argc, char *argv[], options *opt);
void options_o(options *opt, int matched_regular, regex_t regular,
               regmatch_t start);
void flag_l_c(char *argv[], options *opt, int counter, int files_counter);

#endif  // GREP_H