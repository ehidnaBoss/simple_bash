#ifndef S21_GREP_H
#define S21_GREP_H
#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int e, i, v, c, l, n, h, s, f, o;
  char pattern[15000];
  int len_pattern;
} arguments;

void add_pattern(arguments *flag, char *pattern);
void add_pat_from_file(arguments *flag, char *filepath);
arguments argument_parser(int argc, char *argv[]);
void output_line(char *line, int n);
void print_match(arguments flag, regex_t *re, char *line, int line_count,
                 char *path);
void processFile(arguments flag, char *path, regex_t *reg);
void output(arguments flag, int argc, char **argv);

#endif
