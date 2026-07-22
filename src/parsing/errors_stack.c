#include "push_swap.h"

void	free_stack(t_stack *stack)
{   
    t_node *current;
    t_node *aux;

    if (stack == NULL)
        return;
    current = stack->top;
    while (current != NULL)
    {
        aux = current->next;
        free(current);
        current = aux;
    }
    stack->top = NULL;
    stack->bottom = NULL;
    stack->size = 0;
}

void	exit_error(t_stack *a, t_stack *b)
{
    free_stack(a);
    free_stack(b);
    write(2, "Error\n", 6);
    exit(1);
}


/*
void	free_stack(t_stack *stack)

    ** Libera todos los nodos de un stack.
    **
    ** Pseudocódigo:
    **
    ** si el stack es NULL
    **
    **     salir
    **
    ** empezar en el nodo superior (top)
    **
    ** mientras exista un nodo
    **
    **     guardar el siguiente nodo
    **
    **     liberar el nodo actual
    **
    **     avanzar al siguiente nodo
    **
    ** dejar top y bottom a NULL
    **
    ** poner size a 0

void	exit_error(t_stack *a, t_stack *b)

    ** Libera memoria y termina el programa.
    **
    ** Pseudocódigo:
    **
    ** liberar stack a
    **
    ** liberar stack b
    **
    ** escribir "Error\n" en stderr
    **
    ** terminar el programa con código de error
    
*/