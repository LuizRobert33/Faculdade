#include <stdlib.h>
#include <stdio.h>
#include "List.h"

struct Node {
    void *value;
    Node *next;
};

struct List {
    int length;
    Node *first;
    Node *last;
};

int count_recursive(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + count_recursive(node->next);
}

void invert_recursive(Node **head, Node *current, Node *prev) {
    if (!current) {
        *head = prev;
        return;
    }

    Node *next = current->next;
    current->next = prev;
    invert_recursive(head, next, current);
}

int List_invert(List *l) {
    if (!l || !l->first) {
        return 0; 
    }
    
    invert_recursive(&(l->first), l->first, NULL);
    
    
    l->last = l->first;
    while (l->last->next != NULL) {
        l->last = l->last->next;
    }
    
    return 1; // Sucesso
}

List *List_concat(List *l1, List *l2) {
    List *l3 = List_alloc();
    if (!l3) {
        return NULL; 
    }

    Node *current = l1 ? l1->first : NULL;
    while (current) {
        List_insert(l3, current->value);
        current = current->next;
    }

    current = l2 ? l2->first : NULL;
    while (current) {
        List_insert(l3, current->value);
        current = current->next;
    }

    return l3;
}

List *List_alloc() {
    List *l = malloc(sizeof(List));
    
    if (l) {
        l->length = 0;
        l->first = NULL;
        l->last = NULL;
    }
    
    return l;
}

void List_free(List *l) {
    Node *n = l ? l->first : NULL;
    Node *aux;

    while (n) {
        aux = n->next;
        free(n);
        n = aux;
    }

    free(l);
}

void List_insert(List *l, void *value) {
    Node *new = malloc(sizeof(Node));
    if (new) {
        new->value = value;
        new->next = NULL;

        if (l->length > 0) {
            l->last->next = new;
        } else {
            l->first = new;
        }

        l->last = new;
        l->length++;
    }
}

void *List_remove(List *l, void *value, int (*cmp)(void*, void*)) {
    Node *n = l ? l->first : NULL;
    Node *ant = NULL;
    void *aux = NULL;

    while (n) {
        if (cmp(n->value, value) == 0) {
            if (ant) {
                ant->next = n->next;
            } else {
                l->first = n->next;
            }

            if (n->next == NULL) {
                l->last = ant;
            }

            aux = n->value;
            free(n);
            l->length--;
            return aux;
        }

        ant = n;
        n = n->next;
    }

    return NULL;
}

int List_getLength(List *l) {
    if (l) {
        return l->length;
    }
    return 0;
}

void List_print(List *l, void (*print)(void*)) {
    Node *n = l ? l->first : NULL;

    while (n) {
        print(n->value);
        n = n->next;
    }

    printf("\n");
}

int List_count(List *l) {
    if (l) {
        return count_recursive(l->first);
    }
    return 0;
}
