#include "push_swap.h"

/*
** Reverse rotates a stack downwards: the last element becomes
** the first one, everything else shifts down by one position.
** Caller must already have checked the stack has >= 2 elements.
*/
static void	rotate_down(t_stack **s)
{
	t_stack	*current;
	t_stack	*prev;

	current = *s;
	prev = NULL;
	while (current->next)
	{
		prev = current;
		current = current->next;
	}
	prev->next = NULL;
	current->next = *s;
	*s = current;
}

void	ft_rra(t_stack **a, int print, t_bench *bench)
{
	if (!*a || !(*a)->next)
		return ;
	rotate_down(a);
	if (bench)
		bench->rra++;
	if (print)
		write(1, "rra\n", 4);
}

void	ft_rrb(t_stack **b, int print, t_bench *bench)
{
	if (!*b || !(*b)->next)
		return ;
	rotate_down(b);
	if (bench)
		bench->rrb++;
	if (print)
		write(1, "rrb\n", 4);
}

/*
** rrr does rra and rrb at the same time, printing (and counting)
** just one combined operation instead of two.
*/
void	ft_rrr(t_stack **a, t_stack **b, int print, t_bench *bench)
{
	if (*a && (*a)->next)
		rotate_down(a);
	if (*b && (*b)->next)
		rotate_down(b);
	if (bench)
		bench->rrr++;
	if (print)
		write(1, "rrr\n", 4);
}
