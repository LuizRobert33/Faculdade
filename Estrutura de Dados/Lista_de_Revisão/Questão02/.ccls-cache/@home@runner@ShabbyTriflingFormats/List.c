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

List *List_alloc() {
  List *l = malloc(sizeof(List));

  if (l) {
    l->length = 0;
    l->first = NULL;
    l->last = NULL;
  }

  return l;
}

void List_free(List *l){
  Node *n = NULL;
  Node *aux = NULL;

  if (l) {
    n = l->first;
    free(l);

    while (n) {
      aux = n->next;
      free(n);
      n = aux;
    }
  }
}

void List_insert(List *l, void* value){
  Node *new = NULL;

  if (l) {
    new = malloc(sizeof(Node));
    new->value = value;
    new->next = NULL;

    if (l->length > 0) {
      l->last->next = new;
    }
    else {
      l->first = new;
    }

    l->last = new;
    l->length++;
  }
}

void *List_remove(List *l, void *value, int (*cmp)(void*,void*)){
  Node *n = NULL;
  Node *ant = NULL;
  void *aux = NULL;

  if (l) {
    n = l->first;

    if (cmp(n->value, value) == 0) {
      l->first = n->next;

      if (l->length == 1)
        l->last = NULL;

      aux = n->value;

      free(n);
    }
    else {

      while(n) {
        if (cmp(n->value, value) == 0)
          break;

        ant = n;
        n = n->next;
      }

      if (n) {
        ant->next = n->next;

        if (n->next == NULL)
          l->last = ant;

        aux = n->value;
        free(n);
      }
    }
  }

  return aux;
}

int List_getLength(List *l){
  if (l) 
    return l->length;

  return 0;
}

void List_print(List *l, void (*print)(void*)){
  Node *n = NULL;

  if (l) {
    n = l->first;

    while(n) {
      print(n->value);
      n = n->next;
    }

    printf("\n");
  }
}

// Função recursiva para contar nós
static int count_nodes(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + count_nodes(node->next);
}

// Função que chama a função recursiva
int List_count(List *l) {
    if (l == NULL) {
        return 0;
    }
    return count_nodes(l->first);
}

static void invert_nodes(Node** head_ref) {
  Node* first = *head_ref;
  if (first == NULL || first->next == NULL) {
      return; // Caso base: lista vazia ou com um único nó
  }

  Node* rest = first->next;
  invert_nodes(&rest);
  first->next->next = first;
  first->next = NULL;

  *head_ref = rest;
}

int List_invert(List* l) {
  if (l == NULL) {
      return 0;
  }

  invert_nodes(&l->first);

  // Atualizar l->last após a inversão
  Node* temp = l->first;
  if (temp == NULL) {
      l->last = NULL;
  } else {
      while (temp->next != NULL) {
          temp = temp->next;
      }
      l->last = temp;
  }

  return 0;
}