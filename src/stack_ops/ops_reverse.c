/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_reverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/22 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/22 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Reverse rotates stack a downwards: the last element becomes
** the first one, everything else shifts down by one position.
** Does nothing if the stack has 0 or 1 elements.
*/
void	ft_rra(t_stack **a, int print)
{
	t_stack	*current;
	t_stack	*prev;

	if (!*a || !(*a)->next)
		return ;
	current = *a;
	prev = NULL;
	while (current->next)
	{
		prev = current;
		current = current->next;
	}
	prev->next = NULL;
	current->next = *a;
	*a = current;
	if (print)
		write(1, "rra\n", 4);
}

/*
** Same as ft_rra but for stack b.
*/
void	ft_rrb(t_stack **b, int print)
{
	t_stack	*current;
	t_stack	*prev;

	if (!*b || !(*b)->next)
		return ;
	current = *b;
	prev = NULL;
	while (current->next)
	{
		prev = current;
		current = current->next;
	}
	prev->next = NULL;
	current->next = *b;
	*b = current;
	if (print)
		write(1, "rrb\n", 4);
}

/*
** rrr does rra y rrb at the same time, printing just one line.
*/
void	ft_rrr(t_stack **a, t_stack **b, int print)
{
	ft_rra(a, 0);
	ft_rrb(b, 0);
	if (print)
		write(1, "rrr\n", 4);
}
