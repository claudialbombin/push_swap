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

/**
 * @brief Reads a single bit from an integer.
 *
 * Counts from the least significant bit (bit 0).
 *
 * @param value Integer to read the bit from.
 * @param bit Zero-based bit position to read.
 * @return The value of that bit, 0 or 1.
 */
static int	get_bit(int value, int bit)
{
	return ((value >> bit) & 1);
}

/**
 * @brief Computes how many bits are needed to represent every rank.
 *
 * Doubles a capacity counter until it covers "size" instead of using
 * log2 and floating point math.
 *
 * @param size Number of distinct ranks to cover (0 to size - 1).
 * @return Number of bits required.
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

/**
 * @brief Assigns each node its rank based on relative value order.
 *
 * Radix sort needs each value's rank (0 to n - 1) instead of its raw
 * value, since ranks are the smallest possible range of numbers to
 * look at bit by bit. The rank of a node is simply how many other
 * nodes hold a smaller value.
 *
 * @param a Stack whose nodes get their index field filled in.
 * @return void
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

/**
 * @brief Runs one radix-sort pass over a single bit position.
 *
 * Goes through every element once. If its bit is 1, it stays in a but
 * gets rotated to the bottom (out of the way for this pass). If its
 * bit is 0, it gets pushed to b. Afterwards, b is fully drained back
 * into a, which places the "0" group on top while keeping both groups
 * in their original relative order.
 *
 * @param a Pointer to the main stack.
 * @param b Pointer to the auxiliary stack, used as scratch space.
 * @param bit Zero-based bit position processed in this pass.
 * @param bench Optional operation counters, or NULL if unused.
 * @return void
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

/**
 * @brief Sorts stack a in O(n log n) using a radix sort.
 *
 * Assigns each element its rank, then does one pass per bit needed to
 * represent that rank, from least to most significant. Since the last
 * (most significant) bit pass has the strongest effect on final
 * position, the result ends up fully sorted ascending, smallest on top.
 *
 * @param a Pointer to the main stack to sort.
 * @param b Pointer to the auxiliary (initially empty) stack.
 * @param bench Optional operation counters, or NULL if unused.
 * @return void
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
