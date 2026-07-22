#include "push_swap.h"


static int	ft_word_len(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			i += ft_word_len(s + i, c);
		}
	}
	return (count);
}

static void	*free_all(char **tab, int i)
{
	while (i--)
	{
		if (tab[i])
			free(tab[i]);
	}
	free(tab);
	return (NULL);
}

static int	ft_fill_str(char **str, char const *s, char c)
{
	int	i;
	int	subs_len;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			++s;
		if (*s)
		{
			subs_len = ft_word_len(s, c);
			str[i] = ft_calloc(subs_len + 1, sizeof(char));
			if (!str[i])
				return (free_all(str, i), 0);
			ft_strlcpy(str[i], s, subs_len + 1);
			s += subs_len;
			i++;
		}
	}
	str[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = ft_calloc((ft_count_words(s, c) + 1), sizeof(char *));
	if (!str)
		return (NULL);
	if (!ft_fill_str(str, s, c))
		return (NULL);
	return (str);
}
