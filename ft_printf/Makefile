#	Sources
SRCS		= 	srcs/ft_printf.c \
				srcs/ft_printf_u.c \
				srcs/ft_put.c \
				srcs/ft_printf_c.c \
				srcs/ft_printf_p.c \
				srcs/ft_printf_xbig.c \
				srcs/ft_t_seq.c \
				srcs/ft_printf_d.c \
				srcs/ft_printf_s.c \
				srcs/ft_printf_x.c \

OBJS		= ${SRCS:.c=.o}
INCLUDE		= -I includes/
NAME		= libftprintf.a
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

all:	${NAME}

${NAME}:	${OBJS}
		make -C libft/
		cp libft/libft.a libftprintf.a
		ar rc ${NAME} ${OBJS}

bonus:		$(NAME)

clean:
		make clean -C libft/
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		make fclean -C libft/

re:		fclean all

.PHONY: all clean fclean re
