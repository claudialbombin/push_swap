#include "push_swap.h"

static t_strategy	int_to_strategy(int strategy)
{
	if (strategy == SIMPLE)
		return (STRAT_SIMPLE);
	if (strategy == MEDIUM)
		return (STRAT_MEDIUM);
	if (strategy == COMPLEX)
		return (STRAT_COMPLEX);
	if (strategy == ADAPTIVE)
		return (STRAT_ADAPTIVE);
	return (STRAT_NONE);
}

t_strategy	ft_parse_strategy(int argc, char **argv)
{
	int	strategy;
	int	bench;

	strategy = NONE;
	bench = 0;
	if (parse_flags(argc, argv, &strategy, &bench) == -1)
		return (STRAT_NONE);
	return (int_to_strategy(strategy));
}

int	ft_has_bench_flag(int argc, char **argv)
{
	int	strategy;
	int	bench;

	strategy = NONE;
	bench = 0;
	if (parse_flags(argc, argv, &strategy, &bench) == -1)
		return (0);
	return (bench);
}

/*
** Parses flags, splits any space-separated numbers inside a
** single argument, then builds the stack. Any parsing failure
** (bad flag, bad number, out of range, duplicate) exits the
** whole program via exit_error, matching the subject's "Error"
** requirement.
*/
t_stack	*ft_build_stack(int argc, char **argv)
{
	int		strategy;
	int		bench;
	int		first_number;
	char	**numbers;
	t_stack	*a;

	strategy = NONE;
	bench = 0;
	first_number = parse_flags(argc, argv, &strategy, &bench);
	if (first_number == -1)
		exit_error(NULL, NULL);
	if (first_number >= argc)
		return (NULL);
	numbers = normalize_args(argc, argv, first_number);
	if (!numbers)
		exit_error(NULL, NULL);
	a = NULL;
	if (!parse_numbers(numbers, &a))
	{
		free_split(numbers);
		exit_error(a, NULL);
	}
	free_split(numbers);
	return (a);
}
