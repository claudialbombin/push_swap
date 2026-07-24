/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort_apply.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/24 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/24 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	apply_ss(t_state *s)
{
	arr_swap(s->a, s->a_len);
	arr_swap(s->b, s->b_len);
}

static void	apply_rr(t_state *s)
{
	arr_rotate(s->a, s->a_len);
	arr_rotate(s->b, s->b_len);
}

static void	apply_rrr(t_state *s)
{
	arr_reverse_rotate(s->a, s->a_len);
	arr_reverse_rotate(s->b, s->b_len);
}

/*
** move_id follows the same order as the subject's operation list:
** 0 sa, 1 sb, 2 ss, 3 pa, 4 pb, 5 ra, 6 rb, 7 rr, 8 rra, 9 rrb, 10 rrr.
*/
void	apply_move(int move_id, t_state *s)
{
	if (move_id == 0)
		arr_swap(s->a, s->a_len);
	else if (move_id == 1)
		arr_swap(s->b, s->b_len);
	else if (move_id == 2)
		apply_ss(s);
	else if (move_id == 3)
		arr_push(s->a, &s->a_len, s->b, &s->b_len);
	else if (move_id == 4)
		arr_push(s->b, &s->b_len, s->a, &s->a_len);
	else if (move_id == 5)
		arr_rotate(s->a, s->a_len);
	else if (move_id == 6)
		arr_rotate(s->b, s->b_len);
	else if (move_id == 7)
		apply_rr(s);
	else if (move_id == 8)
		arr_reverse_rotate(s->a, s->a_len);
	else if (move_id == 9)
		arr_reverse_rotate(s->b, s->b_len);
	else
		apply_rrr(s);
}
