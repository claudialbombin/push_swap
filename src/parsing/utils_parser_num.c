#include "push_swap.h"

long ft_atol(const char *str)
{
    int i;
    int sign;
    long result;
   
    i = 0;
    sign = 1;
    result = 0;
    while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while(str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result * sign);
}

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

/*
recibe tres cosas:
    new_array → dónde guardar los números.
    split_tmp → los números temporales que vienen de ft_split.
    index → la posición actual donde hay que escribir en new_array.
*/

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}


/*
int	count_numbers(int argc, char **argv, int first_number)
    Cuenta cuántos números habrá después de separar
	** todos los argumentos con ft_split().
	**
	** Pseudocódigo:
	**
	** total = 0
	**
	** recorrer argv desde first_number
	**
	**     hacer ft_split(argv[i], ' ')
	**
	**     recorrer el split
	**
	**         aumentar total
	**
	**     liberar split
	**
	** devolver total


char	**normalize_args(int argc, char **argv, int first_number)
    ** Convierte los argumentos en un único array de números.
	**
	** Pseudocódigo:
	**
	** contar cuántos números habrá
	**
	** reservar memoria para el nuevo array
	**
	** recorrer argv desde first_number
	**
	**     hacer ft_split(argv[i], ' ')
	**
	**     recorrer el split
	**
	**         copiar cada número al nuevo array
	**
	**     liberar split
	**
	** poner NULL al final
	**
	** devolver el nuevo array

void	free_split(char **split)
	** Libera la memoria reservada por ft_split().
	**
	** Pseudocódigo:
	**
	** recorrer split
	**
	**     liberar cada string
	**
	** liberar el array
*/