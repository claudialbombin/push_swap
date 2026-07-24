/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/24 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/24 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** move_id follows the same order used by apply_move: 0 sa, 1 sb,
** 2 ss, 3 pa, 4 pb, 5 ra, 6 rb, 7 rr, 8 rra, 9 rrb, 10 rrr. This
** actually performs the operation on the real stacks (printing and
** counting through the normal ft_* entry points), unlike apply_move
** which only updates the abstract search state.
*/
static void	run_move(int move_id, t_stacks *st)
{
	if (move_id == 0)
		ft_sa(st->a, 1, st->bench);
	else if (move_id == 1)
		ft_sb(st->b, 1, st->bench);
	else if (move_id == 2)
		ft_ss(st->a, st->b, 1, st->bench);
	else if (move_id == 3)
		ft_pa(st->a, st->b, 1, st->bench);
	else if (move_id == 4)
		ft_pb(st->a, st->b, 1, st->bench);
	else if (move_id == 5)
		ft_ra(st->a, 1, st->bench);
	else if (move_id == 6)
		ft_rb(st->b, 1, st->bench);
	else if (move_id == 7)
		ft_rr(st->a, st->b, 1, st->bench);
	else if (move_id == 8)
		ft_rra(st->a, 1, st->bench);
	else if (move_id == 9)
		ft_rrb(st->b, 1, st->bench);
	else
		ft_rrr(st->a, st->b, 1, st->bench);
}

/*
** Walks the parent chain from the goal state back to the start,
** collecting each move along the way, then replays them in forward
** order (the walk itself visits them start-to-goal in reverse).
*/
void	apply_solution(t_state *states, int goal, t_stacks *st)
{
	int	path[MAX_SMALL_MOVES];
	int	len;
	int	cur;

	len = 0;
	cur = goal;
	while (states[cur].parent != -1 && len < MAX_SMALL_MOVES)
	{
		path[len++] = states[cur].move;
		cur = states[cur].parent;
	}
	while (len > 0)
		run_move(path[--len], st);
}
