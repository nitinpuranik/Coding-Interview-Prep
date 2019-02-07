/*
How do you determine the successor of a node in a BST? See implementation of Successor later in the document.
- If the node has a right subtree, then the leftmost child in the right subtree would be the successor.
- If the node has no right subtree and the node is the left child of its parent, then the parent would be the successor.
- If the node has no right subtree and the node is the right child of its parent, then the closest ancestor whose left subtree this node resides in would be the successor.

How do you determine the predecessor of a node in a BST?
- If the node has a left subtree, then the rightmost child in the left subtree would be the predecessor.
- If the node has no left subtree and the node is the right child of its parent, then the parent would be the predecessor.
- If the node has no left subtree and the node is the left child of its parent, then the closest ancestor whose right subtree this node resides in would be the predecessor.
*/

#include <iostream>
#include <vector>
using namespace std;

/*
 * In a BST, nodes in left subtree <= parent.
 * Nodes in right subtree >= parent.
 */

struct Node {
  int data;
  Node *left;
  Node *right;
};

void Insert (Node **node, int data) {
  if (node == nullptr)
    return;

  Node *newnode = new Node {data, nullptr, nullptr};
  if (newnode == nullptr)
    return;

  Node *curr, *prev;

  curr = *node;
  prev = nullptr;

  while (curr) {
    prev = curr;
    if (data <= curr->data)
      curr = curr->left;
    else
      curr = curr->right;
  }

  if (prev) {
    if (data <= prev->data)
      prev->left = newnode;
    else
      prev->right = newnode;
  } else {
    *node = newnode;
  }
}

void PrintRange (Node *node, int min, int max) {
  if (node == nullptr) {
    return;
  }

  if (node->data >= min) {
    PrintRange (node->left, min, max);
  }

  if (node->data >= min && node->data <= max) {
    cout << node->data << ' ';
  }

  if (node->data < max) {
    PrintRange (node->right, min, max);
  }
}

int IsBalancedWorker (TreeNode* node, bool *bal) {
  if (node == nullptr)
    return 0;

  int ldepth = IsBalancedWorker (node->left, bal);

  if (*bal == false)
    return 0;

  int rdepth = IsBalancedWorker (node->right, bal);

  if (*bal == false)
    return 0;

  if (ldepth > rdepth + 1 || rdepth > ldepth + 1) {
    cout << "Imbalanced at " << node->data << endl;
    *bal = false;
    return 0;
  }

  return ldepth > rdepth ? ldepth + 1 : rdepth + 1;
}

bool IsBalanced (Node *node) {
  if (node == nullptr)
    return true;

  bool bal = true;

  IsBalancedWorker (node, &bal);

  return bal;
}

Node* Successor (Node *node) {
  if (node == nullptr) {
    return nullptr;
  }

  // Has a right subtree. Return leftmost child.
  if (node->right) {
    Node *child = node->right;

    while (child->left) {
      child = child->left;
    }

    return child;
  }

  // No right subtree. If node is left child of parent, return parent.
  if (node->parent && node->parent->left == node) {
    return node->parent;
  }

  while (node->parent && node->parent->right == node) {
    node = node->parent;
  }

  return node->parent;
}

/*Bloomberg: Copy a graph. Watch out for the cycle between 1 and 2.
    1
   / \
  0---3
     / \
    2   4 */
Node* Duplicate (Node *node) {
  static unordered_map<Node*, Node*> visited;

  if (node == nullptr)
    return nullptr;

  if (visited.find (node) != visited.end())
    return visited[node];

  Node *newnode = new Node {node->data, nullptr, nullptr};

  /* If you put this map insertion operation after the below two recursive calls,
   * you will run into an infinite loop if 4's left child points back to 3. */
  visited[node] = newnode;

  newnode->left  = Duplicate (node->left);
  newnode->right = Duplicate (node->right);

  return newnode;
}

/* Return the max path sum between any two leaves in the tree. */
int MaxPathSumTwoLeavesWorker (Node *node, int *max) {
  if (node == nullptr)
    return INT32_MIN;

  if (node->left == nullptr && node->right == nullptr)
    return node->data;

  int lsum, rsum;
  lsum = MaxPathSumTwoLeavesWorker (node->left, max);
  rsum = MaxPathSumTwoLeavesWorker (node->right, max);

  if (lsum > INT32_MIN && rsum > INT32_MIN) {
    if (lsum + node->data + rsum > *max) {
      *max = lsum + node->data + rsum;
    }

    return lsum > rsum ? lsum + node->data : rsum + node->data;
  }

  if (lsum > INT32_MIN)
    return lsum + node->data;
  else
    return rsum + node->data;
}

/* Return the max path sum between any two leaves in the tree. Worker function above. */
int MaxPathSumTwoLeaves (Node *node) {
  if (node == nullptr)
    return INT32_MIN;

  if (node->left == nullptr && node->right == nullptr)
    return node->data;

  int max = INT32_MIN;
  int ret = MaxPathSumTwoLeavesWorker (node, &max);
  return ret > max ? ret : max;
}

/* Returning a bool helps in ending your search once you find the
 * first max path. Else you'll end up scouring the entire tree even
 * if you find your path at the very beginning.
 * This prints path from root to leaf. */
bool PrintMaxPathSum (Node *node, int sum) {
  static vector<int> pathvec;

  if (node == nullptr)
    return false;

  pathvec.push_back(node->data);

  if (node->left == nullptr && node->right == nullptr) {
    if (sum == node->data) {
      for (int item : pathvec) {
        cout << item << ' ';
      }

      /* If you want all paths printed, then comment out
       * the 'return true' statement. */
      return true;
    }

    pathvec.pop_back();
    return false;
  }

  if (PrintMaxPathSum (node->left, sum - node->data))
    return true;

  if (PrintMaxPathSum (node->right, sum - node->data))
    return true;

  pathvec.pop_back();
  return false;
}

/* This will return 10 if presented with the above 8-4-(-2) tree. */
int MaxSumRootToLeaf (Node *node) {
  if (node == nullptr)
    /*
     * This return value is the only difference between the above function
     * and this function. Returning 0 will give you the maximum between root
     * and any node including a non-leaf node. Returning INT32_MIN will give
     * you the maximum between root and a leaf. This little subtlety makes a
     * difference only if the tree contains negatives. It won't matter if there
     * are all positives in the tree.
     */
    return INT32_MIN;

  if (node->left == nullptr && node->right == nullptr) {
    return node->data;
  }

  int lsum = MaxSumRootToLeaf (node->left);
  int rsum = MaxSumRootToLeaf (node->right);

  return lsum > rsum ? lsum + node->data : rsum + node->data;
}

// PDF problems start here.
unsigned int size(Node *node) {
  if (node == nullptr) {
    return 0;
  }

  return size(node->left) + 1 + size(node->right);
}

int MaxDepth(Node *node) {
  if (node == nullptr)
    return 0;

  int ldepth = MaxDepth(node->left);
  int rdepth = MaxDepth(node->right);

  return ldepth > rdepth ? ldepth + 1 : rdepth + 1;
}

int MinValue (Node *node) {
  if (node == nullptr) {
    return 0xdeadbeef;
  }

  if (node->left == nullptr) {
    return node->data;
  }

  return MinValue(node->left);
}

void Print(Node *node) {
  if (node) {
    Print(node->left);
    cout << node->data << ' ';
    Print(node->right);
  }
}

/* This is slightly tricky. Check your implementation for the below tree and sum 8.
    5
   / \
  3   7
 /     \
1       9
 \
  2*/
bool hasPathSum(Node *node, int sum) {
  // This condition is necessary because if you instead check if (node == nullptr && data == 0), you'll fail for the above tree with sum 8.
  if (node == nullptr) {
    return false;
  }

  if (node->left == nullptr && node->right == nullptr) {
    return sum == node->data;
  }

  return hasPathSum(node->left, sum - node->data) ||
         hasPathSum(node->right, sum - node->data);
}

void PrintPaths (Node *node) {
  static vector<int> path;

  if (node == nullptr)
    return;

  path.push_back(node->data);

  if (node->left == nullptr && node->right == nullptr) {
    for (int item : path) {
      cout << item << ' ';
    }
    cout << endl;
  } else {
    PrintPaths (node->left);
    PrintPaths (node->right);
  }

  path.pop_back();
}

void Mirror (Node *node) {
  if (node == nullptr)
    return;

  Node *temp = node->left;
  node->left = node->right;
  node->right = temp;

  Mirror(node->left);
  Mirror(node->right);
}

void DoubleTree (Node *node) {
  if (node == nullptr)
    return;

  Node *newnode = new Node {node->data, node->left, nullptr};
  node->left = newnode;

  DoubleTree (newnode->left);
  DoubleTree (node->right);
}

bool SameTree (Node *a, Node *b) {
  if (a == nullptr && b == nullptr)
    return true;

  if (a == nullptr || b == nullptr)
    return false;

  return (a->data == b->data)       &&
         SameTree(a->left, b->left) &&
         SameTree(a->right, b->right);
}

bool IsBSTWorker(Node *node, int min, int max) {
  if (node == nullptr)
    return true;

  if (node->data < min || node->data > max) {
    return false;
  }

  return IsBSTWorker(node->left, min, node->data) &&
         IsBSTWorker(node->right, node->data + 1, max);
}

void MinMaxValues(Node *node, int *min, int *max) {
  if (node == nullptr)
    return;

  if (node->data < *min) {
    *min = node->data;
  } else if (node->data > *max) {
    *max = node->data;
  }

  MinMaxValues(node->left, min, max);
  MinMaxValues(node->right, min, max);
}

bool IsBST(Node *node) {
  int min, max;
  if (node == nullptr)
    return true;

  min = max = node->data;
  MinMaxValues(node, &min, &max);
  return IsBSTWorker(node, min, max);
}

bool IsBST (Node *node) {
  static int lastdata = INT32_MIN;

  if (node == nullptr)
    return true;

  if (false == IsBST (node->left))
    return false;

  if (node->data < lastdata)
    return false;

  lastdata = node->data;

  return IsBST (node->right);
}

/* Check if the given expression is a valid tertiary expression.
=================================================================================
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
  char data;
  struct node *left;
  struct node *right;
  struct node *parent;
} Node;

typedef enum {
  leftchild,
  rightchild
} child;

void Print(Node *tree) {
  if (tree == nullptr) {
    return;
  }

  Print(tree->left);
  printf("%c  ", tree->data);
  Print(tree->right);
}

Node* InsertTree (Node *current, char data, child LeftOrRight) {
  Node *newnode = nullptr;
  Node *parent = current;

  if (LeftOrRight == rightchild) {
    // This is a do-while because you will surely go one level up
    // the tree anytime there's a right child insertion.
    do {
      parent = parent->parent;

      if (parent && parent->right == nullptr) {
        break;
      }
    } while (parent);
  }

  if (parent) {
    newnode = (Node*) malloc (sizeof(Node));
    newnode->data = data;
    newnode->left = newnode->right = nullptr;
    newnode->parent = parent;

    if (LeftOrRight == leftchild) {
      parent->left = newnode;
    } else {
      parent->right = newnode;
    }
  }

  return newnode;
}

bool ExpTree (const char *str) {
  Node *tree;
  Node *current;

  if (str == nullptr || *str == 0) {
    return true;
  }

  tree = (Node*) malloc (sizeof(Node));
  tree->data = *str++;
  tree->left = tree->right = nullptr;
  tree->parent = nullptr;

  current = tree;

  // Keep adjusting the *str pointer such that you only have to deal
  // with ? and : and the actual characters are handled in the InsertTree
  // function.

  while (*str) {
    switch(*str) {
      case '?':
        // current points to the parent node where the next left insertion will happen.
        current = InsertTree(current, *++str, leftchild);
        break;

      case ':':
        // current points to the starting node from where you determine the closest parent
        // without a right child.
        current = InsertTree(current, *++str, rightchild);
        break;

      // You should never encounter a character that is not a ? or a :
      default:
        current = nullptr;
    }

    if (current == nullptr) {
      return false;
    }

    str++;
  }

  // Sanity Tests. You always end up at the right most node in the tree and
  // the parent of this node SHOULD have a left child. Check for these two
  // conditions now.
  if (current != tree) {
    if (current->parent->left == nullptr || current->parent->right != current) {
      return false;
    }
  }

  Print(tree);
  printf("\n");

  return true;
}

int main () {
  char *exp = "a?b:c?d?e:f:k";

  if (ExpTree(exp) == true) {
    printf("Valid expression tree.\n");
  } else {
    printf("Invalid expression tree.\n");
  }

  return 0;
} */