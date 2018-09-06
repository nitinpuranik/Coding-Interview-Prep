// BFS applications: Connected components, two coloring (bipartite). Shortest path from root to any node in undirected graph.
// DFS applications: Connected components, finding cycles, given (x,y) who is an ancestor, how many descendants (exit - entry - 1)/2.
// If entry(x) < entry(y) && exit(x) > exit(y), x is an ancestor of y.

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

// Implement DFS such that we visit each node and each edge once and only once. This needs visited and processed arrays and previous node. Leaving any one of these out will result in some use-case failing. Try with the below graph. Pay attention to how you get to 5 recursively from 2 through 3. You need to process the new edge 5 - 2. Check if 2 is processed, if not then 5 - 2 is a new edge. Process it. As you return from recursive calls, you come to 2 and see the 2 - 5 edge. Check if 5 is processed. Since it is, don't process the edge 2 - 5. This use case doesn't need the previous node. But if you visit 2 from 1 and then look at neighbor 1, then using visited and processed semantics alone won't suffice. You do need the help of 'previous'.

// 1--2--3
// |  |  |
// 6  5--4

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

// How to check if a graph edge is a tree edge or a back edge?
// In other words, how to check if a graph has a cycle?
// Given an edge (u,v), if v is undiscovered, then (u,v) will be
// a tree edge. If v is discovered AND if parent[u] == v, then (u,v)
// is still a tree edge. Else it is a back edge, because the discovered node
// v will be an ancestor in the DFS tree. You can write this code in process_edge.
// A graph with a back edge is nothing but a graph with a cycle.
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

// Finding the shortest path from the root to any node is one of the things BFS gives us.
void FindShortest (int start, int end, int *parent) {
  if (start == end || end == -1) {
    printf("%d", start);
  } else {
    FindShortest (start, parent[end], parent);
    printf(" --> %d", end);
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
//------------------------------------------------
#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <unordered_map>
using namespace std;

class Graph {
  private:
    bool m_directed;
    unordered_map<int, vector<int>> adj;

    void _DFS_node (int u); // Visits every node once. Doesn't visit all edges.
    void _DFS_node_edge (int u, int prev); // Visits every node and edge once.
    bool _DFS_Cycle (int u, int prev); // Detects if there is a cycle in the graph.

    void _BFS_node(); // Visits every node once. Doesn't visit all edges.
    void _BFS_node_edge(); // Visits every node and edge once.

  public:
    Graph (bool directed = false) : m_directed (directed) {}

    void AddEdge (int u, int v) {
      adj[u].push_back(v);

      if (m_directed == false)
        adj[v].push_back(u);
    }

    const auto& GetAdjList () {
      return adj;
    }

    void Print();
    void DFS();
    void BFS();
};

void Graph::Print() {
  for (const auto& entry : adj) {
    cout << entry.first << ": ";

    for (const int item : entry.second)
      cout << item << ' ';

    cout << endl;
  }
}

// Visits every node once. Doesn't visit all edges.
void Graph::_DFS_node (int u) {
  static set<int> visited {u};

  for (const int v : adj[u]) {

    if (visited.find(v) == visited.end()) {
      cout << "Visited node " << v << endl;

      visited.insert(v);

      _DFS_node (v);
    }
  }
}

// Visits every node and edge once.
void Graph::_DFS_node_edge (int u, int prev) {
  static set<int> visited {u};
  static set<int> processed;

  for (int v : adj[u]) {
    if (v != prev) {
      if (processed.find(v) == processed.end()) {
        cout << "Processed edge " << u << " - " << v << endl;
      }

      if (visited.find(v) == visited.end()) {
        cout << "Visited node " << v << endl;

        visited.insert(v);
        _DFS_node_edge (v, u);
      }
    }
  }

  processed.insert(u);
}

// Detects if there is a cycle in the graph.
bool Graph::_DFS_Cycle (int u, int prev) {
  static set<int> visited {u};

  for (int v : adj[u]) {
    if (v != prev) {
      if (visited.find(v) != visited.end()) {
        cout << u << " - " << v << " makes a cycle!" << endl;
        return true;
      }

      cout << "Visited node " << v << endl;
      visited.insert(v);

      if (_DFS_Cycle (v, u))
        return true;
    }
  }

  return false;
}

void Graph::DFS() {
  int startnode = adj.begin()->first;

  // Call this method if you need to visit all nodes.
  cout << "Visited node " << startnode << endl;
  _DFS_node (startnode);

  // Call this method if you need to visit all nodes and edges.
  cout << endl;
  cout << "Visited node " << startnode << endl;
  _DFS_node_edge (startnode, INT_MIN);

  // Call this method if you need to check for cycles.
  cout << endl;
  cout << "Visited node " << startnode << endl;
  if (_DFS_Cycle (startnode, INT_MIN) == false) {
    cout << "No cycle." << endl;
  }
}

void Graph::_BFS_node_edge() {
  unordered_set<int> visited;
  unordered_set<int> processed;
  queue<int> q;

  int first = adj.begin()->first;

  cout << "Visited " << first << endl;
  visited.insert(first);
  q.push(first);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      //        1
      //       / \
      //      /   \
      //     2-----3
      // Convince yourself with the above triangular graph diagram that the edge (u,v) is a
      // new edge only if the node v is not processed or if the graph is a directed graph.
      // If node v is processed, then for an undirected graph, you've already processed all edges from v, including edge (v,u).
      // If node v is only in a discovered state in an undirected graph, then you've reached node v through
      // some edge other than (u,v). So you can process this new edge (u,v) even if v is in the discovered state.
      //
      if (processed.find(v) == processed.end() || m_directed) {
        // We satisfy this if-conditional once for every unique edge.
        // If v is discovered but not processed, it means this edge won't figure in the BFS tree.
        cout << "Processed edge " << u << "-" << v << endl;
      }

      // We enqueue the node only if it is not visited. If it is visited, it means we already
      // hit this node through some edge other than (u,v) and it should already have been enqueued.
      // Or, in the case of 1 - 2 graph, we came to 2 from 1 and are now looking back at 1.
      if (visited.find(v) == visited.end()) {
        cout << "Visited " << v << endl;
        visited.insert(v);
        q.push(v);
      }
    }

    processed.insert(u);
  }
}

void Graph::_BFS_node() {
  int first = adj.begin()->first;
  queue<int> q;
  unordered_set<int> visited;

  visited.insert(first);
  q.push(first);

  cout << "Visited " << first << endl;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      if (visited.find(v) == visited.end()) {
        cout << "Visited " << v << endl;

        visited.insert(v);
        q.push(v);
      }
    }
  }
}

void Graph::BFS() {
  _BFS_node(); // Visits every node once. Doesn't visit all edges.

  _BFS_node_edge(); // Visits every node and edge once.
}

int main () {
  Graph g;

  g.AddEdge(1,2);
  g.AddEdge(2,3);
  g.AddEdge(3,4);
  g.AddEdge(4,5);
  g.AddEdge(5,6);
  g.AddEdge(6,1);

  g.DFS();

  return 0;
}