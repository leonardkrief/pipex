SRCS		=	srcs/pipex.c \
				srcs/t_infos.c \
				srcs/here_doc.c \

OBJS		=	${SRCS:.c=.o}
INCLUDE		=	-I include
LIBS		=	libft/libft.a
NAME		=	pipex
CC			=	cc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -g3

all:	${NAME}

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} ${LIBS} -c $< -o ${<:.c=.o}

libs:	
		make -C libft
		make clean -C libft

${NAME}:	libs
		${CC} ${CFLAGS} ${INCLUDE} ${SRCS} ${LIBS} -o ${NAME}

bonus:		${NAME}

clean:
		make clean -C libft/
		${RM} ${OBJS}

fclean:	clean
		make fclean -C libft/
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re
.SILENT:
