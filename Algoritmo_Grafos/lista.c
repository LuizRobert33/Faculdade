#include <stdio.h>
#include "lista.h"
#include <stdlib.h>
#include <time.h>


static link NEWnode( vertex w, link next) {
   link a = malloc( sizeof (struct node));
   a->w = w;
   a->next = next;
   return a;
}


Graph GRAPHinit( int V) {
   Graph G = malloc( sizeof *G);
   G->V = V;
   G->A = 0;
   G->adj = malloc( V * sizeof (link));
   for (vertex v = 0; v < V; ++v)
      G->adj[v] = NULL;
   return G;
}

void GRAPHdestroy(Graph G){
    for(vertex v = 0; v < G->V; v++){
        link a = G->adj[v];
        while(a != NULL){
            link next = a->next;
            free(a);
            a = next;
        }
    }
    free(G->adj);
    free(G);
}

void GRAPHinsertArc( Graph G, vertex v, vertex w) {
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (a->w == w)
         return;
      G->adj[v] = NEWnode( w, G->adj[v]);
      G->A++;
}

void GRAPHremoveArc (Graph G, vertex v, vertex w) {
  link p, q = NULL;
    for (p = G->adj[v]; p != NULL; p = p->next) {
      if (p->w == w) {
        if (q == NULL)
          G->adj[v] = p->next;
        else
          q->next = p->next;
        p = NULL;
        free(p);
        return;
      }
      q = p;
    }
}

void GRAPHshow( Graph G) {
   vertex v;
   for (v = 0; v < G->V; ++v) {
      printf("%d: ", v);
      for (link a = G->adj[v]; a != NULL; a = a->next)
         printf("%2d ", a->w);
      printf("\n");
   }
}

Graph GRAPHrand( int V, int A){
    Graph G = GRAPHinit( V);
    srand(time(NULL));
    while(G->A < A) {
        vertex v = rand() % V;
        vertex w = rand() % V;
        if(v != w)
            GRAPHinsertArc( G, v, w);
    }
    return G;
}

int GRAPHoutdeg( Graph G, vertex v){ //CALCULA GRAUS DE SAIDA DE UM VERTICE
    int outdeg = 0;

    for(link a = G->adj[v]; a != NULL; a = a->next)
        outdeg++;

    return outdeg;
}

int GRAPHindeg (Graph G, vertex v){  //CALCULA GRAUS DE ENTRADA DE UM GRAFO 
    int indeg = 0;

    for (vertex q = 0 ; q < G->V; ++q)
        for(link a = G->adj[q]; a != NULL; a = a->next)
            if(a->w == v)
                indeg++;

    return indeg;
}

void GRAPHoutdegs( Graph G, int vec[]){ //CALCULA GRAUS DE SAIDA DE UM VERTICE, e passa os em um vetor
    for(vertex v = 0; v < G->V; v++){
        vec[v] = GRAPHoutdeg(G, v);
    }
}

void GRAPHindegs(Graph G, int vec[]){  //CALCULA GRAUS DE ENTRADA DE UM GRAFO , e passa os em um vetor
    for(vertex v = 0; v < G->V; v++){
        vec[v] = GRAPHindeg(G, v);
    }
}

int isTopoNumbering( Graph G, int topo[]) {
    for (vertex v = 0; v < G->V; ++v)
        for (link a = G->adj[v]; a != NULL; a = a->next)
            if (topo[v] >= topo[a->w])
                return 0;
    return 1;
}

int topo[1000];

int topol( Graph G) {
    for (vertex v = 0; v < G->V; ++v)
        topo[v] = -1;

    int cnt = 0;
    vertex v;
    while (cnt < G->V) {

        for ( v = 0; v < G->V; ++v)
            if (GRAPHindeg( G, v) == 0 && topo[v] == -1)
                break;
        if (v >= G->V) return 0;
        // v é fonte
        topo[v] = cnt++;
        for (link a = G->adj[v]; a != NULL; a = a->next)
            GRAPHremoveArc( G, v, a->w);
    }
    return 1;
}

void calcSink(Graph G, int issink[]){
    for(vertex v = 0; v < G->V; v++){
        if(GRAPHoutdeg(G, v) == 0){
            issink[v] = 1;
        }else{
            issink[v] = 0;
        }
    }        
}

void calcSource(Graph G, int issource[]){
    for(vertex v = 0; v < G->V; v++){
        if(GRAPHindeg(G, v) == 0){
            issource[v] = 1;
        }else{
            issource[v] = 0;
        }
    }  
}

int GRAPHundir(Graph G){
    for (vertex v = 0 ; v < G->V; ++v){
        for(link a = G->adj[v]; a != NULL; a = a->next){
            vertex u = a->w;
            int found = 0;
            for(link b = G->adj[u]; b != NULL; b = b->next){
                if(b->w == v){
                    found = 1;
                    break;
                }
            }
            if (!found) {
                return 0;
            }
        }
    }
    return 1;     
}

Graph buildCompleteDirGRAPH(vertex v){ //Cria um grafocompletoDIRECIONADO
    Graph G = GRAPHinit(v);
    for(vertex u = 0; u < G->V; u++){
        for(vertex w = 0; w < G->V; w++){  
            if(u == w)
                continue;
            G->adj[u] = NEWnode( w, G->adj[u]);
            G->A++;
        }
    }
    return G;
}

Graph buildCompleteUndGRAPH(vertex v){ //Cria um grafocompletoDIRECIONADO
    Graph G = GRAPHinit(v);
    for(vertex u = 0; u < G->V; u++){
        for(vertex w = u + 1; w < G->V; w++){  
            G->adj[u] = NEWnode( w, G->adj[u]);
            G->adj[w] = NEWnode( u, G->adj[w]);
            G->A += 2;
        }
    }
    return G;
}

int visited[1000]; 

void reachR( Graph G, vertex v){  
    visited[v] = 1; 
    for (link a = G->adj[v]; a != NULL; a = a->next) 
        if (visited[a->w] == 0) 
            reachR( G, a->w); 
} 

int GRAPHreach( Graph G, vertex s, vertex t){  
    for (vertex v = 0; v < G->V; ++v) 
        visited[v] = 0; 
    reachR( G, s); 
    if (visited[t] == 0) 
        return 0; 
    else 
        return 1; 
} 