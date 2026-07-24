/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/22 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/24 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Returns the value of a single bit (0 or 1) from an integer,
** counting from the least significant bit (bit 0).
*/
static int	get_bit(int value, int bit)
{
	return ((value >> bit) & 1);
}

/*
** Finds how many bits are needed to represent every rank from
** 0 to size - 1. Doubles a capacity counter until it covers
** "size" instead of using log2 and floating point math.
*/
static int	count_max_bits(int size)
{
	int	bits;
	int	capacity;

	bits = 0;
	capacity = 1;
	while (capacity < size)
	{
		capacity = capacity * 2;
		bits++;
	}
	return (bits);
}

/*
** Radix sort needs each value's rank (0 to n - 1) instead of
** its raw value, since ranks are the smallest possible range
** of numbers to look at bit by bit. The rank of a node is
** simply how many other nodes hold a smaller value.
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
** Goes through every element once. If its bit is 1, it stays
** in a but gets rotated to the bottom (out of the way for this
** pass). If its bit is 0, it gets pushed to b. Afterwards, b is
** fully drained back into a, which places the "0" group on top
** while keeping both groups in their original relative order.
*/
static void	do_bit_pass(t_stack **a, t_stack **b, int bit, t_bench *bench)
{
	int	i;
	int	size;

	size = ft_stack_size(*a);
	i = 0;
	while (i < size)
	{
		if (get_bit((*a)->index, bit) == 0)
			ft_pb(a, b, 1, bench);
		else
			ft_ra(a, 1, bench);
		i++;
	}
	while (*b)
		ft_pa(a, b, 1, bench);
}

/*
** O(n log n) sort: assigns each element its rank, then does
** one pass per bit needed to represent that rank, from least
** to most significant. Since the last (most significant) bit
** pass has the strongest effect on final position, the result
** ends up fully sorted ascending, smallest on top.
*/
void	ft_complex_sort(t_stack **a, t_stack **b, t_bench *bench)
{
	int	size;
	int	max_bits;
	int	bit;

	if (ft_is_sorted(*a))
		return ;
	size = ft_stack_size(*a);
	assign_indexes(*a);
	max_bits = count_max_bits(size);
	bit = 0;
	while (bit < max_bits)
	{
		do_bit_pass(a, b, bit, bench);
		bit++;
	}
}
