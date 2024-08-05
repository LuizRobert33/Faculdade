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
    Player *p = (Player *)a;
    printf("%s ", p->nickname);
}

int main() {
    List *l1 = List_alloc();
    List *l2 = List_alloc();

    Player p1[] = {
        {100, 100.0, 1, "happyberto"},
        {100, 100.0, 2, "pineapple"},
        {100, 100.0, 3, "blaze"}
    };

    Player p2[] = {
        {100, 100.0, 4, "P4uloR3gis"},
        {100, 100.0, 5, "KRBL"}
    };

    for (int i = 0; i < 3; i++) {
        List_insert(l1, &p1[i]);
    }

    for (int i = 0; i < 2; i++) {
        List_insert(l2, &p2[i]);
    }

    printf("Lista 1:\n");
    List_print(l1, Player_print);

    printf("Lista 2:\n");
    List_print(l2, Player_print);

    List *l3 = List_concat(l1, l2);
    printf("Lista concatenada:\n");
    List_print(l3, Player_print);

    List_free(l1);
    List_free(l2);
    List_free(l3);

    return 0;
}
