#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const struct option long_options[] = {{"number-nonblank", no_argument, 0, 'b'},
                                      {"E", no_argument, 0, 'e'},
                                      {"number", no_argument, 0, 'n'},
                                      {"squeeze-blank", no_argument, 0, 's'},
                                      {"T", no_argument, 0, 't'},
                                      {"show-nonprinting", no_argument, 0, 'v'},
                                      {0, 0, 0, 0}};

void print_chr(int *current, int *previous, int b_flag, int n_flag, int s_flag,
               int t_flag, int v_flag, int e_flag, int *count_line_number,
               int *is_blank);

void process_file(int b_flag, int n_flag, int s_flag, int t_flag, int v_flag,
                  int e_flag, char *filename);

#endif
