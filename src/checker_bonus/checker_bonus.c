#include "checker_bonus.h"

/**
 * @brief Prints "OK\n" or "KO\n" to stdout depending on the result.
 *
 * "a is sorted and b is empty" is the only success condition the
 * subject defines - anything else, including a non-empty b, is KO.
 *
 * @param a Final state of stack a.
 * @param b Final state of stack b.
 * @return void
 */
static void	checker_print_result(t_stack *a, t_stack *b)
{
	if (ft_is_sorted(a) && !b)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

/**
 * @brief Reads every instruction line from stdin.
 *
 * @return NULL-terminated array of instruction strings, or NULL on
 *         allocation or read failure.
 */
static char	**checker_get_lines(void)
{
	char	*input;
	char	**lines;

	input = checker_read_stdin();
	if (!input)
		return (NULL);
	lines = ft_split(input, '\n');
	free(input);
	return (lines);
}

/**
 * @brief Applies every instruction line to the real stacks in order.
 *
 * Exits via exit_error on the first unrecognized instruction, matching
 * the subject's "instruction doesn't exist or is malformed" error case.
 *
 * @param lines NULL-terminated array of instruction strings, freed
 *              here once every line has been applied.
 * @param a Pointer to stack a.
 * @param b Pointer to stack b.
 * @return void
 */
static void	checker_run(char **lines, t_stack **a, t_stack **b)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (!checker_apply_line(lines[i], a, b))
		{
			free_split(lines);
			exit_error(*a, *b);
		}
		i++;
	}
	free_split(lines);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	char	**lines;

	if (argc <= 1)
		return (0);
	a = ft_build_stack(argc, argv);
	b = NULL;
	lines = checker_get_lines();
	if (!lines)
		exit_error(a, b);
	checker_run(lines, &a, &b);
	checker_print_result(a, b);
	ft_free_stack(&a);
	ft_free_stack(&b);
	return (0);
}
