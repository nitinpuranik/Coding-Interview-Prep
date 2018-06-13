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
 * Nodes in right subtree > parent.
 */

typedef struct node {
  int data;
  struct node *left;
  struct node *right;
} Node;

void Insert (Node **node, int data) {
  if (node == nullptr)
    return;

  Node *newnode = new Node;
  if (newnode == nullptr)
    return;

  newnode->data = data;
  newnode->left = newnode->right = nullptr;

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

/*Bloomberg: Copy a graph. Watch out for the cycle between 1 and 2.
    0
   / \
  1---2
     / \
    3   4 */
Node* Duplicate (Node *node) {
  static unordered_map<Node*, Node*> visited;

  if (node == nullptr)
    return nullptr;

  if (visited.find (node) != visited.end())
    return visited[node];

  Node *newnode = new Node;
  newnode->data = node->data;

  newnode->left  = Duplicate (node->left);
  newnode->right = Duplicate (node->right);

  visited.insert({node, newnode});

  return newnode;
}

void Print(Node *node) {
  if (!node) {
    return;
  }

  Print(node->left);
  cout << node->data << ' ';
  Print(node->right);
}

unsigned int MaxDepth(Node *node) {
  unsigned int ldepth;
  unsigned int rdepth;

  if (node == nullptr)
    return 0;

  ldepth = MaxDepth(node->left);
  rdepth = MaxDepth(node->right);

  if (ldepth > rdepth)
    return ldepth + 1;
  else
    return rdepth + 1;
}

unsigned int Count(Node *node) {
  if (node == nullptr) {
    return 0;
  }

  return Count(node->left) + 1 + Count(node->right);
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

/* This is slightly tricky. Check your implementation for the below tree and sum 8.
    5
   / \
  3   7
 /     \
1       9
 \
  2*/
bool hasPathSum(Node *node, int sum) {
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
  static vector<int> arr;

	if (node == nullptr)
		return;

	arr.push_back(node->data);

	if (node->left == NULL && node->right == NULL) {

		for (unsigned i = 0; i < arr.size(); i++) {
			cout << arr[i] << ' ';
		}
		cout << endl;

	} else {
		PrintPaths (node->left);
		PrintPaths (node->right);
	}

	arr.pop_back();
}

void Mirror (Node *node) {
  Node *temp;

  if (node == nullptr)
    return;

  temp = node->left;
  node->left = node->right;
  node->right = temp;

  Mirror(node->left);
  Mirror(node->right);
}

void DoubleTree (Node *node) {
  if (node == nullptr)
    return;
  
  Node *newnode = new Node;
  newnode->data = node->data;
  newnode->left = node->left;
  newnode->right = nullptr;
  
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

void PrintRange (Node *node, int min, int max) {
  if (node == nullptr) {
    return;
  }

  if (node->data > min) {
    PrintRange (node->left, min, max);
  }

  if (node->data >= min && node->data <= max) {
    printf("%d ", node->data);
  }

  if (node->data < max) {
    PrintRange (node->right, min, max);
  }
}

bool IsBalanced (Node *node) {
  unsigned ldepth, rdepth;
  unsigned diff;

  if (node == nullptr) {
    return true;
  }

  ldepth = MaxDepth (node->left);
  rdepth = MaxDepth (node->right);

  diff = ldepth > rdepth ? ldepth - rdepth : rdepth - ldepth;

  return   (diff <= 1)              &&
           IsBalanced (node->left)  &&
           IsBalanced (node->right);
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

int main(int argc, char **argv)
{
  Node *node = nullptr;

  Insert (&node, 5);
  Insert (&node, 7);
  Insert (&node, 3);
  Insert (&node, 1);
  Insert (&node, 9);
  Insert (&node, 2);
  Insert (&node, 6);

  return 0;
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