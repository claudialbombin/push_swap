/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/22 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/22 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Brings the node at "index" (from the top) to the top of a,
** choosing whichever rotation direction needs fewer moves.
*/
static void	rotate_to_top(t_stack **a, int index, int size)
{
	if (index <= size - index)
	{
		while (index > 0)
		{
			ft_ra(a, 1);
			index--;
		}
	}
	else
	{
		index = size - index;
		while (index > 0)
		{
			ft_rra(a, 1);
			index--;
		}
	}
}

/*
** O(n^2) sort: n times, finds the current minimum of a,
** rotates it to the top and pushes it to b. The very last
** element left in a is automatically the maximum, so we stop
** at size 1 instead of moving it too. Finally, pushes
** everything back from b to a in the right order.
*/
void	ft_simple_sort(t_stack **a, t_stack **b)
{
	int	size;
	int	index;

	if (ft_is_sorted(*a))
		return ;
	size = ft_stack_size(*a);
	while (size > 1)
	{
		index = ft_min_index(*a);
		rotate_to_top(a, index, size);
		ft_pb(a, b, 1);
		size--;
	}
	while (*b)
		ft_pa(a, b, 1);
}
