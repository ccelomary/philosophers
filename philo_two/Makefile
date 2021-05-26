NAME = philo_two
SRCS = srcs/main.c srcs/ft_initialize_global.c srcs/ft_initialize_phiosopher.c \
	srcs/ft_printers2.c srcs/ft_printers.c \
	srcs/ft_timer.c srcs/string2number.c srcs/ft_checkers.c \
	srcs/ft_child_thread.c srcs/ft_error_checker.c

OBJECTS = srcs/main.o srcs/ft_initialize_global.o srcs/ft_initialize_phiosopher.o \
	srcs/ft_printers2.o srcs/ft_printers.o \
	srcs/ft_timer.o srcs/string2number.o srcs/ft_checkers.o \
	srcs/ft_child_thread.o srcs/ft_error_checker.o
FLAGS = -Wall -Wextra -Werror
LIBRARIES =  -lpthread

all: $(NAME)
$(NAME):
	@gcc $(FLAGS) $(SRCS) $(LIBRARIES) -o $(NAME)

clean:
	@rm -f $(OBJECTS)
fclean: clean
	@rm -f $(NAME)
re: fclean all
