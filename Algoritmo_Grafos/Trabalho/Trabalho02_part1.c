/* Questão 01

Se G tem 1 vértice → retorna apenas esse vértice (árvore trivial).
Se G não tem arcos → somente o vértice-fonte é alcançável.
Se G é árvore com 2 vértices → retorna a própria árvore.
Se G é árvore com 3 vértices → retorna a própria árvore.
Em todos os casos, GRAPHspt() produz o resultado correto.

*/ 

/* Questão 02

Se o grafo é não ponderado e o algoritmo usa BFS,
o teste `dist[w] == INFINITY` é suficiente (primeiro caminho encontrado é ótimo).
Se houver chance de encontrar caminho melhor depois,
deve-se usar `if (dist[v] + 1 < dist[w])` para relaxar a aresta.

*/

// Questão 03
/* Distâncias a partir do vértice 0 */
int dist[10]   = {0, 3, 2, 5, 2, 1, 1, 5, 4, 3};

/* Pais na árvore de caminhos mínimos (-1 para raiz) */
int parent[10] = {-1, 4, 5, 8, 6, 0, 0, 8, 9, 2};

/* Árvore de caminhos mínimos (ASCII)
0
├─5
│  └─2
│     └─9
│        └─8
│           ├─3
│           └─7
└─6
   └─4
      └─1
*/


