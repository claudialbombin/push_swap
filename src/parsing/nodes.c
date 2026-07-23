#include "push_swap.h"

t_stack	*create_node(int value)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = 0;
	node->next = NULL;
	return (node);
}

/*
** Appends a node at the end of the list, keeping *tail up to
** date so the caller doesn't have to walk the whole list again
** for the next append.
*/
void	add_node(t_stack **head, t_stack **tail, t_stack *node)
{
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
}
