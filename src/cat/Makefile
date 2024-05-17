CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all: s21_cat

s21_cat: clean
	$(CC) $(CFLAGS) *.c -o s21_cat

clang:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	rm -rf .clang-format

style_check:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	rm -rf .clang-format

clean:
	rm -rf s21_cat *.o

tests: s21_cat
	sh test_s21_cat.sh