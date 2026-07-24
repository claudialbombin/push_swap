/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+    */
/*   By: clopez-b <clopez-b@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2026/07/22 00:00:00 by clopez-b          #+#    #+#             */
/*   Updated: 2026/07/24 00:00:00 by clopez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Builds the "[bench] strategy: ..." label. For forced flags
** the label is fixed, but for --adaptive we need to repeat the
** same disorder thresholds used inside ft_adaptive_sort, since
** that function only sorts, it doesn't report which internal
** method it picked. Stacks of SMALL_N_MAX elements or fewer always
** go through ft_optimal_sort instead (see execute_strategy), so
** their label overrides everything else, chosen strategy included.
*/
static char	*strategy_label(t_strategy strategy, double disorder, int size)
{
	if (size <= SMALL_N_MAX)
		return ("Optimal (exhaustive search)");
	if (strategy == STRAT_SIMPLE)
		return ("Simple / O(n^2)");
	if (strategy == STRAT_MEDIUM)
		return ("Medium / O(n * sqrt(n))");
	if (strategy == STRAT_COMPLEX)
		return ("Complex / O(n log n)");
	if (disorder < 0.2)
		return ("Adaptive / O(n)");
	if (disorder < 0.5)
		return ("Adaptive / O(n * sqrt(n))");
	return ("Adaptive / O(n log n)");
}

/*
** Runs whichever sorting strategy the user picked (or the
** adaptive one by default). bench always points at a valid,
** zero-initialized struct - the counters just go unused (and
** unprinted) when --bench wasn't passed.
**
** Stacks of SMALL_N_MAX elements or fewer always go through the
** exhaustive-search optimal sort instead, regardless of the chosen
** strategy: at that size the state space is tiny enough to search
** in full, so there's no reason to settle for any strategy's
** general-purpose (and here, non-optimal) behaviour.
*/
static void	execute_strategy(t_stack **a, t_stack **b, t_strategy strategy,
		t_bench *bench)
{
	if (ft_stack_size(*a) <= SMALL_N_MAX)
		ft_optimal_sort(a, b, bench);
	else if (strategy == STRAT_SIMPLE)
		ft_simple_sort(a, b, bench);
	else if (strategy == STRAT_MEDIUM)
		ft_medium_sort(a, b, bench);
	else if (strategy == STRAT_COMPLEX)
		ft_complex_sort(a, b, bench);
	else
		ft_adaptive_sort(a, b, bench);
}

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;
	t_bench		bench;
	t_strategy	strategy;
	double		disorder;

	if (argc <= 1)
		return (0);
	a = ft_build_stack(argc, argv);
	b = NULL;
	strategy = ft_parse_strategy(argc, argv);
	disorder = compute_disorder(a);
	ft_bench_init(&bench);
	execute_strategy(&a, &b, strategy, &bench);
	if (ft_has_bench_flag(argc, argv))
		ft_print_bench(disorder,
			strategy_label(strategy, disorder, ft_stack_size(a)), &bench);
	ft_free_stack(&a);
	ft_free_stack(&b);
	return (0);
}
