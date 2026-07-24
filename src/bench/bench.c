/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/22 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/22 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	total_ops(t_bench *bench)
{
	return (bench->sa + bench->sb + bench->ss + bench->pa + bench->pb
		+ bench->ra + bench->rb + bench->rr + bench->rra + bench->rrb
		+ bench->rrr);
}

static void	print_line_swap_push(t_bench *bench)
{
	ft_put_str_fd("[bench] sa: ", 2);
	ft_put_nbr_fd(bench->sa, 2);
	ft_put_str_fd(" sb: ", 2);
	ft_put_nbr_fd(bench->sb, 2);
	ft_put_str_fd(" ss: ", 2);
	ft_put_nbr_fd(bench->ss, 2);
	ft_put_str_fd(" pa: ", 2);
	ft_put_nbr_fd(bench->pa, 2);
	ft_put_str_fd(" pb: ", 2);
	ft_put_nbr_fd(bench->pb, 2);
	ft_put_str_fd("\n", 2);
}

static void	print_line_rotate(t_bench *bench)
{
	ft_put_str_fd("[bench] ra: ", 2);
	ft_put_nbr_fd(bench->ra, 2);
	ft_put_str_fd(" rb: ", 2);
	ft_put_nbr_fd(bench->rb, 2);
	ft_put_str_fd(" rr: ", 2);
	ft_put_nbr_fd(bench->rr, 2);
	ft_put_str_fd(" rra: ", 2);
	ft_put_nbr_fd(bench->rra, 2);
	ft_put_str_fd(" rrb: ", 2);
	ft_put_nbr_fd(bench->rrb, 2);
	ft_put_str_fd(" rrr: ", 2);
	ft_put_nbr_fd(bench->rrr, 2);
	ft_put_str_fd("\n", 2);
}

/*
** Prints the full --bench report to stderr, matching the
** subject's example format. "strategy" comes in already built
** as one string (eg. "Adaptive / O(n^2)") because the exact
** label depends on which internal method got picked, and that
** decision is made in main.c, not here.
*/
void	ft_print_bench(double disorder, char *strategy, t_bench *bench)
{
	ft_put_str_fd("[bench] disorder: ", 2);
	ft_put_percent_fd(disorder, 2);
	ft_put_str_fd("\n[bench] strategy: ", 2);
	ft_put_str_fd(strategy, 2);
	ft_put_str_fd("\n[bench] total_ops: ", 2);
	ft_put_nbr_fd(total_ops(bench), 2);
	ft_put_str_fd("\n", 2);
	print_line_swap_push(bench);
	print_line_rotate(bench);
}
