/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonardkrief <leonardkrief@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:04:43 by lkrief            #+#    #+#             */
/*   Updated: 2022/09/30 15:00:16 by leonardkrie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_seq
{
	int	n;
	int	minus;
	int	zero;
	int	dot;
	int	n_dot;
	int	hash;
	int	space;
	int	plus;
	int	len;
}t_seq;

//libft
int		ft_atoi(const char *str);
int		ft_belongs(char s1, char const *set);
int		ft_isprint(int c);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlen(const char *s);

//ft_printf_c.c
int		ft_put_c(char c);
int		ft_printf_c(const char *str, int i, va_list *argptr);

//ft_printf_d.c
int		ft_put_d(long d, int n, int plus, int space);
void	ft_seq_d(t_seq *s, long d);
int		ft_printf_d(const char *str, int i, va_list *argptr);

//ft_printf_p.c
int		ft_len_p(void *p);
int		ft_put_p(void *p);
int		ft_printf_p(const char *str, int i, va_list *argptr);

//ft_printf_s.c
int		ft_put_s(char *s, int n);
int		ft_atoi_after_dot(const char *str);
int		ft_printf_s_minus(const char *str, int i, char *s);
int		ft_printf_s_nominus(const char *str, int i, char *s);
int		ft_printf_s(const char *str, int i, va_list *argptr);

//ft_printf_u.c
void	ft_putunbr_fd(unsigned int u, int fd);
int		ft_put_u(unsigned int u);
int		ft_printf_u(const char *str, int i, va_list *argptr);

//ft_printf_x.c
int		ft_put_x(long d, int n, int plus, int space);
void	ft_seq_x(t_seq *s, long d);
int		ft_printf_x(const char *str, int i, va_list *argptr);

//ft_printf_xbig.c
int		ft_put_xbig(long d, int n, int plus, int space);
int		ft_printf_xbig(const char *str, int i, va_list *argptr);

//ft_printf.c
char	ft_argtype(const char *str, int i);
int		ft_printfmod(const char *str, int i, va_list *argptr);
void	ft_printf_aux(const char *str, int *i, int *count_print);
int		ft_printf(const char *str, ...);

//put.c
int		ft_len_base(long c, int len_base);
void	ft_put_positive_base(long d, char *base, int len_base);
int		ft_put_base(long d, char *base, int len_base, int n);
void	ft_putullbase_fd(unsigned long long z, char *base, int lenbas, int fd);
int		ft_printf_percent(void);

//ft_t_seq.c
void	ft_minus_seq(t_seq *s);
void	ft_init_seq(const char *str, int *i, char *set, t_seq *s);
void	ft_print_seq(t_seq s);

#endif
