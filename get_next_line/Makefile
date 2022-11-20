SRCS		=	get_next_line.c \
				get_next_line_utils.c \

OBJS		=	${SRCS:.c=.o}
INCLUDE		=	-I ../include
NAME		=	libftgnl.a
CC			=	cc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		ar rc ${NAME} ${OBJS}

bonus:	${NAME}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re
