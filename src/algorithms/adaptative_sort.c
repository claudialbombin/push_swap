/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/22 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/22 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Picks a strategy based on the disorder index: low disorder
** tries the O(n) rotation fix first (falling back to the O(n
** log n) sort if that guess turns out wrong), medium disorder
** uses the chunk-based sort, high disorder uses radix sort.
*/
void	ft_adaptive_sort(t_stack **a, t_stack **b, t_bench *bench)
{
	double	disorder;

	if (ft_is_sorted(*a))
		return ;
	disorder = compute_disorder(*a);
	if (disorder < 0.2)
		ft_linear_sort(a, b, bench);
	else if (disorder < 0.5)
		ft_medium_sort(a, b, bench);
	else
		ft_complex_sort(a, b, bench);
}
