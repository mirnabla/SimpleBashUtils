#include "grep.h"

void files_count(options *opt, int argc, int *files_counter) {
  if (opt->e) {
    *files_counter = (argc) - (opt->flag_counter_e + (opt->flag_counter_e + 1));
  } else
    *files_counter = argc - opt->flag_counter - 2;
}

void options_f(options *opt) {
  FILE *f = fopen(optarg, "r");
  if (f != NULL) {
    while (fgets(opt->filestr, BUF, f) != NULL) {
      if (opt->filestr[strlen(opt->filestr) - 1] == '\n' &&
          strlen(opt->filestr) != '\0') {
        opt->filestr[strlen(opt->filestr) - 1] = '\0';
      }
      strcat(opt->pattern, opt->filestr);
      strcat(opt->pattern, "|");
    }
  } else {
    fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
  }
  fclose(f);
}

void options_f_e(int argc, char *argv[], options *opt) {
  if (!opt->e && !opt->f) {
    if (optind < argc) {
      strcat(opt->pattern, argv[optind]);
    }
    optind++;
  }
  if (opt->e || opt->f) {
    opt->pattern[strlen(opt->pattern) - 1] = '\0';
  }
}

void options_o(options *opt, int matched_regular, regex_t regular,
               regmatch_t start) {
  if (!matched_regular && opt->o && !opt->l && !opt->c) {
    char *pointer = opt->filestr;
    while ((regexec(&regular, pointer, 1, &start, 0) == 0)) {
      printf("%.*s\n", (int)(start.rm_eo - start.rm_so), pointer + start.rm_so);
      pointer += start.rm_eo;
    }
  }
}