/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/22 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/22 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_len(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_put_str_fd(char *s, int fd)
{
	write(fd, s, ft_len(s));
}

void	ft_put_nbr_fd(int n, int fd)
{
	char	buf[12];
	int		len;

	len = 0;
	if (n == 0)
		buf[len++] = '0';
	while (n > 0)
	{
		buf[len++] = '0' + (n % 10);
		n = n / 10;
	}
	while (len > 0)
		write(fd, &buf[--len], 1);
}

void	ft_put_percent_fd(double value, int fd)
{
	int	scaled;

	scaled = (int)(value * 10000 + 0.5);
	ft_put_nbr_fd(scaled / 100, fd);
	ft_put_str_fd(".", fd);
	if (scaled % 100 < 10)
		ft_put_str_fd("0", fd);
	ft_put_nbr_fd(scaled % 100, fd);
	ft_put_str_fd("%", fd);
}

/*
** No memset allowed, so every counter gets zeroed by hand.
** Called once in main before any sorting happens.
*/
void	ft_bench_init(t_bench *bench)
{
	bench->sa = 0;
	bench->sb = 0;
	bench->ss = 0;
	bench->pa = 0;
	bench->pb = 0;
	bench->ra = 0;
	bench->rb = 0;
	bench->rr = 0;
	bench->rra = 0;
	bench->rrb = 0;
	bench->rrr = 0;
}
