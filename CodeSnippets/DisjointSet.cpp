// C++ implementation of Disjoint set operations.
// Disjoint sets are data structures that support these operations:
// FindSet(data): Returns the representative element of the set that 'data' belongs to.
// Union(data1, data2): If data1 and data2 belong to two different sets, then combine them into one set.
// MakeSet(data): Create a standalone set containing 'data'.
// See https://youtu.be/ID00PMy0-vE for an introduction to disjoint sets.

#include <iostream>
#include <unordered_map>
using namespace std;

typedef struct node {
  int data;
  unsigned rank;
  struct node *parent;
} Node;

unordered_map<int, Node*> nodemap;

void MakeSet (int data) {
  Node *newnode = new Node;
  
  newnode->data = data;
  newnode->rank = 0;
  newnode->parent = newnode;
  
  nodemap[data] = newnode;
}

Node* FindSet (Node *node) {
  if (node == nullptr)
    return nullptr;
  
  if (node == node->parent)
    return node;
  
  node->parent = FindSet (node->parent);
  return node->parent;
}

int FindSet (int data) {
  unordered_map<int, Node*>::const_iterator it;
  
  it = nodemap.find(data);
  
  if (it != nodemap.end()) {
    Node *root = FindSet (it->second);
    
    if (root)
      return root->data;
  }
  
  return 0xdeadbeef;
}

bool Union (int data1, int data2) {
  Node *node1 = nodemap[data1];
  Node *node2 = nodemap[data2];
  
  if (node1 == nullptr || node2 == nullptr) {
    cout << "Invalid input." << endl;
    return false;
  }
  
  Node *parent1 = FindSet(node1);
  Node *parent2 = FindSet(node2);
  
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
  MakeSet(1);
  MakeSet(2);
  MakeSet(3);
  MakeSet(4);
  MakeSet(5);
  MakeSet(6);
  MakeSet(7);

  Union(1, 2);
  Union(2, 3);
  Union(4, 5);
  Union(6, 7);
  Union(5, 6);
  Union(3, 7);

  cout << FindSet(1) << endl;
  cout << FindSet(2) << endl;
  cout << FindSet(3) << endl;
  cout << FindSet(4) << endl;
  cout << FindSet(5) << endl;
  cout << FindSet(6) << endl;
  cout << FindSet(7) << endl;
}