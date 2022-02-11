NAME = philo
CC = gcc
CFLAGS =  -Wall -Wextra -Werror -pthread
LIBFT = libft/libft.a
SRCS =  src/main.c src/philo.c src/eat.c src/utils.c src/utils2.c
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

#s:
#	$(CC) -g -fsanitize=thread $(CFLAGS) $(INLCLUDE) -o $(NAME) $(OBJS) $(LIBFT)
#leak: $(OBJS)
#	$(CC) $(CFLAGS) -D LEAKS=1 $(INCLUDE) -o $(NAME) $(OBJS) $(LIBFT)
#
#
#test: $(NAME)
#	./philo 5 800 500 500
#
#norm:
#	norminette src libft include | grep Error

.PHONY: all clean fclean re empty norm test s leak
