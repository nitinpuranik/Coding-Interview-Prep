// https://www.youtube.com/watch?v=Yo7sddEVONg
// See the example weighted graph in the above YT video.
// This implementation has both Kruskal and Disjoint set
// classes. Disjoint sets are needed to check if two
// vertices belong to the same Minimum Spanning Tree.

#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

class Disjoint {
  private:
    struct Node {
      char val;
      int rank;
      Node *parent;

      Node (char x) : val(x), rank(0), parent(nullptr) {}
    };

    unordered_map<char, Node*> umap;
    Node* FindSet (Node*);

  public:
    void MakeSet (char x);
    void Union (char x, char y);
    char FindSet (char x);
};

void Disjoint::MakeSet (char x) {
  if (umap.find(x) != umap.end())
    return;

  Node *newnode = new Node {x};
  newnode->parent = newnode;

  umap[x] = newnode;
}

void Disjoint::Union (char x, char y) {
  if (umap.find(x) == umap.end() ||
      umap.find(y) == umap.end())
    return;

  Node *xnode = FindSet(umap[x]);
  Node *ynode = FindSet(umap[y]);

  if (xnode == ynode)
    return;

  if (xnode->rank > ynode->rank) {
    ynode->parent = xnode;
  }

  else if (xnode->rank < ynode->rank) {
    xnode->parent = ynode;
  }

  else {
    ynode->parent = xnode;
    xnode->rank++;
  }
}

Disjoint::Node* Disjoint::FindSet (Node *node) {
  if (node->parent == node)
    return node;

  /* Path compression. */
  node->parent = FindSet (node->parent);
  return node->parent;
}

char Disjoint::FindSet (char x) {
  if (umap.find(x) == umap.end())
    throw "Invalid set element.";

  Node *xnode = FindSet (umap[x]);

  return xnode->val;
}

class Graph {
  private:
    priority_queue<int, vector<int>, greater<int>> pq;
    unordered_multimap<int, pair<char,char>> umap;
    Disjoint ds;

  public:
    void Insert (int weight, char x, char y);
    void Kruskal ();
};

void Graph::Insert (int weight, char x, char y) {
  pq.push(weight);

  umap.insert({weight, {x,y}});

  ds.MakeSet(x);
  ds.MakeSet(y);
}

void Graph::Kruskal () {
  int sum = 0;
  unordered_multimap<int, pair<char,char>> mstmap;

  while (!pq.empty()) {
    int weight = pq.top();
    pq.pop();

    auto range = umap.equal_range(weight);
    for (auto it = range.first; it != range.second; it++) {
      pair<char,char>& p = it->second;

      if (ds.FindSet(p.first) != ds.FindSet(p.second)) {
        sum += it->first;
        ds.Union(p.first, p.second);
        mstmap.insert({weight, p});
      }
    }
  }

  for (auto entry : mstmap) {
    cout << entry.second.first << " - " << entry.second.second << ": " << entry.first << endl;
  }

  cout << "MST: " << sum << endl;
}

// This graph is from the above YouTube video.
int main() {
  Graph g;

  g.Insert(4, 'a', 'b');
  g.Insert(11, 'b', 'h');
  g.Insert(8, 'a', 'h');
  g.Insert(8, 'b', 'c');
  g.Insert(2, 'c', 'i');
  g.Insert(7, 'h', 'i');
  g.Insert(6, 'i', 'g');
  g.Insert(1, 'h', 'g');
  g.Insert(4, 'c', 'f');
  g.Insert(2, 'f', 'g');
  g.Insert(14, 'd', 'f');
  g.Insert(7, 'c', 'd');
  g.Insert(10, 'f', 'e');
  g.Insert(9, 'd', 'e');

  g.Kruskal();
  return 0;
}