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

int CoinDistroWorker (Node *node, int *totalcost) {
  if (node == nullptr)
    return 0;

  // Optimization. Don't need to call left and right for leaf nodes.
  // Pop-quiz: Why do you not need to update totalcost for leaves? Because
  // when you're at a leaf node, there are no coin movements needed.
  // Only when you get to the inner nodes, will you need to move coins
  // back and forth between leaves and internal nodes.
  if (node->left == nullptr && node->right == nullptr)
    return node->data - 1;

	// Coins available in the left and right subtree. Optimize so you call functions only if children exist.
  int lcredit = 0, rcredit = 0;

  if (node->left)
    lcredit = CoinDistroWorker (node->left, totalcost);

  if (node->right)
    rcredit = CoinDistroWorker (node->right, totalcost);

	// Here we take the absolute values of coins because a +1
	// means a coin is being given out and a -1 means a coin is
  // being requested. Both providing and requesting a coin constitute
	// a move and so we cumulatively sum up the absolute values.
  *totalcost += abs(lcredit) + abs(rcredit);

	// A -1 in the end because every node needs a coin for itself.
  return lcredit + rcredit + node->val - 1;
}

int CoinDistro (Node *node) {
	// This variable goes on cumulatively summing up the absolute values
	// of coins available. This gives us the total number of moves needed
	// or the 'cost' of distribution.
  int totalcost = 0;

  CoinDistroWorker (node, &totalcost);

  return totalcost;
}

int main () {
  Node *node = new Node {0};

  Insert(node, 1, e_left);
  Insert(node, 0, e_right);
  Insert(node->left, 3, e_right);

  cout << CoinDistro (node);
}