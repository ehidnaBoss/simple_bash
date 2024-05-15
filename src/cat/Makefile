flags=-Wall -Werror -Wextra -std=c11


all: s21_cat

s21_cat:
	gcc $(flags) s21_cat.c -o s21_cat
clang:
	clang-format -i s21_cat.c s21_cat.h
test:
	sh stanislav_test_cat.sh
clean:
	rm -f s21_cat

rebuild: clean s21_cat

