#include "grep.h"

int main(int argc, char *argv[]) {
  options opt = {0};
  options_parser(argc, argv, &opt);
  if (opt.error) return 1;
  while (optind < argc) {
    output(argc, argv, &opt);
    optind++;
  }
  return 0;
}