/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort_moves.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/24 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/24 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Pure array transforms mirroring sa/sb, ra/rb, rra/rrb and pa/pb,
** but operating on the small fixed-size int arrays a t_state holds
** instead of the real linked-list stacks. Used only by the BFS
** search over abstract states; the real stacks are moved separately
** once the winning sequence of moves is known.
*/
void	arr_swap(int *arr, int len)
{
	int	tmp;

	if (len < 2)
		return ;
	tmp = arr[0];
	arr[0] = arr[1];
	arr[1] = tmp;
}

void	arr_rotate(int *arr, int len)
{
	int	first;
	int	i;

	if (len < 2)
		return ;
	first = arr[0];
	i = 0;
	while (i < len - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[len - 1] = first;
}

void	arr_reverse_rotate(int *arr, int len)
{
	int	last;
	int	i;

	if (len < 2)
		return ;
	last = arr[len - 1];
	i = len - 1;
	while (i > 0)
	{
		arr[i] = arr[i - 1];
		i--;
	}
	arr[0] = last;
}

void	arr_push(int *dest, int *dest_len, int *src, int *src_len)
{
	int	val;
	int	i;

	if (*src_len == 0)
		return ;
	val = src[0];
	i = 0;
	while (i < *src_len - 1)
	{
		src[i] = src[i + 1];
		i++;
	}
	(*src_len)--;
	i = *dest_len;
	while (i > 0)
	{
		dest[i] = dest[i - 1];
		i--;
	}
	dest[0] = val;
	(*dest_len)++;
}
