flags=-Wall -Werror -Wextra -std=c11


all: s21_grep

s21_grep:
	gcc $(flags) s21_grep.c -o s21_grep

clang:
	clang-format -i s21_grep.c s21_grep.h
	
test:
	sh stanislav_test_grep.sh

clean:
	rm -f s21_grep

rebuild: clean s21_grep
