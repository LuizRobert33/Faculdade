//Arquivo de implementações

#include <stdio.h>
#include "matriz.h"
#include <stdlib.h>
#include <time.h>


static int **MATRIXint( int r, int c, int val) {
   int **m = malloc ( r * sizeof (int *) );
   for ( vertex i = 0; i < r; ++i)
      m[i] = malloc ( c * sizeof (int) );
   for ( vertex i = 0; i < r; ++i)
      for ( vertex j = 0; j < c; ++j)
         m[i][j] = val;
   return m;
}

Graph GRAPHinit( int V) {
   Graph G = malloc ( sizeof *G);
   G->V = V;
   G->A = 0;
   G->adj = MATRIXint( V, V, 0);
   return G;
}

void GRAPHinsertArc( Graph G, vertex v, vertex w) {
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1;
      G->A++;
   }
}

void GRAPHremoveArc( Graph G, vertex v, vertex w) {
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0;
      G->A--;
   }
}

void GRAPHshow( Graph G) {
   for ( vertex v = 0; v < G->V; ++v) {
      printf ( "%2d:" , v);
      for ( vertex w = 0; w < G->V; ++w)
         if (G->adj[v][w] == 1)
            printf ( " %2d" , w);
         printf ( "\n" );
      }
}

Graph GRAPHrand(int V, int A){
    Graph G = GRAPHinit(V);
    srand(time(NULL));
    while(G->A < A){
        vertex v = rand() % V;
        vertex w = rand() % V;
        if(v != w){
            GRAPHinsertArc(G, v, w);
        }
    }
    return G;
}

void GRAPHindeg(Graph G, int v[]){
    int cont = 0;
    for( vertex w = 0; w < G->V;++w){
        for( vertex v = 0; v < G->V;++v){
            cont += G->adj[v][w];
        }
        v[w] = cont;
        cont = 0;
    }
}

void printMatriz(Graph G){
    for(int i = 0; i < G->V; ++i){
        for(int j = 0; j < G->V; ++j){
            printf("%d ", G->adj[i][j]);
        }
        printf("\n");
    }
}
