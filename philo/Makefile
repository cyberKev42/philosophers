NAME = philo

FLAGS = -Wall -Wextra -Werror

SRCS = main.c init.c sim.c eat_s_t.c utils.c free.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	cc $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
