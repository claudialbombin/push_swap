#include "push_swap.h"

/*
** Moves the top node of src onto the top of dest.
** Caller must already have checked src is not empty.
*/
static void	move_top(t_stack **dest, t_stack **src)
{
	t_stack	*node;

	node = *src;
	*src = (*src)->next;
	node->next = *dest;
	*dest = node;
}

void	ft_pa(t_stack **a, t_stack **b, int print)
{
	if (!*b)
		return ;
	move_top(a, b);
	if (g_bench)
		g_bench->pa++;
	if (print)
		write(1, "pa\n", 3);
}

void	ft_pb(t_stack **a, t_stack **b, int print)
{
	if (!*a)
		return ;
	move_top(b, a);
	if (g_bench)
		g_bench->pb++;
	if (print)
		write(1, "pb\n", 3);
}
