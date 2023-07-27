#!/bin/bash
#!make -C libft/ fclean && make -C libft/ re
gcc -g -o0 -o gnl -Wall -Wextra -Werror -D BUFFER_SIZE=$1 main.c get_next_line.c get_next_line_utils.c
echo "COMP GNL OK"
