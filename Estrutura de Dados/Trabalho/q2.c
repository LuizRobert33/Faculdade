#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

typedef struct Player {
  int life;
  float money;
  int id;
  char nickname[20];
} Player;

Player *Player_alloc(int life, float money, int id, char nickname[20]) {
  Player *p = malloc(sizeof(Player));
  if (p) {
    p->life = life;
    p->money = money;
    p->id = id;
    strcpy(p->nickname, nickname);
  }
  return p;
}

void Player_print(void *a) {
  Player *p = a;
  printf("%s ", p->nickname);
}

int Player_cmp(void *a, void *b) {
  Player *p = a;
  int *id = b;
  return p->id - *id;
}

int main() {
  List *l = List_alloc();

  Player p[] = {
    {100, 100.0, 1, "happyberto"},
    {100, 100.0, 2, "pineapple"},
    {100, 100.0, 3, "blaze"},
    {100, 100.0, 4, "P4uloR3gis"},
    {100, 100.0, 5, "KRBL"}
  };

  List_insert(l, &p[0]);
  List_insert(l, &p[1]);
  List_insert(l, &p[2]);
  List_insert(l, &p[3]);
  List_insert(l, &p[4]);


  printf("Lista de jogadores:\n");
  List_print(l, Player_print);

  printf("Número de elementos na lista: %d\n", List_count(l));


  int id = 3;
  List_remove(l, &id, Player_cmp);

  List_free(l);

  return 0;
}
