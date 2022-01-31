NAME = philo
CC = gcc
CFLAGS = -g -fsanitize=thread  #-Wall -Wextra -Werror
LIBFT = libft/libft.a
SRCS =  src/main.c src/utils.c src/eat.c src/philo.c src/debug.c
OBJS = $(SRCS:%.c=%.o)
INCLUDE = -I include/

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT): empty
	make -C libft

empty:

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
clean:
	$(RM) $(OBJS)
	make clean -C libft
fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
re: fclean all

test: $(NAME)
	./philo
t: $(NAME)
	$(CC) $(CFLAGS) $(NAME) main.c
test-: $(NAME)
	$(CC) $(NAME) main.c &&./a.out

.PHONY: all clean fclean re empty
