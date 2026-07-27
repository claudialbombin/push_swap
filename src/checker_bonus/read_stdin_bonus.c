#include "checker_bonus.h"

#define CHK_BUF_SIZE 4096

/**
 * @brief Builds a fresh buffer holding a followed by b, then frees a.
 *
 * Only malloc/free are authorized here (no realloc), so growing the
 * stdin buffer means allocating a new block and copying every time
 * instead of resizing in place.
 *
 * @param a First half, freed once the join is complete.
 * @param b Second half, appended after a.
 * @return The newly allocated, concatenated string, or NULL on
 *         allocation failure.
 */
static char	*checker_join(char *a, char *b)
{
	char	*joined;
	size_t	i;
	size_t	j;

	joined = malloc(ft_strlen(a) + ft_strlen(b) + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (a[i])
	{
		joined[i] = a[i];
		i++;
	}
	j = 0;
	while (b[j])
	{
		joined[i + j] = b[j];
		j++;
	}
	joined[i + j] = '\0';
	free(a);
	return (joined);
}

/**
 * @brief Reads the whole of stdin into a single heap buffer.
 *
 * Reads every instruction the checker will ever get in one go
 * (checker has no other use for stdin once sorting starts), since
 * get_next_line-style incremental reading buys nothing here.
 *
 * @return NUL-terminated buffer holding everything read from stdin,
 *         or NULL on allocation or read failure.
 */
char	*checker_read_stdin(void)
{
	char	*buf;
	char	chunk[CHK_BUF_SIZE + 1];
	int		n;

	buf = ft_strdup("");
	if (!buf)
		return (NULL);
	n = read(0, chunk, CHK_BUF_SIZE);
	while (n > 0)
	{
		chunk[n] = '\0';
		buf = checker_join(buf, chunk);
		if (!buf)
			return (NULL);
		n = read(0, chunk, CHK_BUF_SIZE);
	}
	if (n < 0)
		return (free(buf), NULL);
	return (buf);
}
