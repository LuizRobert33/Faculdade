// 1° Questão
// Calcula os sorvedouros
bool* calcIsSink(Graph G) {
    bool* isSink = malloc(G->V * sizeof(bool));
    for (vertex v = 0; v < G->V; ++v) {
        bool sink = true;
        for (vertex w = 0; w < G->V; ++w) {
            if (G->adj[v][w] != 0) {
                sink = false;
                break;
            }
        }
        isSink[v] = sink;
    }
    return isSink;
}

// Calcula as fontes
bool* calcIsSource(Graph G) {
    bool* isSource = malloc(G->V * sizeof(bool));
    for (vertex v = 0; v < G->V; ++v) {
        bool source = true;
        for (vertex w = 0; w < G->V; ++w) {
            if (G->adj[w][v] != 0) {
                source = false;
                break;
            }
        }
        isSource[v] = source;
    }
    return isSource;
}


// 2° Questão Função  GRAPHundir() 
bool GRAPHundir(Graph G) {
    for (vertex v = 0; v < G->V; ++v) {
        for (vertex w = 0; w < G->V; ++w) {
            if (G->adj[v][w] != G->adj[w][v]) {
                return false;  
            }
        }
    }
    return true; 
}


// 3° Questão  GRAPHequal()
bool GRAPHequal(Graph G, Graph H) {
    if (G->V != H->V || G->A != H->A) {
        return false; 
    }
    for (vertex v = 0; v < G->V; ++v) {
        for (vertex w = 0; w < G->V; ++w) {
            if (G->adj[v][w] != H->adj[v][w]) {
                return false;
            }
        }
    }
    return true;
}

// 4° Questão GRAPHrandTournament()
Graph GRAPHrandTournament(int V) {
    Graph G = GRAPHinit(V);
    
    for (vertex v = 0; v < V; v++) {
        for (vertex w = v + 1; w < V; w++) {
            
            if (rand() % 2) {
                G->adj[v][w] = 1;  // Aresta v->w
                G->adj[w][v] = 0;
            } else {
                G->adj[v][w] = 0;
                G->adj[w][v] = 1;  // Aresta w->v
            }
            G->A++;
        }
    }
    return G;
}

// 5° Questão 
vertex GRAPHfindRoot(Graph G) {
    for (vertex v = 0; v < G->V; ++v) {
        bool isRoot = true;
        
        for (vertex w = 0; w < G->V; ++w) {
            if (G->adj[w][v]) {  // Se existe aresta w->v
                isRoot = false;
                break;
            }
        }

        if (isRoot) return v;
    }
}

// 6° Questão PLUS++
bool GRAPHcheckTopological(Graph G, vertex* vv) {
    for (int i = 0; i < G->V; i++) {
        for (int j = i + 1; j < G->V; j++) {
            
            if (G->adj[vv[j]][vv[i]]) {
                return false;  
            }
        }
    }
    return true;  
}

