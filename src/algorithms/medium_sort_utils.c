/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/24 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/24 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Same rank trick as complex_sort: gives every node its rank
** (0 to size - 1) instead of its raw value, so ranks can be
** grouped into chunks.
*/
void	assign_ranks(t_stack *a)
{
	t_stack	*current;
	t_stack	*other;
	int		count;

	current = a;
	while (current)
	{
		other = a;
		count = 0;
		while (other)
		{
			if (other->value < current->value)
				count++;
			other = other->next;
		}
		current->index = count;
		current = current->next;
	}
}

/*
** Smallest chunk length whose square covers "size", so the
** stack ends up split into roughly sqrt(size) chunks.
*/
int	chunk_length(int size)
{
	int	chunk;

	chunk = 1;
	while (chunk * chunk < size)
		chunk++;
	return (chunk);
}

/*
** Rotates a until "node" reaches the top, picking whichever
** direction (ra or rra) needs fewer moves.
*/
void	rotate_node_to_top(t_stack **a, t_stack *node, t_bench *bench)
{
	t_stack	*current;
	int		pos;
	int		size;

	pos = 0;
	current = *a;
	while (current != node)
	{
		pos++;
		current = current->next;
	}
	size = ft_stack_size(*a);
	if (pos <= size - pos)
	{
		while (pos-- > 0)
			ft_ra(a, 1, bench);
	}
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			ft_rra(a, 1, bench);
	}
}
