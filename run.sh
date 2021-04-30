#!/bin/bash
gcc srcs/main.c srcs/ft_initialize_global.c srcs/ft_initialize_phiosopher.c \
srcs/ft_printers2.c srcs/ft_printers.c srcs/ft_timer.c srcs/string2number.c -lpthread -o f