//Arquivo de assinaturas

#define vertex int

struct graph {
	int V;
	int A;
	int **adj;
};

typedef struct graph *Graph;

static int **MATRIXint( int r, int c, int val);
Graph GRAPHinit( int V);
void GRAPHinsertArc( Graph G, vertex v, vertex w);
void GRAPHremoveArc( Graph G, vertex v, vertex w);
void GRAPHshow( Graph G);
void GRAPHindeg(Graph G, int v[]);
Graph GRAPHrand(int V, int A);
void printMatriz(Graph G);
