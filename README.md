*This project has been created as part of the 42 curriculum by clopez-b, raqcabre.*

# push_swap

## Description

`push_swap` is a 42 School algorithmic project. Given a random list of integers,
the goal is to sort them in ascending order using two stacks (`a` and `b`) and a
small, fixed set of operations (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`,
`rra`, `rrb`, `rrr`), while using as few operations as possible.

The project extends the standard push_swap subject with a **disorder index**
(a value between 0 and 1 describing how far the input is from being sorted)
and requires implementing four distinct sorting strategies, each targeting a
different complexity class, plus an adaptive mode that picks between them
based on the disorder index:

| Flag         | Strategy                         | Complexity class |
|--------------|-----------------------------------|-------------------|
| `--simple`   | Selection-based sort               | O(n²)             |
| `--medium`   | Chunk-based sort                   | O(n√n)            |
| `--complex`  | LSD radix sort                     | O(n log n)        |
| `--adaptive` | Picks one of the above (default)   | depends on input  |

Complexity here is always measured as **the number of push_swap operations
generated**, not the theoretical complexity of a classic array-sorting
algorithm (per the subject's model, VI.3.1).

## Instructions

### Build

```
make            # builds push_swap
make bonus      # builds the checker (bonus)
make clean      # removes object files
make fclean     # removes object files and binaries
make re         # fclean + all
```

The Makefile compiles with `-Wall -Wextra -Werror`, uses `cc`, and never
relinks unnecessarily.

### Run

```
./push_swap 2 1 3 6 5 8
```

Prints the shortest sequence of operations found, one per line, to `stdout`.
With no arguments, the program prints nothing and returns control immediately.

### Strategy selector (optional flag)

```
./push_swap --simple 5 4 3 2 1
./push_swap --medium 5 4 3 2 1
./push_swap --complex 5 4 3 2 1
./push_swap --adaptive 5 4 3 2 1   # same as no flag at all
```

### Benchmark mode (optional flag)

```
./push_swap --bench 2 1 3 6 5 8 2> bench.txt
cat bench.txt
```

Prints, to `stderr` only:
- the disorder index (as a percentage, two decimals),
- the strategy used and its theoretical complexity class,
- the total number of operations,
- a breakdown of operations by type.

`stdout` keeps showing only the operation sequence, so it can still be piped
straight into a checker.

### Error handling

Invalid input (non-integer arguments, values outside `int` range, duplicate
values) makes the program print `Error` followed by `\n` to `stderr` and exit,
without printing any operations.

## Project structure

```
push_swap/
├── Makefile
├── README.md
├── includes/
│   └── push_swap.h
├── src/
│   ├── main.c
│   ├── parsing/
│   │   ├── parse_args.c
│   │   ├── parse_flags.c
│   │   └── parse_errors.c
│   ├── stack_ops/
│   │   ├── ops_swap.c
│   │   ├── ops_push.c
│   │   ├── ops_rotate.c
│   │   └── ops_reverse.c
│   ├── algorithms/
│   │   ├── disorder_index.c
│   │   ├── simple_sort.c
│   │   ├── medium_sort.c
│   │   ├── complex_sort.c
│   │   ├── adaptive_sort.c
│   │   └── sort_utils.c
│   └── bench/
│       ├── bench.c
│       └── bench_utils.c
└── checker_bonus/
```

## Algorithms

### Disorder index

Computed once, before any operation is applied, by counting inversions:
pairs `(i, j)` with `i` before `j` where the value at `i` is greater than the
value at `j`. The result is `mistakes / total_pairs`, where `total_pairs =
n * (n - 1) / 2`. This counting itself never generates any push_swap
operation — it is plain C bookkeeping and is not part of the operation-count
complexity the subject asks us to optimize.

### Simple sort — O(n²)

Repeatedly finds the current minimum of stack `a`, rotates it to the top in
whichever direction is shorter, and pushes it to `b`. The last element left in
`a` is always the maximum, so it is never moved. Finally, `b` is drained back
into `a`, restoring ascending order.

- **Space:** O(1) extra (in-place on the existing nodes).
- **Time (operations):** each of the n iterations costs up to O(n) for the
  minimum search and up to O(n) for the rotation, giving O(n²) operations in
  the worst case.

### Medium sort — O(n√n)

Each value is mapped to its rank (0 to n-1), and ranks are split into
approximately √n chunks. Each chunk is processed in a single left-to-right
pass over `a`: matching elements are pushed to `b` and locally inserted into
their correct spot within that chunk (using `sb`/`rb`/`rrb`); the rest are
rotated with `ra` to be revisited in a later chunk pass.

- **Space:** O(1) extra.
- **Time (operations):** √n chunk passes, each O(n) to scan `a` plus O(√n)
  insertion cost per element within the chunk (√n elements per chunk), giving
  O(n√n) operations overall.

### Complex sort — O(n log n)

LSD radix sort adapted to stacks. Each value is mapped to its rank (0 to
n-1). For each bit needed to represent that rank (⌈log₂ n⌉ bits), one pass is
made over `a`: elements whose current bit is 0 go to `b`, others are rotated
to the bottom of `a` with `ra`; `b` is then drained back into `a` with `pa`.
Processing from the least to the most significant bit leaves the stack fully
sorted once all bits have been processed.

- **Space:** O(1) extra.
- **Time (operations):** ⌈log₂ n⌉ passes, each O(n), giving O(n log n)
  operations overall.

### Adaptive sort

Picks one of the three strategies above based on the disorder index computed
at the start:

| Disorder range   | Strategy used | Complexity |
|-------------------|--------------|------------|
| `< 0.2`            | Simple sort   | O(n)      |
| `0.2` to `< 0.5`   | Medium sort   | O(n√n)     |
| `>= 0.5`           | Complex sort  | O(n log n) |

> **Erratum note:** the written subject states that low disorder (`< 0.2`)
> should use O(n). This was confirmed by staff during a live correction
> session to be a true in the subject text: the intended mapping is low
> disorder → O(n), medium disorder → O(n√n), high disorder → O(n log n),
> which is the mapping implemented and described above.

**Threshold justification:**

- **`0.5` (high disorder cutoff):** for a uniformly random permutation of n
  distinct values, the expected number of inversions is `n(n-1)/4`, i.e. the
  expected disorder index is exactly `0.5`. Using `0.5` as the cutoff for the
  most general-purpose strategy (radix sort, which makes no assumption about
  the input's structure) means: anything at or above "average shuffle"
  randomness gets the strategy with the strongest worst-case guarantee.
- **`0.2` (low disorder cutoff):** below this point, fewer than one in five
  possible pairs are inverted, which in practice corresponds to inputs that
  are already nearly sorted (a handful of misplaced values, or a short local
  perturbation). Simple sort's actual operation count scales with how far
  values are from their sorted position, not just with `n`; on this kind of
  input the rotation distances involved are small, so despite its O(n²)
  worst-case class, it stays cheap in practice for this specific regime while
  remaining a fully deterministic, always-correct choice with no need to
  detect specific structural patterns.
- **`[0.2, 0.5)` (medium band):** the remaining range is handled by the
  chunk-based sort, giving a middle-ground operation count that fits inputs
  that are partially, but not extremely, shuffled.


## Resources

- Donald Knuth, *The Art of Computer Programming, Vol. 3: Sorting and
  Searching* — background on sorting algorithms and Big-O notation.
- Wikipedia: [Radix sort](https://en.wikipedia.org/wiki/Radix_sort),
  [Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort),
  [Big O notation](https://en.wikipedia.org/wiki/Big_O_notation).
- 42 Norm v4.1 — coding style requirements applied throughout this project.
- 42 push_swap subject (this repository's `en_norm.pdf` / project subject
  files) for the operation definitions and evaluation criteria.

### AI usage disclosure

AI assistance was minimaly used in the early design stages to design the
project architecture and to understand the initial logic of the stack
operations (`sa`/`sb`/`ss`/`pa`/`pb`/`ra`/`rb`/`rr`/`rra`/`rrb`/`rrr`), the
disorder index calculation, to help choose the four sorting strategies and to understand the benchmark mode.
