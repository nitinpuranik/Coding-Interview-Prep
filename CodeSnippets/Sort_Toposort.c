// Topological sorting is only possible on a DAG (Directed Acyclic Graph).
// Run a DFS. Throw items into a stack as they get processed. Then reverse the stack for the topo order.
// Note that while running DFS, you don't need a visited array. Only a processed array needed.
// This is because in a DAG, you will only visit every node once during an onward recursion.
// If you visit a node the second time during the same onward recursive path, then it's a cycle.
// https://youtu.be/Q9PIxaNGnig
// https://www.geeksforgeeks.org/topological-sorting/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Graph {
  private:
    unordered_map<char, vector<char>> adj;
    void _DFS (char, unordered_set<char>&, vector<char>&);

  public:
    void AddEdge (char u, char v);
    void Topo ();
};

void Graph::AddEdge (char u, char v) {
  adj[u].push_back(v);
}

void Graph::_DFS (char u, unordered_set<char>& processed, vector<char>& vtopo) {
  for (char v : adj[u]) {
    if (processed.find(v) == processed.end()) {
      _DFS (v, processed, vtopo);
    }
  }

  processed.insert (u);
  vtopo.push_back(u);
}

void Graph::Topo () {
  unordered_set<char> processed;
  vector<char> vtopo;

  for (const auto& list : adj) {
    if (processed.find(list.first) == processed.end()) {
      _DFS (list.first, processed, vtopo);
    }
  }

  for (vector<char>::reverse_iterator it = vtopo.rbegin(); it != vtopo.rend(); it++)
    cout << *it << ' ';

  // Or, access the vector in a more straightforward way.
  for (int i = vtopo.size() - 1; i >= 0; i--)
    cout << vtopo[i] << ' ';

  cout << endl;
}

int main() {
  Graph g;

  g.AddEdge ('A', 'B');
  g.AddEdge ('A', 'F');
  g.AddEdge ('G', 'A');
  g.AddEdge ('G', 'B');
  g.AddEdge ('B', 'H');
  g.AddEdge ('G', 'C');
  g.AddEdge ('D', 'C');
  g.AddEdge ('D', 'I');
  g.AddEdge ('D', 'H');
  g.AddEdge ('D', 'E');
  g.AddEdge ('E', 'I');
  g.AddEdge ('J', 'E');
  g.AddEdge ('I', 'C');

  g.Topo();

  return 0;
}