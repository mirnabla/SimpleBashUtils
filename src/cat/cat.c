#include "cat.h"

int main(int argc, char *argv[]) {
  options opt = {0};
  options_parser(argc, argv, &opt);
  if (!opt.error)
    while (optind < argc) {
      output(&opt, argc, argv);
      optind++;
    }
  return 0;
}