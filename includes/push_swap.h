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

typedef enum e_strategy
{
	STRAT_NONE,
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX,
	STRAT_ADAPTIVE
}	t_strategy;

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

typedef struct s_bench
{
	int	sa;
	int	sb;
	int	ss;
	int	pa;
	int	pb;
	int	ra;
	int	rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
}	t_bench;

extern t_bench	*g_bench;

/* Parser flags */
int			flag_duplicates(char *flag, int strategy, int bench);
int			set_strategy(char *flag, int *strategy);
int			parse_flags(int argc, char **argv, int *strategy, int *bench);

/* Parser numbers */
int			parse_numbers(char **argv, t_stack **a);
int			is_number(char *str);
int			is_int_range(long value);
int			has_duplicates(t_stack *a);

/* Utils parser numbers */
long		ft_atol(const char *str);
int			count_numbers(int argc, char **argv, int first_number);
char		**normalize_args(int argc, char **argv, int first_number);
void		copy_split(char **new_array, char **split_tmp, int *index);
void		free_split(char **split);

/* Utils */
int			ft_strcmp(const char *s1, const char *s2);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *s, int c, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strdup(const char *s);

/* Libft-utils */
size_t		ft_strlen(const char *s);

/* Split */
char		**ft_split(char const *s, char c);

/* Nodes */
t_stack		*create_node(int value);
void		add_node(t_stack **head, t_stack **tail, t_stack *node);

/* Build stack / high level parsing */
t_stack		*ft_build_stack(int argc, char **argv);
t_strategy	ft_parse_strategy(int argc, char **argv);
int			ft_has_bench_flag(int argc, char **argv);

/* Errors / Stack */
void		free_stack(t_stack *stack);
void		exit_error(t_stack *a, t_stack *b);

/* Stack utils */
int			ft_stack_size(t_stack *stack);
int			ft_is_sorted(t_stack *a);
int			ft_min_index(t_stack *a);
void		ft_free_stack(t_stack **stack);
double		compute_disorder(t_stack *a);

/* Stack ops */
void		ft_sa(t_stack **a, int print);
void		ft_sb(t_stack **b, int print);
void		ft_ss(t_stack **a, t_stack **b, int print);
void		ft_pa(t_stack **a, t_stack **b, int print);
void		ft_pb(t_stack **a, t_stack **b, int print);
void		ft_ra(t_stack **a, int print);
void		ft_rb(t_stack **b, int print);
void		ft_rr(t_stack **a, t_stack **b, int print);
void		ft_rra(t_stack **a, int print);
void		ft_rrb(t_stack **b, int print);
void		ft_rrr(t_stack **a, t_stack **b, int print);

/* Algorithms */
void		ft_simple_sort(t_stack **a, t_stack **b);
void		ft_medium_sort(t_stack **a, t_stack **b);
void		ft_complex_sort(t_stack **a, t_stack **b);
void		ft_adaptive_sort(t_stack **a, t_stack **b);

/* Bench */
void		ft_bench_init(t_bench *bench);
void		ft_print_bench(double disorder, char *strategy, t_bench *bench);
void		ft_put_str_fd(char *s, int fd);
void		ft_put_nbr_fd(int n, int fd);
void		ft_put_percent_fd(double value, int fd);

#endif
