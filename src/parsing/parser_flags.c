#include "push_swap.h"

int	flag_duplicates(char *flag, int strategy, int bench)
{
	if (ft_strcmp(flag, "--simple") == 0
		|| ft_strcmp(flag, "--medium") == 0
		|| ft_strcmp(flag, "--complex") == 0
		|| ft_strcmp(flag, "--adaptive") == 0)
	{
		if (strategy != NONE)
			return (1);
	}
	else if (ft_strcmp(flag, "--bench") == 0)
	{
		if (bench == 1)
			return (1);
	}
	return (0);
}

int	set_strategy(char *flag, int *strategy)
{
	if (ft_strcmp(flag, "--simple") == 0)
		*strategy = SIMPLE;
	else if (ft_strcmp(flag, "--medium") == 0)
		*strategy = MEDIUM;
	else if (ft_strcmp(flag, "--complex") == 0)
		*strategy = COMPLEX;
	else if (ft_strcmp(flag, "--adaptive") == 0)
		*strategy = ADAPTIVE;
	else
		return (0);
	return (1);
}

int	parse_flags(int argc, char **argv, int *strategy, int *bench)
{
	int	i;

	i = 1;
	while (i < argc && argv[i] != NULL
		&& argv[i][0] == '-' && argv[i][1] == '-')
	{
		if (flag_duplicates(argv[i], *strategy, *bench))
			return (-1);
		if (!set_strategy(argv[i], strategy))
		{
			if (ft_strcmp(argv[i], "--bench") == 0)
				*bench = 1;
			else
				return (-1);
		}
		i++;
	}
	return (i);
}
