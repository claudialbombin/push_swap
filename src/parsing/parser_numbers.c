#include "push_swap.h"

int	parse_numbers(char **argv, t_stack **a)
{
	int		i;
	long	nbr;
	t_stack	*new_node;
	t_stack	*tail;

	i = 0;
	tail = NULL;
	*a = NULL;
	while (argv[i] != NULL)
	{
		if (!is_number(argv[i]))
			return (0);
		nbr = ft_atol(argv[i]);
		if (!is_int_range(nbr))
			return (0);
		new_node = create_node((int)nbr);
		if (!new_node)
			return (0);
		add_node(a, &tail, new_node);
		i++;
	}
	if (has_duplicates(*a))
		return (0);
	return (1);
}

int	is_number(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_int_range(long value)
{
	if (value >= INT_MIN && value <= INT_MAX)
		return (1);
	return (0);
}

int	has_duplicates(t_stack *a)
{
	t_stack	*current;
	t_stack	*check;

	if (a == NULL)
		return (0);
	current = a;
	while (current != NULL)
	{
		check = current->next;
		while (check != NULL)
		{
			if (current->value == check->value)
				return (1);
			check = check->next;
		}
		current = current->next;
	}
	return (0);
}
