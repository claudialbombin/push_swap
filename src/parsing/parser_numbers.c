#include "push_swap.h"

/**
 * @brief Parses an array of number strings into a new stack.
 *
 * @param argv Null-terminated array of number strings.
 * @param a Pointer set to the newly built stack.
 * @return 1 on success; 0 if any string isn't a valid number, is out
 *         of int range, allocation failed, or duplicates were found.
 */
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

/**
 * @brief Checks whether a string is a valid (optionally signed) integer.
 *
 * @param str String to check.
 * @return 1 if str is a valid integer literal, 0 otherwise.
 */
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

/**
 * @brief Checks whether a long value fits within int range.
 *
 * @param value Value to check.
 * @return 1 if value is between INT_MIN and INT_MAX, 0 otherwise.
 */
int	is_int_range(long value)
{
	if (value >= INT_MIN && value <= INT_MAX)
		return (1);
	return (0);
}

/**
 * @brief Checks whether a stack contains any repeated value.
 *
 * @param a Stack to check.
 * @return 1 if any two nodes share the same value, 0 otherwise.
 */
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
