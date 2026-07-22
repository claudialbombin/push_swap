#include "push_swap.h"

t_node *create_node(int value)
{
   
    t_node *nodo;
   
    nodo = malloc(sizeof(t_node));
    if (!nodo)
        return (NULL);
    nodo->value = value;
    nodo->index = 0;
    nodo->next = NULL;
    nodo->prev = NULL;
    return (nodo);
}

void add_node(t_stack *stack, t_node *new_node) // Añade un nodo al final del stack
{
    if (!stack)
        return;
    if (stack->top == NULL) //Stack vacío
    {
        stack->top = new_node;
        stack->bottom = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    else //Ya hay nodos
    {
        stack->bottom->next = new_node; //el antiguo último apunta al nuevo
        new_node->prev = stack->bottom; //El nuevo nodo apunta hacia atrás al antiguo último
        stack->bottom = new_node; //bottom actualiza su posición
        new_node->next = NULL; //Nuevo último apunta a NULL
    }
    stack->size++;
}