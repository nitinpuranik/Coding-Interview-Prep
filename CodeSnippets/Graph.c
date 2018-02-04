// BFS applications: Connected components, two coloring (bipartite). Shortest path from root to any node in undirected graph.
// DFS applications: Connected components, finding cycles, given (x,y) who is an ancestor, how many descendants (exit - entry - 1)/2.
// Finding cycles: If an edge is a back-edge, we have a cycle. If entry(x) < entry(y) && exit(x) > exit(y), x is an ancestor of y.

#include <stdio.h>
#include <stdlib.h>

#define MAXV 50

// Consider our sample triangular graph below.
//        1
//       / \
//      /   \
//     2-----3
// For a graph of this nature, the adjacency matrix looks like:
// 1 : 2 --> 3
// 2 : 1 --> 3
// 3:  1 --> 2
// So for each node, we have a linked list of its adjacent neighbor nodes.
// In all, we would have as many such linked lists as there are nodes.
// Each item in this linked list is represented by 'struct edgenode' below.

typedef struct {
  int y;                  // Value of the node.
  int weight;             // Weight of the edge between the originating node and this node.
  struct edgenode *next;  // Pointer to the next neighboring node of the originating node in the linked list.
} edgenode_t;

// Here is the data structure that represents a graph.
typedef struct {
  edgenode *edges[MAXV + 1];  // An array of pointers to the heads of the linked lists for each node.
  unsigned degree[MAXV + 1];  // An array to store the degree of each node.
  unsigned nvertices;         // Total number of vertices.
  unsigned nedges;            // Total number of edges.
  bool directed;              // Is the graph directed or undirected.
} graph_t;

// An alternative definition of the graph structure with less space wastage but more dynamic memory management.
typedef struct {
  edgenode_t **adjlist;
  unsigned int *nodedegree;
  unsigned int nvertices;
  unsigned int nedges;
  bool directed;
} graph_t;

typedef enum {
  undiscovered,
  discovered,
  processed
} state_t;

typedef enum {
  black,
  white,
  uncolored
} color_t;

// Checking if the graph is bipartite is an application of BFS.
void Bipartite(graph *g) {
  bool bipartite = TRUE;
  unsigned int i;
  color_t colors[g->nvertices + 1];

  for (i = 1; i <= g->nvertices; i++) {
    colors[i] = uncolored;
  }

  for (i = 1; i <= g->nvertices; i++) {
    if (state[i] == undiscovered) {
      colors[i] = white;
      bfs(g, i);
    }
  }
}

void process_edge(int x, int y) {
  if (colors[x] == colors[y]) {
    bipartite = FALSE;
    printf("Warning: Not a bipartite graph.\n");
  } else {
    colors[y] = (colors[x] == white) ? black : white;
  }
}

/* Data structures for DFS. */
static unsigned time = 0;
int parent[MAXV + 1];
state_t state[MAXV + 1];
unsigned entry[MAXV + 1];
unsigned exit[MAXV + 1];

/* Initialize routine for DFS. */
void initialize(graph *g) {
  int i;

  for (i = 1; i <= g->nvertices; i++) {
    parent[i] = -1;
    state[i] = undiscovered;
  }
}

// How to check if a graph edge is a tree edge or a back edge?
// Given an edge (u,v), if v is undiscovered, then (u,v) will be
// a tree edge. If v is discovered AND if parent[u] == v, then (u,v)
// is still a tree edge. Else it is a back edge, because the discovered node
// v will be an ancestor in the DFS tree. You can write this code in process_edge.
void dfs(graph *g, int u) {
  edgenode *edge;
  int v;

  state[u] = discovered;
  entry[u] = time++;

  edge = g->edges[u];
  while (edge) {
    v = edge->y;

    if (state[v] != processed || g->directed) {
      // Note that for a graph such as 1 -- 2, you will end up calling process_edge twice.
      // Once for (g, 1, 2) and once for (g, 2, 1). To avoid duplication of effort, in the
      // function process_edge(), you can check if parent[u] == v and simply return if yes.
      process_edge(g, u, v);
    }
    
    if (state[v] == undiscovered) {
      parent[v] = u;
      dfs(g, v);
    }

    edge = edge->next;
  }

  state[u] = processed;
  exit[u] = time++;
}

void bfs(graph *g, int start) {
  queue_t q;
  int i, u, v;
  edgenode *edge;
  state_t state[g->nvertices + 1];
  int parent[g->nvertices + 1];

  for (i = 1; i <= g->nvertices; i++) {
    state[i] = undiscovered;
    parent[i] = -1;
  }

  state[start] = discovered;
  enqueue(q, start);

  while(!is_empty(q)) {
    u = dequeue(q);
    edge = g->edges[u];

    while(edge) {
      v = edge->y;

      /*
       * Convince yourself with the above triangular graph diagram that the edge (u,v) is a
       * new edge only if the node v is not processed or if the graph is a directed graph.
       * If node v is processed, then for an undirected graph, you've already processed all edges from v, including edge (v,u).
       * If node v is only in a discovered state in an undirected graph, then you've reached node v through
       * some edge other than (u,v). So you can process this new edge (u,v) even if v is in the discovered state.
       */
      if (state[v] != processed || g->directed) {
        /*
         * If v is discovered but not processed, it means this edge won't figure in the BFS tree.
         * We hit this function call surely once for every new edge.
         */
        process_edge(g, u, v);
      }

      // We enqueue the node only if it is undiscovered. If it is discovered, it means we already
      // hit this node through some edge other than (u,v) and it should already have been enqueued.
      if (state[v] == undiscovered) {
        state[v] = discovered;
        enqueue(q, v);
        parent[v] = u;
      }

      edge = edge->next;
    }

    state[u] = processed;
  }
}

// Connected components is an application of BFS.
unsigned Connected_Components (graph *g) {
  unsigned conn = 0;
  unsigned i;

  for (i = 1; i <= g->nvertices; i++) {
    if (state[i] == undiscovered) {
      conn++;
      printf("Component %u:", conn);
      bfs(g, i);
      printf("\n");
    }
  }

  return conn;
}

void insert_edge (graph *g, int x, int y, bool directed) {
  edgenode *edge;

  if (g == NULL) {
    return;
  }

  edge = (edgenode*) malloc (sizeof(edgenode));
  edge->y = y;
  edge->weight = 0;

  edge->next = g->edges[x];
  g->edges[x] = edge;

  g->degree[x]++;

  if (directed == false) {
    insert_edge (g, y, x, true);
  }
}

// Finding the shortest path from the root to any node is one of the things BFS gives us.
void FindShortest (int start, int end, int *parent) {
  if (start == end || end == -1) {
    printf("%d", start);
  } else {
    FindShortest (start, parent[end], parent);
    printf(" --> %d", end);
  }
}

void Initialize_Graph(graph *g) {
  int i;

  if (g == NULL) {
    return;
  }

  // Accept user arguments on graph parameters.
  scanf("Directed: %d\n", &(g->directed));
  scanf("Num vertices: %d\n", &(g->nvertices));
  scanf("Num edges: %d\n", &(g->nedges));

  // Initialize the graph to predetermined values.
  for (i = 1; i <= g->nvertices; i++) {
    g->edges[i] = NULL;
    g->degree[i] = 0;
  }

  // Get the graph's edge layout input from the user.
  for (i = 0; i < g->nedges; i++) {
    int x, y;
    printf("Edge %u:\n", i + 1);
    scanf("x: %d", &x);
    scanf("y: %d", &y);
    insert_edge(g, x, y, g->directed);
  }
}

bool AreNeighbors(graph *g, int x, int y) {
  edgenode *edge;
  
  if (g == NULL) {
    printf("Invalid graph.\n");
    return false;
  }
  
  edge = g->edges[x];

  while(edge) {
    if (edge->y == y) {
      return true;
    }
    edge = edge->next;
  }
  
  return false;
}