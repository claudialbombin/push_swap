#include "push_swap.h"

static long	read_digits(const char *str, int *i, int sign)
{
	long	result;
	int		digit;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (result > (LONG_MAX - digit) / 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			return (LONG_MIN);
		}
		result = result * 10 + digit;
		(*i)++;
	}
	return (result * sign);
}

long	ft_atol(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (read_digits(str, &i, sign));
}
