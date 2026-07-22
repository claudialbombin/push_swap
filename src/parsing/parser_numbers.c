#include "push_swap.h"

// int parse_numbers(int argc, char **argv, int first_number, t_stack *a) //construye el stack
// {  
//     int i;
//     long nbr;
//     t_node *new_node;
  
//     i = first_number;
//     while(i < argc && argv[i] != NULL)
//     {
//         if (!is_number(argv[i]))
//             return (0);
//         nbr = ft_atol(argv[i]);
//         if (!is_int_range(nbr))
//             return (0);
//         new_node = create_node(nbr);
//         if(!new_node)
//             return(0);
//         add_node(a, new_node);
//         i++;
//     }
//     if (has_duplicates(a))
//         return (0);
//     return (1);
// }

int	parse_numbers(char **argv, t_stack *a)
{
	int		i;
	long	nbr;
	t_node	*new_node;

	i = 0;
	while (argv[i] != NULL)
	{
		if (!is_number(argv[i]))
			return (0);
		nbr = ft_atol(argv[i]);
		if (!is_int_range(nbr))
			return (0);
		new_node = create_node((int)nbr);
		if (!new_node)
			return (0);
		add_node(a, new_node);
		i++;
	}
	if (has_duplicates(a))
		return (0);
	return (1);
}

int is_number(char *str)
{
    int i;

    if (!str || str[0] == '\0')
        return (0);
    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (str[i] == '\0')
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int is_int_range(long value)
{
   
    if (value >= INT_MIN && value <= INT_MAX)
        return (1);
    else
        return (0);
}

int has_duplicates(t_stack *a)
{
    t_node *current;
    t_node *check;
   
    if (a == NULL || a->top == NULL)
        return (0);
    current = a->top; // Empiezo en el nodo de arriba
    while (current != NULL) // Bucle externo
    {
        check = current->next;
        while(check != NULL)
        {
            if (current->value == check->value) //Comparo los valores
                return (1);
            check = check->next; //avanza el check al siguiente nodo
        }
        current = current->next; //avanza current al siguiente nodo
    }
    return (0);
}

