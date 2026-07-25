#include "push_swap.h"

/**
 * @brief Moves the top node of one stack onto another.
 *
 * Caller must already have checked src is not empty.
 *
 * @param dest Pointer to the destination stack, receives the node.
 * @param src Pointer to the source stack, loses its top node.
 * @return void
 */
static void	move_top(t_stack **dest, t_stack **src)
{
	t_stack	*node;

	node = *src;
	*src = (*src)->next;
	node->next = *dest;
	*dest = node;
}

/**
 * @brief Pushes the top of b onto the top of a.
 *
 * Does nothing if b is empty.
 *
 * @param a Pointer to the destination stack.
 * @param b Pointer to the source stack.
 * @param print 1 to print "pa\n" to stdout, 0 to stay silent.
 * @param bench Optional operation counter, or NULL if unused.
 * @return void
 */
void	ft_pa(t_stack **a, t_stack **b, int print, t_bench *bench)
{
	if (!*b)
		return ;
	move_top(a, b);
	if (bench)
		bench->pa++;
	if (print)
		write(1, "pa\n", 3);
}

/**
 * @brief Pushes the top of a onto the top of b.
 *
 * Does nothing if a is empty.
 *
 * @param a Pointer to the source stack.
 * @param b Pointer to the destination stack.
 * @param print 1 to print "pb\n" to stdout, 0 to stay silent.
 * @param bench Optional operation counter, or NULL if unused.
 * @return void
 */
void	ft_pb(t_stack **a, t_stack **b, int print, t_bench *bench)
{
	if (!*a)
		return ;
	move_top(b, a);
	if (bench)
		bench->pb++;
	if (print)
		write(1, "pb\n", 3);
}
