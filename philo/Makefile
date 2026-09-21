# Makefile for philosophers

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SOURCES = main.c \
		initiate_general_data.c \
		initiate_mutexes.c \
		initiate_philosophers.c \
		philosophers.c \
		thinking_helpers.c \
		chopstick_helpers.c \
		first_meal_ifs.c \
		flexsleep.c \
		eat_sleep_think.c \
		helpers.c \
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

re:
	$(MAKE) fclean
	$(MAKE) all

# With re written like this, it is safe to use re -j (unlike "re: fclean all") and the compilation inside 'all' runs in
# parallel across all CPU cores which makes it much faster

.PHONY: all clean fclean re
