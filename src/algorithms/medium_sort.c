/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/23 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/23 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Same rank trick as complex_sort: gives every node its rank
** (0 to size - 1) instead of its raw value, so ranks can be
** grouped into chunks.
*/
static void	assign_indexes(t_stack *a)
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
static int	chunk_length(int size)
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
static void	rotate_to_top(t_stack **a, t_stack *node)
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
			ft_ra(a, 1);
	}
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			ft_rra(a, 1);
	}
}

/*
** Finds the node still in a with the smallest rank that falls
** inside [lower, upper], or NULL if the chunk is exhausted.
*/
static t_stack	*find_min_in_range(t_stack *a, int lower, int upper)
{
	t_stack	*best;

	best = NULL;
	while (a)
	{
		if (a->index >= lower && a->index <= upper
			&& (!best || a->index < best->index))
			best = a;
		a = a->next;
	}
	return (best);
}

/*
** O(n * sqrt(n)) sort: splits the ranks into chunks of about
** sqrt(n) elements. Chunks are processed from lowest to highest
** rank and, inside a chunk, ranks are also pushed low to high.
** That leaves b sorted with the highest rank on top, which is
** exactly what's needed to unload it back into a in ascending
** order with straight pa calls.
*/
void	ft_medium_sort(t_stack **a, t_stack **b)
{
	int		size;
	int		chunk;
	int		lower;
	int		upper;
	t_stack	*node;

	if (ft_is_sorted(*a))
		return ;
	size = ft_stack_size(*a);
	assign_indexes(*a);
	chunk = chunk_length(size);
	lower = 0;
	while (lower < size)
	{
		upper = lower + chunk - 1;
		if (upper > size - 1)
			upper = size - 1;
		node = find_min_in_range(*a, lower, upper);
		while (node)
		{
			rotate_to_top(a, node);
			ft_pb(a, b, 1);
			node = find_min_in_range(*a, lower, upper);
		}
		lower += chunk;
	}
	while (*b)
		ft_pa(a, b, 1);
}
