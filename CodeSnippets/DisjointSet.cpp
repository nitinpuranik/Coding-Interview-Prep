// C++ implementation of Disjoint set operations.
// Disjoint sets are data structures that support these operations:
// FindSet(data): Returns the representative element of the set that 'data' belongs to.
// Union(data1, data2): If data1 and data2 belong to two different sets, then combine them into one set.
// MakeSet(data): Create a standalone set containing 'data'.
// See https://youtu.be/ID00PMy0-vE for an introduction to disjoint sets.

#include <iostream>
#include <unordered_map>
using namespace std;

class DisjointSet {
  private:
    struct Node {
      int data;
      unsigned rank;
      struct node *parent;
    };

    unordered_map<int, Node*> umap;
    Node* FindSet (Node *node);

  public:
    int FindSet (int data);
    bool Union (int data1, int data2);
    void MakeSet (int data);
};

void DisjointSet::MakeSet (int data) {
  Node *newnode = new Node;
  newnode->data = data;
  newnode->rank = 0;
  newnode->parent = newnode;

  umap[data] = newnode;
}

int DisjointSet::FindSet (int data) {
  Node *node = umap[data];

  if (node == nullptr) {
    cout << data << ": Invalid parameter!" << endl;
    return 0xdeadbeef;
  }

  Node *root = FindSet(node);

  return root->data;
}

DisjointSet::Node* DisjointSet::FindSet (Node *node) {
  if (node == nullptr)
    return nullptr;

  if (node->parent == node)
    return node;

  node->parent = FindSet (node->parent);
  return node->parent;
}

bool DisjointSet::Union (int data1, int data2) {
  Node *node1 = umap[data1];
  Node *node2 = umap[data2];

  if (node1 == nullptr || node2 == nullptr)
    return false;

  Node *parent1 = FindSet (node1);
  Node *parent2 = FindSet (node2);

  if (parent1 == parent2)
    return false;

  if (parent1->rank >= parent2->rank) {
    parent1->rank = (parent1->rank == parent2->rank) ?
                    parent1->rank + 1 : parent1->rank;
    parent2->parent = parent1;
  } else {
    parent1->parent = parent2;
  }

  return true;
}

int main() {
  DisjointSet ds;

  ds.MakeSet(1);
  ds.MakeSet(2);
  ds.MakeSet(3);
  ds.MakeSet(4);
  ds.MakeSet(5);
  ds.MakeSet(6);
  ds.MakeSet(7);

  ds.Union(1, 2);
  ds.Union(2, 3);
  ds.Union(4, 5);
  ds.Union(6, 7);
  ds.Union(5, 6);
  ds.Union(3, 7);

  cout << ds.FindSet(1) << endl;
  cout << ds.FindSet(2) << endl;
  cout << ds.FindSet(3) << endl;
  cout << ds.FindSet(4) << endl;
  cout << ds.FindSet(5) << endl;
  cout << ds.FindSet(6) << endl;
  cout << ds.FindSet(7) << endl;
}