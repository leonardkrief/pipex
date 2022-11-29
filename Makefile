SRCS		=	srcs/water.c \
				srcs/bread.c \
				srcs/pipex.c \

OBJS		= $(SRCS:.c=.o)
DEPS		= $(SRCS:.c=.d)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3
INCLUDE		=	-I include
PIPEX		=	pipex
LIBS		=	libft/libft.a
RM			=	rm -rf

all:	${PIPEX}

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${PIPEX}:	${OBJS}
			make -C libft
			${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${PIPEX}

bonus:	${PIPEX}

clean:
		${RM} ${OBJS}
		${RM} ${DEPS}

fclean:	clean
		${RM} ${PIPEX}
		make fclean -C libft/

re:		fclean all

-include : ${DEPS}

.PHONY: all clean fclean re
.SILENT:
