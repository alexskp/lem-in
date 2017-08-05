#include "lem-in.h"


elem *get_last_elem(elem *head)
{
    if (head == NULL)
        return head;
    while (head->next)
        head = head->next;
    return head;
}

void push(elem **head, room* content)
{
    elem *last = get_last_elem(*head);
    elem *new = (elem *)my_malloc(sizeof(elem));
    new->content = content;
    new->next = NULL;
    if (last)
        last->next = new;
    else
        (*head) = new;
}

room *pop(elem **head)
{
    if (head == NULL)
        error("Error! Can't pop element from empty queue!");
    elem *pop_elem = (*head);
    room *content = pop_elem->content;
    (*head) = pop_elem->next;
    my_free(pop_elem);
    return content;
}
