#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
ptrn='he'
echo "start"
FLAGS=(-e -i -v -c -l -n -h -s -o -iv -in)

for flag in "${FLAGS[@]}"; do
    ./s21_grep "$flag" "$ptrn" salfetka.txt > s21_grep.txt
    grep "$flag" "$ptrn" salfetka.txt > grep.txt

    if diff -s s21_grep.txt grep.txt; then
        echo "${GREEN}Test passed: $flag${NC}"
    else
        echo "${RED}Test failed: $flag${NC}"
    fi

     rm s21_grep.txt grep.txt
done
