/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/23 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/24 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Finds the node still in a with the smallest rank that falls
** inside [lower, upper], or NULL if the chunk is exhausted (or,
** with upper == INT_MAX, NULL once a itself is exhausted).
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
** Pushes every element of one chunk into b, ranks low to high,
** before moving on to the next chunk. Once every chunk has gone
** through, b ends up with the highest rank on top - ready to be
** unloaded straight into a.
*/
static void	sort_by_chunks(t_stack **a, t_stack **b, int chunk,
		t_bench *bench)
{
	int		lower;
	int		upper;
	t_stack	*node;

	lower = 0;
	while (find_min_in_range(*a, lower, INT_MAX))
	{
		upper = lower + chunk - 1;
		node = find_min_in_range(*a, lower, upper);
		while (node)
		{
			rotate_node_to_top(a, node, bench);
			ft_pb(a, b, 1, bench);
			node = find_min_in_range(*a, lower, upper);
		}
		lower += chunk;
	}
}

/*
** O(n * sqrt(n)) sort: splits the ranks into chunks of about
** sqrt(n) elements. Chunks are processed from lowest to highest
** rank and, inside a chunk, ranks are also pushed low to high.
** That leaves b sorted with the highest rank on top, which is
** exactly what's needed to unload it back into a in ascending
** order with straight pa calls.
*/
void	ft_medium_sort(t_stack **a, t_stack **b, t_bench *bench)
{
	int	size;
	int	chunk;

	if (ft_is_sorted(*a))
		return ;
	size = ft_stack_size(*a);
	assign_ranks(*a);
	chunk = chunk_length(size);
	sort_by_chunks(a, b, chunk, bench);
	while (*b)
		ft_pa(a, b, 1, bench);
}
