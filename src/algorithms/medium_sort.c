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

/**
 * @brief Finds the node with the smallest rank inside a range.
 *
 * Searches only among ranks in [lower, upper], or, with
 * upper == INT_MAX, among every remaining node in a.
 *
 * @param a Stack to search.
 * @param lower Lowest rank accepted (inclusive).
 * @param upper Highest rank accepted (inclusive).
 * @return The matching node, or NULL if the chunk is exhausted.
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

/**
 * @brief Pushes every chunk of a into b, ordered low rank to high.
 *
 * Pushes every element of one chunk into b, ranks low to high, before
 * moving on to the next chunk. Once every chunk has gone through, b
 * ends up with the highest rank on top - ready to be unloaded straight
 * into a.
 *
 * @param a Pointer to the main stack.
 * @param b Pointer to the auxiliary (initially empty) stack.
 * @param chunk Size of each chunk of ranks.
 * @param bench Optional operation counters, or NULL if unused.
 * @return void
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

/**
 * @brief Sorts stack a in O(n * sqrt(n)) using a chunk-based sort.
 *
 * Splits the ranks into chunks of about sqrt(n) elements. Chunks are
 * processed from lowest to highest rank and, inside a chunk, ranks
 * are also pushed low to high. That leaves b sorted with the highest
 * rank on top, which is exactly what's needed to unload it back into
 * a in ascending order with straight pa calls.
 *
 * @param a Pointer to the main stack to sort.
 * @param b Pointer to the auxiliary (initially empty) stack.
 * @param bench Optional operation counters, or NULL if unused.
 * @return void
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
