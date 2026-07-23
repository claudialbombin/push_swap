#include "push_swap.h"

/*
** Rotates a stack upwards: the first element becomes the last
** one, everything else shifts up by one position. Caller must
** already have checked the stack has at least 2 elements.
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

void	ft_ra(t_stack **a, int print)
{
	if (!*a || !(*a)->next)
		return ;
	rotate_up(a);
	if (g_bench)
		g_bench->ra++;
	if (print)
		write(1, "ra\n", 3);
}

void	ft_rb(t_stack **b, int print)
{
	if (!*b || !(*b)->next)
		return ;
	rotate_up(b);
	if (g_bench)
		g_bench->rb++;
	if (print)
		write(1, "rb\n", 3);
}

/*
** rr does ra and rb at the same time, printing (and counting)
** just one combined operation instead of two.
*/
void	ft_rr(t_stack **a, t_stack **b, int print)
{
	if (*a && (*a)->next)
		rotate_up(a);
	if (*b && (*b)->next)
		rotate_up(b);
	if (g_bench)
		g_bench->rr++;
	if (print)
		write(1, "rr\n", 3);
}
