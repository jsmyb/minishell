NAME = minishell
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -L/usr/include -lreadline

all: ${NAME}

${NAME} : ${OBJS}
		@$(MAKE) -C ./libft
		@${CC} ${OBJS} ${CFLAGS} ./libft/libft.a -o ${NAME}

clean :
	@rm -rf ${OBJS}
	@$(MAKE) -C libft fclean

fclean : clean
	@rm -rf ${NAME}

re : fclean all

.PHONY : all clean fclean re .c.o
