#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#define NONE        0
#define SIMPLE      1
#define MEDIUM      2
#define COMPLEX     3
#define ADAPTIVE    4

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
}	t_stack;



/* Parser flags */
int		flag_duplicates(char *flag, int strategy, int bench);
int		set_strategy(char *flag, int *strategy);
int		parse_flags(int argc, char **argv, int *strategy, int *bench);

/* Parser numbers */
//int		parse_numbers(int argc, char **argv, int first_number, t_stack *a);
int		parse_numbers(char **argv, t_stack *a);
int		is_number(char *str);
int		is_int_range(long value);
int		has_duplicates(t_stack *a);

/* Utils parser numbers */
long	ft_atol(const char *str);
int		count_numbers(int argc, char **argv, int first_number);
char	**normalize_args(int argc, char **argv, int first_number);
void	copy_split(char **new_array, char **split_tmp, int *index);
void	free_split(char **split);

/* Utils */
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);

/* Libft-utils */
size_t	ft_strlen(const char *s);

/* Split */
static int	ft_word_len(char const *str, char c);
static int	ft_count_words(char const *s, char c);
static void	*free_all(char **tab, int i);
static int	ft_fill_str(char **str, char const *s, char c);
char		**ft_split(char const *s, char c);

/* Nodes */
t_node	*create_node(int value);
void	add_node(t_stack *stack, t_node *new_node);

/* Errors / Stack */
void	free_stack(t_stack *stack);
void	exit_error(t_stack *a, t_stack *b);

/* Swap */
void	swap_node(t_stack *stack);
void	sa(t_stack *a, bool checker);
void	sb(t_stack *b, bool checker);

/* Push */
void	push(t_stack *dest, t_stack *src);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);

#endif