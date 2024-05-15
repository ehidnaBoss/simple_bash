#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
echo "start"
FLAGS=(-b -e -n -s -t -v -besntv)

for flag in "${FLAGS[@]}"; do
    ./s21_cat "$flag" shlyapa.txt > s21_cat.txt
    cat "$flag" shlyapa.txt > cat.txt

    if diff -s s21_cat.txt cat.txt; then
        echo "${GREEN}Test passed: $flag${NC}"
    else
        echo "${RED}Test failed: $flag${NC}"
    fi

     rm s21_cat.txt cat.txt
done