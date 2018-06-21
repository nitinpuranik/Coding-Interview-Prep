#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <unordered_map>
using namespace std;

class Graph {
  private:
    bool m_directed;
    unordered_map<int, vector<int>> adj;

  public:
    Graph (bool directed = false) : m_directed (directed) {}

    void AddEdge (int u, int v) {
      adj[u].push_back(v);

      if (m_directed == false)
        adj[v].push_back(u);
    }

    const auto& GetAdjList () const {
      return adj;
    }

    void Print () const;
};

void Graph::Print() const {
  for (const auto& entry : adj) {
    cout << entry.first << ": ";

    for (const int item : entry.second)
      cout << item << ' ';

    cout << endl;
  }
}

bool DFS (Graph& g, int u, int prev) {
  static set<int> visited {u};

  const auto& adjlist = g.GetAdjList();

  for (const auto& v : adjlist.find(u)->second) {
    if (v != prev) {
      if (visited.find(v) != visited.end()) {
        cout << u << " - " << v << " makes a cycle!" << endl;
        return true;
      }

      visited.insert(v);

      if (DFS (g, v, u))
        return true;
    }
  }

  return false;
}

bool CycleDetected (Graph& g) {
  int u = g.GetAdjList().begin()->first;

  return DFS (g, u, INT_MIN);

}

int main () {
  Graph g;

  g.AddEdge(1,2);
  g.AddEdge(2,3);
  g.AddEdge(3,4);
  g.AddEdge(4,5);
  g.AddEdge(6,5);
  g.AddEdge(6,1);

  g.Print();

  if (CycleDetected(g))
    cout << "Cycle detected." << endl;
  else
    cout << "Cycle not detected." << endl;

  return 0;
}