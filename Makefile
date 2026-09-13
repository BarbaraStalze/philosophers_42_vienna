# Makefile for philosophers

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
SOURCES = main.c \
		initiate_general_data.c \
		initiate_mutexes.c \
		initiate_philosophers.c \
		cleanup.c

OBJFILES = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJFILES)

fclean:clean
	rm -f $(NAME)

re:fclean all

.PHONY: all clean fclean re debug
