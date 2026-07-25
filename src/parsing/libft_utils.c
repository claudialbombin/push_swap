#include "push_swap.h"

/**
 * @brief Computes the length of a null-terminated string.
 *
 * @param s String to measure.
 * @return Number of characters before the terminating null byte.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
