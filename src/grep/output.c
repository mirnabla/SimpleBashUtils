#include "grep.h"

int output(int argc, char *argv[], options *opt) {
  int files_counter, counter = 0, number_str = 0, matched_regular = 0,
                     opt_i = REG_EXTENDED;
  files_count(opt, argc, &files_counter);
  FILE *f = fopen(argv[optind], "r");
  if (f == NULL) {
    if (!opt->s) {
      fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
    }
    return 1;
  }
  regex_t regular;
  regmatch_t start;
  if (opt->i) opt_i = REG_EXTENDED | REG_ICASE;
  regcomp(&regular, opt->pattern, opt_i);
  while (fgets(opt->filestr, BUF, f) != NULL) {
    number_str++;
    matched_regular = regexec(&regular, opt->filestr, 1, &start, 0);
    if (opt->v) matched_regular = !matched_regular;
    if (!matched_regular) {
      if (files_counter > 1 && !opt->h && !opt->l && !opt->c) {
        printf("%s:", argv[optind]);
      }
      if (opt->o) options_o(opt, matched_regular, regular, start);
      if (opt->n) {
        printf("%d:%s", number_str, opt->filestr);
      }
      counter++;
      int stringlen = strlen(opt->filestr);
      if (!opt->l && !opt->c && !opt->n && !opt->o) {
        printf("%s", opt->filestr);
        if (opt->filestr[stringlen - 1] != '\n') {
          printf("\n");
        }
      }
    }
  }
  flag_l_c(argv, opt, counter, files_counter);
  fclose(f);
  regfree(&regular);
  return 0;
}

void flag_l_c(char *argv[], options *opt, int counter, int files_counter) {
  if (opt->l && counter >= 1) {
    printf("%s\n", argv[optind]);
  }
  if (opt->c && files_counter == 1) {
    printf("%d\n", counter);
  } else if (opt->c && files_counter > 1) {
    printf("%s:%d\n", argv[optind], counter);
  }
}