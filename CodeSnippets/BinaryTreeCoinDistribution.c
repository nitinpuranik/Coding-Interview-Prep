// https://leetcode.com/articles/distribute-coins-in-binary-tree/
// https://medium.com/algorithm-and-datastructure/distribute-coins-in-binary-tree-9a5af0114c3c
// Below are some sample trees with expected values.
//     0      0      3      0
//    /      /      /      / \
//   0 = 3  3 = 2  0 = 3  1   0 = 5
//  /      /      /        \
// 3      0      0          3

#include <iostream>
#include <cstdlib>
using namespace std;

// Handy direction specifier to quickly build the tree you want.
enum dir_t { e_left, e_right };

struct Node {
  int val;
  Node *left;
  Node *right;

  Node (int x) : val(x), left(nullptr), right(nullptr) {}
};

void Insert (Node *node, int val, dir_t dir) {
  Node *newnode = new Node {val};

  if (dir == e_left)
    node->left = newnode;
  else
    node->right = newnode;
}

int BalanceTreeWorker (Node *node, int *totalcost) {
  if (node == nullptr)
    return 0;

	// Coins available in the left and right subtree.
  int lcredit = BalanceTreeWorker (node->left, totalcost);
  int rcredit = BalanceTreeWorker (node->right, totalcost);

	// Here we take the absolute values of coins because a +1
	// means a coin is being given out and a -1 means a coin is
  // being requested. Both providing and requesting a coin constitute
	// a move and so we cumulatively sum up the absolute values.
  *totalcost += abs(lcredit) + abs(rcredit);

	// A -1 in the end because every node needs a coin for itself.
  return lcredit + rcredit + node->val - 1;
}

int BalanceTree (Node *node) {
	// This variable goes on cumulatively summing up the absolute values
	// of coins available. This gives us the total number of moves needed
	// or the 'cost' of distribution.
  int totalcost = 0;

  BalanceTreeWorker (node, &totalcost);

  return totalcost;
}

int main () {
  Node *node = new Node {0};

  Insert(node, 1, e_left);
  Insert(node, 0, e_right);
  Insert(node->left, 3, e_right);

  cout << BalanceTree (node);
}