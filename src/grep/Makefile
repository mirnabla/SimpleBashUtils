CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all: s21_grep

s21_grep: clean
	$(CC) $(CFLAGS) *.c -o s21_grep

clang:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	rm -rf .clang-format

style_check:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	rm -rf .clang-format

clean:
	rm -rf s21_grep *.o

tests: s21_grep
	sh test_s21_grep.sh