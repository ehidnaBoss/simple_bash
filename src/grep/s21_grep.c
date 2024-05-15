#include "s21_grep.h"

int main(int argc, char **argv) {
  arguments flag = argument_parser(argc, argv);
  output(flag, argc, argv);
  return 0;
}

void add_pattern(arguments *flag, char *pattern) {
  if (flag->len_pattern != 0) {
    strcat(flag->pattern + flag->len_pattern, "|");
    flag->len_pattern++;
  }
  flag->len_pattern +=
      sprintf(flag->pattern + flag->len_pattern, "(%s)", pattern);
}

void add_pat_from_file(arguments *flag, char *filepath) {
  FILE *f = fopen(filepath, "r");
  if (f == NULL) {
    if (!flag->s) perror(filepath);
    exit(1);
  }
  char *line = NULL;
  size_t memlen = 0;
  int symbol = getline(&line, &memlen, f);

  while (symbol != -1) {
    if (line[symbol - 1] == '\n') line[symbol - 1] = '\0';
    add_pattern(flag, line);
    symbol = getline(&line, &memlen, f);
  }
  free(line);

  fclose(f);
}

arguments argument_parser(int argc, char *argv[]) {
  arguments flag = {0};
  int opt = 0;
  for (; opt != -1; opt = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, 0)) {
    switch (opt) {
      case 'e':
        flag.e = 1;
        add_pattern(&flag, optarg);
        break;
      case 'i':
        flag.i = REG_ICASE;
        break;
      case 'v':
        flag.v = 1;
        break;
      case 'c':
        flag.c = 1;
        break;
      case 'l':
        flag.l = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 'h':
        flag.h = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 'f':
        flag.f = 1;
        add_pat_from_file(&flag, optarg);
        break;
      case 'o':
        flag.o = 1;
        break;
      case '?':
        exit(1);
        break;
    }
  }
  if (flag.len_pattern == 0) {
    add_pattern(&flag, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) flag.h = 1;
  return flag;
}

void output_line(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void print_match(arguments flag, regex_t *re, char *line, int line_count,
                 char *path) {
  regmatch_t math;
  int offset = 0;
  while (1) {
    int res = regexec(re, line + offset, 1, &math, 0);
    if (res != 0) {
      break;
    }
    if (!flag.h) printf("%s:", path);
    if (flag.n) printf("%d:", line_count);
    for (int i = math.rm_so; i < math.rm_eo; i++) {
      putchar(line[offset + i]);
    }
    putchar('\n');
    offset += math.rm_eo;
  }
}

void processFile(arguments flag, char *path, regex_t *reg) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    if (!flag.s) perror(path);
    return;
  }
  char *line = NULL;
  size_t memlen = 0;
  int symbol = 0;
  int line_count = 1;
  int c = 0;
  symbol = getline(&line, &memlen, f);
  while (symbol != -1) {
    int res = regexec(reg, line, 0, NULL, 0);
    if ((res == 0 && !flag.v) || (flag.v && res != 0)) {
      if (!flag.c && !flag.l) {
        if (!flag.h && !flag.o) printf("%s:", path);
        if (flag.n && !flag.o) printf("%d:", line_count);
        if (flag.o) {
          if (res == 0) print_match(flag, reg, line, line_count, path);
          if (res != 0 && !flag.h) printf("%s:", path);
          if (res != 0 && flag.n) printf("%d:", line_count);
          if (res != 0) output_line(line, symbol);
        } else
          output_line(line, symbol);
      }
      c++;
    }
    symbol = getline(&line, &memlen, f);
    line_count++;
  }
  free(line);
  if (flag.c && flag.l) {
    if (!flag.h) printf("%s:", path);
    if (c >= 1)
      printf("1\n");
    else
      printf("0\n");
  }
  if (flag.c && !flag.l) {
    if (!flag.h) printf("%s:", path);
    printf("%d\n", c);
  }
  if (flag.l && c > 0) printf("%s\n", path);
  fclose(f);
}

void output(arguments flag, int argc, char **argv) {
  regex_t re;
  int error = regcomp(&re, flag.pattern, REG_EXTENDED | flag.i);
  if (error) perror("Error");
  for (int i = optind; i < argc; i++) {
    processFile(flag, argv[i], &re);
  }
  regfree(&re);
}
