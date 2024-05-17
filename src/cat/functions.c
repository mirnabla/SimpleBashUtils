#include "cat.h"

char v_output(char ch) {
  if (ch == '\n' || ch == '\t') return ch;
  if (ch < 0) {
    printf("M-");
    ch = ch & 0x7F;
  }
  if (ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void work_flags(options *opt, char **line, int *line_count, int read) {
  if (opt->n || opt->b) {
    if (opt->b && (*line)[0] != '\n') {
      printf("%6d\t", (*line_count)++);
    } else if (opt->n) {
      printf("%6d\t", (*line_count)++);
    }
  }
  for (int i = 0; i < read; i++) {
    if (opt->T && (*line)[i] == '\t') {
      printf("^I");
    } else {
      if (opt->E && (*line)[i] == '\n') {
        printf("$");
      }
      if (opt->v) {
        (*line)[i] = v_output((*line)[i]);
      }
      putchar((*line)[i]);
    }
  }
}

void output(options *opt, int argc, char *argv[]) {
  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[optind], "r");
    if (f == NULL) {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
      return;
    }
    char *line = {0};
    size_t memline = 0;
    int read = 0;

    int line_count = 1;
    int empty_count = 0;
    read = getline(&line, &memline, f);
    while (read != -1) {
      if (line[0] == '\n') {
        empty_count++;
      } else {
        empty_count = 0;
      }
      if ((opt->s && empty_count > 1) == 0) {
        work_flags(opt, &line, &line_count, read);
      }
      read = getline(&line, &memline, f);
    }

    free(line);
    fclose(f);
  }
}