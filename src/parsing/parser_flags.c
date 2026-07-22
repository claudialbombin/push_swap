#include "push_swap.h"

int	flag_duplicates(char *flag, int strategy, int bench)
{
	if (ft_strcmp(flag, "--simple") == 0
		|| ft_strcmp(flag, "--medium") == 0
		|| ft_strcmp(flag, "--complex") == 0
		|| ft_strcmp(flag, "--adaptive") == 0)
	{
		if (strategy != NONE)
			return (1);
	}
	else if (ft_strcmp(flag, "--bench") == 0)
	{
		if (bench == 1)
			return (1);
	}
	return (0);
}

int	set_strategy(char *flag, int *strategy)
{
	if (ft_strcmp(flag, "--simple") == 0)
		*strategy = SIMPLE;
	else if (ft_strcmp(flag, "--medium") == 0)
		*strategy = MEDIUM;
	else if (ft_strcmp(flag, "--complex") == 0)
		*strategy = COMPLEX;
	else if (ft_strcmp(flag, "--adaptive") == 0)
		*strategy = ADAPTIVE;
	else
		return (0);
	return (1);
}

int	parse_flags(int argc, char **argv, int *strategy, int *bench)
{
	int	i;

	i = 1;
	while (i < argc && argv[i] != NULL
		&& argv[i][0] == '-' && argv[i][1] == '-')
	{
		if (flag_duplicates(argv[i], *strategy, *bench))
			return (-1);
		if (!set_strategy(argv[i], strategy))
		{
			if (ft_strcmp(argv[i], "--bench") == 0)
				*bench = 1;
			else
				return (-1);
		}
		i++;
	}
	return (i);
}  
 
// EXPLICACIONES

/*
int		parse_flags(int argc, char **argv, int *strategy, int *bench)

    ** Analiza las flags.
    **
    ** Devuelve:
    **  - índice del primer número.
    **  - -1 si hay error.
    **
    ** Pseudocódigo:
    **
    ** recorrer argv desde argv[1]
    **
    ** mientras el argumento empiece por "--"
    **
    **     identificar la flag
    **
    **     guardar la estrategia
    **
    **     activar bench si aparece
    **
    ** devolver el índice donde empiezan los números

int parse_numbers(int argc, char **argv, int first_number, t_stack *a) -> construye el stack

    ** Construye el stack.
    **
    ** Devuelve:
    **  1 -> correcto
    **  0 -> error
    **
    ** Pseudocódigo:
    **
    ** recorrer todos los números
    **
    **     comprobar formato
    **
    **     convertir a long
    **
    **     comprobar rango int
    **
    **     crear nodo
    **
    **     añadir nodo al stack
    **
    ** comprobar duplicados
    **
    ** devolver éxito

t_node *create_node(int value) 

    ** Crea un nuevo nodo del stack.
    **
    ** Devuelve:
    **  puntero al nodo creado.
    **  NULL -> si falla malloc.
    **
    ** Pseudocódigo:
    **
    ** reservar memoria para un nodo
    **
    ** si malloc falla
    **
    **     devolver NULL
    **
    ** guardar value
    **
    ** inicializar index
    **
    ** poner next a NULL
    **
    ** poner prev a NULL
    **
    ** devolver el nodo

void add_node(t_stack *stack, t_node *new_node) -> Añade un nodo al final del stack

    ** Añade un nodo al final del stack.
    **
    ** Pseudocódigo:
    **
    ** si el stack está vacío
    **
    **     top = nuevo nodo
    **
    **     bottom = nuevo nodo
    **
    ** si no
    **
    **     conectar el antiguo bottom con el nuevo nodo
    **
    **     conectar el nuevo nodo con el antiguo bottom
    **
    **     actualizar bottom
    **
    ** aumentar size

int is_number(char *str)

    ** Comprueba si una cadena representa un entero válido.
    **
    ** Devuelve:
    **  1 -> válido
    **  0 -> inválido
    **
    ** Pseudocódigo:
    **
    ** comprobar cadena vacía
    **
    ** comprobar signo
    **
    ** comprobar que existen dígitos
    **
    ** recorrer todos los caracteres
    **
    **     si alguno no es un dígito
    **
    **         inválido
    **
    ** válido

long ft_atol(const char *str)

    ** Convierte una cadena a long.
    **
    ** Pseudocódigo:
    **
    ** leer signo
    **
    ** resultado = 0
    **
    ** mientras haya dígitos
    **
    **     resultado = resultado * 10 + dígito
    **
    ** aplicar signo
    **
    ** devolver resultado

int is_int_range(long value)

    ** Comprueba si un long cabe en un int.
    **
    ** Devuelve:
    **  1 -> sí
    **  0 -> no
    **
    ** Pseudocódigo:
    **
    ** si value < INT_MIN
    **
    **     no
    **
    ** si value > INT_MAX
    **
    **     no
    **
    ** sí

int has_duplicates(t_stack *a)

    ** Busca valores repetidos.
    **
    ** Devuelve:
    **  1 -> hay duplicados
    **  0 -> no hay duplicados
    **
    ** Pseudocódigo:
    **
    ** para cada nodo
    **
    **     recorrer los siguientes
    **
    **         si coinciden
    **
    **             duplicado
    **
    ** no hay duplicados
*/





/*
MI PARSE FLAGS ANTERIOR 22/07

// int		parse_flags(int argc, char **argv, int *strategy, int *bench)
// {
//     int i;

//     i = 1;
//     while (i < argc && argv[i] != NULL && argv[i][0] == '-' && argv[i][1] == '-')
//     {
//         // identificar la flag y guardar la estrategia / activar bench
//         if (ft_strcmp(argv[i], "--simple") == 0)
//             *strategy = SIMPLE;
//         else if (ft_strcmp(argv[i], "--medium") == 0)
//             *strategy = MEDIUM;
//         else if (ft_strcmp(argv[i], "--complex") == 0)
//             *strategy = COMPLEX;
//         else if (ft_strcmp(argv[i], "--adaptive") == 0)
//             *strategy = ADAPTIVE;
//         else if (ft_strcmp(argv[i], "--bench") == 0)
//             *bench = 1;
//         else // Devuelve -1 si es una flag desconocida (ej. --error)
//             return (-1);
//         i++; // Avanza al siguiente argumento
//     }
//     return (i); // devolver el índice donde empiezan los números
// }
*/