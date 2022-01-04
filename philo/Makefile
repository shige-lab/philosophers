NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS =  
OBJS = $(SRCS:%.c=%.o)
COBJS = $(CSRCS:%.c=%.o)
INCLUDE = -I include/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
clean:
	$(RM) $(OBJS)
	$(RM) $(COBJS)
	make clean -C libft
fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(CHECKER)
re: fclean all
test: $(NAME)
	$(CC) $(CFLAGS) $(NAME) main.c &&./a.out
t: $(NAME)
	$(CC) $(CFLAGS) $(NAME) main.c
test-: $(NAME)
	$(CC) $(NAME) main.c &&./a.out

.PHONY: all clean fclean re