NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iincludes

SRC =	src/main.c \
	src/parsing/parser_flags.c \
	src/parsing/parser_numbers.c \
	src/parsing/build_stack.c \
	src/parsing/nodes.c \
	src/parsing/errors_stack.c \
	src/parsing/split.c \
	src/parsing/utils.c \
	src/parsing/utils_parser_num.c \
	src/parsing/libft_utils.c \
	src/stack_ops/ops_push.c \
	src/stack_ops/ops_swap.c \
	src/stack_ops/ops_rotate.c \
	src/stack_ops/ops_reverse.c \
	src/algorithms/simple_sort.c \
	src/algorithms/medium_sort.c \
	src/algorithms/complex_sort.c \
	src/algorithms/adaptative_sort.c \
	src/algorithms/sort_utils.c \
	src/algorithms/disorder_index.c \
	src/bench/bench.c \
	src/bench/bench_utils.c

OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c includes/push_swap.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
