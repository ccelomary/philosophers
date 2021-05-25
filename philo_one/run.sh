#!/bin/bash
gcc -Wall -Wextra -Werror srcs/main.c srcs/ft_initialize_global.c srcs/ft_initialize_phiosopher.c \
srcs/ft_printers2.c srcs/ft_printers.c \
srcs/ft_timer.c srcs/string2number.c srcs/ft_checkers.c \
srcs/ft_child_thread.c srcs/ft_error_checker.c -lpthread -o f