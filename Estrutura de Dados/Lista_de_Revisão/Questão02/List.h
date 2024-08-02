typedef struct List List;
typedef struct Node Node;

List *List_alloc();
void  List_free(List *l);
void  List_insert(List *l, void *value);
void *List_remove(List *l, void *value, int (*cmp)(void*, void*));
int   List_getLength(List *l);
void  List_print(List *l, void (*print)(void*));
int   List_count(List *l);
int List_invert(List* l) ;