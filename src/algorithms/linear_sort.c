/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/23 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/24 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Walks "index" nodes forward from a and returns where that
** lands.
*/
static t_stack	*node_at(t_stack *a, int index)
{
	while (index-- > 0)
		a = a->next;
	return (a);
}

/*
** A stack whose disorder index is this low is, in practice,
** either already sorted or the sorted sequence rotated by some
** offset (eg. the last k values moved in front of the rest).
** Walking once from the minimum all the way back around to it
** must find every value strictly increasing - if it doesn't,
** the stack isn't a pure rotation.
*/
static int	is_rotated_sorted(t_stack *a, int min_index, int size)
{
	t_stack	*current;
	int		i;
	int		prev;

	if (size <= 1)
		return (1);
	current = node_at(a, min_index);
	prev = current->value;
	i = 1;
	while (i < size)
	{
		current = current->next;
		if (!current)
			current = a;
		if (current->value < prev)
			return (0);
		prev = current->value;
		i++;
	}
	return (1);
}

static void	rotate_min_to_top(t_stack **a, int min_index, int size,
		t_bench *bench)
{
	if (min_index <= size - min_index)
	{
		while (min_index-- > 0)
			ft_ra(a, 1, bench);
	}
	else
	{
		min_index = size - min_index;
		while (min_index-- > 0)
			ft_rra(a, 1, bench);
	}
}

/*
** O(n) sort for the low-disorder regime (disorder < 0.2): find
** the minimum (O(n)) and rotate it to the top the short way
** (O(n)) - if the stack really was just a rotated sorted
** sequence, that alone leaves it fully sorted. A true O(n)
** comparison sort can't exist for every permutation in this
** regime (disorder only bounds how many inversions there are,
** not the stack's shape), so as a correctness safety net, the
** rare low-disorder stack that isn't a pure rotation falls back
** to ft_complex_sort - that path is no longer O(n), but it never
** produces a wrong result.
*/
void	ft_linear_sort(t_stack **a, t_stack **b, t_bench *bench)
{
	int	size;
	int	min_index;

	if (ft_is_sorted(*a))
		return ;
	size = ft_stack_size(*a);
	min_index = ft_min_index(*a);
	if (!is_rotated_sorted(*a, min_index, size))
	{
		ft_complex_sort(a, b, bench);
		return ;
	}
	rotate_min_to_top(a, min_index, size, bench);
}
