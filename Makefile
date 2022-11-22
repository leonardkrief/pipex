SRCS		=	pipex.c \

OBJS		=	${SRCS:.c=.o}
INCLUDE		=	-I include
LIBS		=	libft/libft.a \
				ft_printf/libftprintf.a \
NAME		=	pipex
CC			=	cc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

libs:	${OBJS}
		make -C libft/
		make -C ft_printf/

${NAME}:	libs
			${CC} ${CFLAGS} ${INCLUDE} ${LIBS} ${SRCS} -o ${NAME}

all:	${NAME}

clean:
		make clean -C libft/
		make clean -C ft_printf/
		${RM} ${OBJS}

fclean:	clean
		make fclean -C libft/
		make fclean -C ft_printf/
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re
