CC:= cc
CFLAGS:= -Wall -Werror -Wextra
NAME:= philo_bonus

SRCS:= philo.c parse.c inits.c routines.c utils.c actions.c

OBJS:= $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

$(NAME_BONUS): $(OBJSB)
	$(CC) $(CFLAGS) $(OBJSB) -o $(NAME_BONUS)

debug: CFLAGS += -fsanitize=address -ggdb3
debug: all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -pthread

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all debug