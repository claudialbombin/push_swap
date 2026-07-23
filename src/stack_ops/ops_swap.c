#include "push_swap.h"

/*
** Swaps the two top nodes of a stack.
** Caller must already have checked the stack has >= 2 elements.
*/
static void	swap_top(t_stack **s)
{
	t_stack	*first;
	t_stack	*second;

	first = *s;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*s = second;
}

void	ft_sa(t_stack **a, int print)
{
	if (!*a || !(*a)->next)
		return ;
	swap_top(a);
	if (g_bench)
		g_bench->sa++;
	if (print)
		write(1, "sa\n", 3);
}

void	ft_sb(t_stack **b, int print)
{
	if (!*b || !(*b)->next)
		return ;
	swap_top(b);
	if (g_bench)
		g_bench->sb++;
	if (print)
		write(1, "sb\n", 3);
}

/*
** ss does sa and sb at the same time, printing (and counting)
** just one combined operation instead of two.
*/
void	ft_ss(t_stack **a, t_stack **b, int print)
{
	if (*a && (*a)->next)
		swap_top(a);
	if (*b && (*b)->next)
		swap_top(b);
	if (g_bench)
		g_bench->ss++;
	if (print)
		write(1, "ss\n", 3);
}
