/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudialbombin <claudialbombin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 12:07:21 by claudialbom       #+#    #+#             */
/*   Updated: 2026/07/24 12:08:07 by claudialbom      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief Rotates a stack upwards by one position.
 *
 * The first element becomes the last one, everything else shifts up
 * by one position. Caller must already have checked the stack has at
 * least 2 elements.
 *
 * @param s Pointer to the stack to rotate.
 * @return void
 */
static void	rotate_up(t_stack **s)
{
	t_stack	*first;
	t_stack	*last;

	first = *s;
	*s = (*s)->next;
	last = *s;
	while (last->next)
		last = last->next;
	last->next = first;
	first->next = NULL;
}

/**
 * @brief Rotates stack a upwards by one position.
 *
 * Does nothing if a has fewer than 2 elements.
 *
 * @param a Pointer to the stack to rotate.
 * @param print 1 to print "ra\n" to stdout, 0 to stay silent.
 * @param bench Optional operation counter, or NULL if unused.
 * @return void
 */
void	ft_ra(t_stack **a, int print, t_bench *bench)
{
	if (!*a || !(*a)->next)
		return ;
	rotate_up(a);
	if (bench)
		bench->ra++;
	if (print)
		write(1, "ra\n", 3);
}

/**
 * @brief Rotates stack b upwards by one position.
 *
 * Does nothing if b has fewer than 2 elements.
 *
 * @param b Pointer to the stack to rotate.
 * @param print 1 to print "rb\n" to stdout, 0 to stay silent.
 * @param bench Optional operation counter, or NULL if unused.
 * @return void
 */
void	ft_rb(t_stack **b, int print, t_bench *bench)
{
	if (!*b || !(*b)->next)
		return ;
	rotate_up(b);
	if (bench)
		bench->rb++;
	if (print)
		write(1, "rb\n", 3);
}

/**
 * @brief Rotates both stacks a and b upwards at the same time.
 *
 * rr does ra and rb at the same time, printing (and counting) just
 * one combined operation instead of two.
 *
 * @param a Pointer to the first stack to rotate.
 * @param b Pointer to the second stack to rotate.
 * @param print 1 to print "rr\n" to stdout, 0 to stay silent.
 * @param bench Optional operation counter, or NULL if unused.
 * @return void
 */
void	ft_rr(t_stack **a, t_stack **b, int print, t_bench *bench)
{
	if (*a && (*a)->next)
		rotate_up(a);
	if (*b && (*b)->next)
		rotate_up(b);
	if (bench)
		bench->rr++;
	if (print)
		write(1, "rr\n", 3);
}
