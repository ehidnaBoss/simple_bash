#include "s21_cat.h"

void print_chr(int *current, int *previous, int b_flag, int n_flag, int s_flag,
               int t_flag, int v_flag, int e_flag, int *count_line_number,
               int *is_blank) {
  if (!(*current == '\n' && *previous == '\n' && s_flag && *is_blank)) {
    if (*previous == '\n' && *current == '\n')
      *is_blank = 1;
    else
      *is_blank = 0;

    if (b_flag && *previous == '\n' && *current != '\n') {
      fprintf(stdout, "%6d\t", *count_line_number);
      *count_line_number += 1;
    }

    if (n_flag && *previous == '\n') {
      fprintf(stdout, "%6d\t", *count_line_number);
      *count_line_number += 1;
    }

    if (t_flag && *current == '\t') {
      fprintf(stdout, "^");
      *current = '\t' + 64;
    }

    if (e_flag && *current == '\n') {
      if (b_flag && *previous == '\n') {
        fprintf(stdout, "      \t$");
      } else
        fprintf(stdout, "$");
    }
    if (v_flag) {
      if (*current > 127 && *current < 160) fprintf(stdout, "M-^");
      if ((*current < 32 && *current != '\n' && *current != '\t') ||
          *current == 127)
        fprintf(stdout, "^");
      if ((*current < 32 || (*current > 126 && *current < 160)) &&
          *current != '\n' && *current != '\t')
        *current = *current > 126 ? *current - 128 + 64 : *current + 64;
    }
    fprintf(stdout, "%c", *current);
  }
  *previous = *current;
}

void process_file(int b_flag, int n_flag, int s_flag, int t_flag, int v_flag,
                  int e_flag, char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("cat");
    return;
  }
  int current;
  int previous = '\n';
  int count_line_number = 1;
  int is_blank = 0;
  while ((current = fgetc(file)) != EOF) {
    print_chr(&current, &previous, b_flag, n_flag, s_flag, t_flag, v_flag,
              e_flag, &count_line_number, &is_blank);
  }

  fclose(file);
}

int main(int argc, char *argv[]) {
  int opt;
  int option_index = 0;
  int b_flag = 0, n_flag = 0, s_flag = 0, t_flag = 0, v_flag = 0, e_flag = 0;

  while ((opt = getopt_long(argc, argv, "+benstvET", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        b_flag = 1;
        break;
      case 'e':
        v_flag = 1;
        e_flag = 1;
        break;

      case 'n':
        n_flag = 1;
        break;
      case 's':
        s_flag = 1;
        break;
      case 't':
        v_flag = 1;
        t_flag = 1;
        break;

      case 'v':
        v_flag = 1;
        break;
    }
  }
  if (n_flag == 1 && b_flag == 1) {
    n_flag = 0;
  }
  for (int i = optind; i < argc; i++) {
    process_file(b_flag, n_flag, s_flag, t_flag, v_flag, e_flag, argv[i]);
  }

  return 0;
}
