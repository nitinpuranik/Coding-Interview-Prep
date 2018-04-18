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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * In a BST, nodes in left subtree <= parent.
 * Nodes in right subtree >= parent.
 */

typedef struct node {
  int data;
  struct node *left;
  struct node *right;
} Node;

/********************************************************************************
Practice Area
********************************************************************************/

void Insert (Node **root, int data) {
  Node *curr, *prev;
  Node *newnode = NULL;

  if (root == NULL) {
    return;
  }

  newnode = (Node*) malloc (sizeof(Node));
  newnode->data = data;
  newnode->left = newnode->right = NULL;

  prev = curr = *root;

  while (curr) {
    prev = curr;
    if (data <= curr->data) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }

  if (prev) {
    if (data <= prev->data) {
      prev->left = newnode;
    } else {
      prev->right = newnode;
    }
  } else {
    *root = newnode;
  }
}

void InsertRecursiveWorker(Node *curr, Node *parent, Node *newnode) {
  if (!curr) {
    if (newnode->data <= parent->data) {
      parent->left = newnode;
    } else {
      parent->right = newnode;
    }
  } else if (newnode->data <= curr->data) {
    InsertRecursiveWorker(curr->left, curr, newnode);
  } else {
    InsertRecursiveWorker(curr->right, curr, newnode);
  }
}

void InsertRecursive (Node **root, int data) {
  Node *newnode;

  if (!root) {
    return;
  }

  newnode = (Node*) malloc (sizeof (Node));
  newnode->data = data;
  newnode->left = newnode->right = NULL;

  if (!*root) {
    *root = newnode;
  } else {
    InsertRecursiveWorker(*root, NULL, newnode);
  }
}

void Print(Node *node) {
  if (!node) {
    return;
  }

  Print(node->left);
  printf("%d ", node->data);
  Print(node->right);
}

unsigned int MaxDepth(Node *node) {
  unsigned int ldepth;
  unsigned int rdepth;

  if (node == NULL)
    return 0;

  ldepth = MaxDepth(node->left);
  rdepth = MaxDepth(node->right);

  if (ldepth > rdepth)
    return ldepth + 1;
  else
    return rdepth + 1;
}

unsigned int Count(Node *node) {
  if (node == NULL) {
    return 0;
  }

  return Count(node->left) + 1 + Count(node->right);
}

int MinValue (Node *node) {
  if (node == NULL) {
    return 0xdeadbeef;
  }

  if (node->left == NULL) {
    return node->data;
  }

  return MinValue(node->left);
}

bool hasPathSum(Node *node, int sum) {
  if (node == NULL) {
    return sum == 0 ?  true : false;
  }

  return hasPathSum(node->left, sum - node->data) ||
         hasPathSum(node->right, sum - node->data);
}

void PrintPathsWorker(Node *node, int *patharray, unsigned index) {
  unsigned count;

  if (node == NULL) {
    return;
  }

  patharray[index] = node->data;

  if (node->left == NULL && node->right == NULL) {
    for (count = 0; count <= index; count++) {
      printf("%d ", patharray[count]);
    }
    printf("\n");
  } else {
    PrintPathsWorker(node->left, patharray, index + 1);
    PrintPathsWorker(node->right, patharray, index + 1);
  }
}

void PrintPaths (Node *node) {
  int *patharray;
  unsigned maxdepth;

  if (node == NULL) {
    return;
  }

  maxdepth = MaxDepth(node);
  patharray = (int*) malloc (maxdepth * sizeof(int));

  PrintPathsWorker(node, patharray, 0);
}

void Mirror (Node *node) {
  Node *temp;

  if (node == NULL)
    return;

  temp = node->left;
  node->left = node->right;
  node->right = temp;

  Mirror(node->left);
  Mirror(node->right);
}

void DoubleTree (Node *node) {
  Node *newnode;

  if (node == NULL)
    return;

  newnode = (Node*) malloc (sizeof(Node));
  newnode->data = node->data;
  newnode->left = node->left;
  newnode->right = NULL;

  node->left = newnode;

  DoubleTree(newnode->left);
  DoubleTree(node->right);
}

bool SameTree (Node *a, Node *b) {
  if (a == NULL && b == NULL)
    return true;

  if (a == NULL || b == NULL)
    return false;

  return (a->data == b->data)       &&
         SameTree(a->left, b->left) &&
         SameTree(a->right, b->right);
}

bool IsBSTWorker(Node *node, int min, int max) {
  if (node == NULL)
    return true;

  if (node->data < min || node->data > max) {
    return false;
  }

  return IsBSTWorker(node->left, min, node->data) &&
         IsBSTWorker(node->right, node->data + 1, max);
}

void MinMaxValues(Node *node, int *min, int *max) {
  if (node == NULL)
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
  if (node == NULL)
    return true;

  min = max = node->data;
  MinMaxValues(node, &min, &max);
  return IsBSTWorker(node, min, max);
}

void PrintRange (Node *node, int min, int max) {
  if (node == NULL) {
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

  if (node == NULL) {
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
  if (node == NULL) {
    return NULL;
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
  Node nodes[] = {
    {6, NULL, NULL},  //node 0 = 5
    {4, NULL, NULL},  //node 1 = 4
    {7, NULL, NULL},  //node 2 = 8
    {11, NULL, NULL}, //node 3 = 11
    {13, NULL, NULL}, //node 4 = 13
    {4, NULL, NULL},  //node 5 = 4
    {7, NULL, NULL},  //node 6 = 7
    {2, NULL, NULL},  //node 7 = 2
    {1, NULL, NULL},  //node 8 = 1
  };

  nodes[0].left = &nodes[1];
  nodes[0].right = &nodes[2];
  nodes[1].left = &nodes[3];/*
  nodes[3].left = &nodes[6];
  nodes[2].left = &nodes[4];
  nodes[2].right = &nodes[5];
  nodes[3].left = &nodes[6];
  nodes[3].right = &nodes[7];
  nodes[5].right = &nodes[8];*/


  if (IsBalanced(&nodes[0]) == true) {
    printf("Balanced Tree.\n");
  } else {
    printf("Not a balanced Tree.\n");
  }
  /*
  InsertRecursive(&A, 2);
  InsertRecursive(&A, 4);
  InsertRecursive(&A, 4);
  printf("Count = %d.\n", countTrees(3));

  if(SameTree(A,B)) {
    printf("Same trees.\n");
  } else {
    printf("Different trees.\n");
  }

  if (hasPathSum(&nodes[0], 22) == true) {
    printf("Has pathsum.\n");
  } else {
    printf("No pathsum.\n");
  }
  DoubleTree(A);
  InsertRecursive(&A, 2);
  InsertRecursive(&A, 8);
  InsertRecursive(&A, 1);
  InsertRecursive(&A, 3);
  PrintPaths(A, arr, 0);
  Mirror(A);
  printf("MaxDepth = %u\n", MaxDepth(A));
  printf("Count = %u\n", Count(A));
  */

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
  if (tree == NULL) {
    return;
  }

  Print(tree->left);
  printf("%c  ", tree->data);
  Print(tree->right);
}

Node* InsertTree (Node *current, char data, child LeftOrRight) {
  Node *newnode = NULL;
  Node *parent = current;

  if (LeftOrRight == rightchild) {
    // This is a do-while because you will surely go one level up
    // the tree anytime there's a right child insertion.
    do {
      parent = parent->parent;

      if (parent && parent->right == NULL) {
        break;
      }
    } while (parent);
  }

  if (parent) {
    newnode = (Node*) malloc (sizeof(Node));
    newnode->data = data;
    newnode->left = newnode->right = NULL;
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

  if (str == NULL || *str == 0) {
    return true;
  }

  tree = (Node*) malloc (sizeof(Node));
  tree->data = *str++;
  tree->left = tree->right = NULL;
  tree->parent = NULL;

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
        current = NULL;
    }

    if (current == NULL) {
      return false;
    }

    str++;
  }

  // Sanity Tests. You always end up at the right most node in the tree and
  // the parent of this node SHOULD have a left child. Check for these two
  // conditions now.
  if (current != tree) {
    if (current->parent->left == NULL || current->parent->right != current) {
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