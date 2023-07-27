#!/bin/sh
valgrind -v --leak-check=full --show-leak-kinds=all ./gnl get_next_line.c
