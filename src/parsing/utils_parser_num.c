#include "push_swap.h"

int	count_numbers(int argc, char **argv, int first_number)
{
	char	**numbers;
	int		total;
	int		i;
	int		j;

	total = 0;
	i = first_number;
	while (i < argc && argv[i] != NULL)
	{
		numbers = ft_split(argv[i], ' ');
		if (!numbers)
			return (0);
		j = 0;
		while (numbers[j] != NULL)
		{
			total++;
			j++;
		}
		free_split(numbers);
		i++;
	}
	return (total);
}

char	**normalize_args(int argc, char **argv, int first_number)
{
	int		total_numbers;
	int		i;
	int		index;
	char	**new_array;
	char	**split_tmp;

	total_numbers = count_numbers(argc, argv, first_number);
	new_array = malloc(sizeof(char *) * (total_numbers + 1));
	if (!new_array)
		return (NULL);
	i = first_number;
	index = 0;
	while (i < argc && argv[i] != NULL)
	{
		split_tmp = ft_split(argv[i], ' ');
		if (!split_tmp)
			return (NULL);
		copy_split(new_array, split_tmp, &index);
		free_split(split_tmp);
		i++;
	}
	new_array[index] = NULL;
	return (new_array);
}

void	copy_split(char **new_array, char **split_tmp, int *index)
{
	int	j;

	j = 0;
	while (split_tmp[j] != NULL)
	{
		new_array[*index] = ft_strdup(split_tmp[j]);
		(*index)++;
		j++;
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
