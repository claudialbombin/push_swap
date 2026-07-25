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

/**
 * @brief Assigns each node its rank based on relative value order.
 *
 * Same rank trick as complex_sort: gives every node its rank (0 to
 * size - 1) instead of its raw value, so ranks can be grouped into
 * chunks.
 *
 * @param a Stack whose nodes get their index field filled in.
 * @return void
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

/**
 * @brief Computes the chunk length used to split ranks for medium sort.
 *
 * Smallest chunk length whose square covers "size", so the stack ends
 * up split into roughly sqrt(size) chunks.
 *
 * @param size Number of elements in the stack.
 * @return Chunk length to use.
 */
int	chunk_length(int size)
{
	int	chunk;

	chunk = 1;
	while (chunk * chunk < size)
		chunk++;
	return (chunk);
}

/**
 * @brief Rotates a stack until a given node reaches the top.
 *
 * Picks whichever direction (ra or rra) needs fewer moves.
 *
 * @param a Pointer to the stack to rotate.
 * @param node Node to bring to the top; must belong to *a.
 * @param bench Optional operation counters, or NULL if unused.
 * @return void
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
