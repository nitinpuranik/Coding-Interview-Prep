#include <stdio.h>

// To get an array in the ascending order, build a MaxHeap.
// To get an array in the descending order, build a MinHeap.
void swap (int *arr, int i, int j) {
  int temp;

  temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

void heapify (int *arr, int n, int i) {
  int largest;
  int lchild, rchild;

  largest = i;
  lchild = 2 * i + 1;
  rchild = 2 * i + 2;

	// Get the largest item among root, left child and right child.
  if (lchild < n && arr[largest] < arr[lchild]) {
    largest = lchild;
  }

  if (rchild < n && arr[largest] < arr[rchild]) {
    largest = rchild;
  }

  if (largest != i) {
    swap (arr, i, largest);

		// You heapified the root at index i. Now heapify down.
    heapify (arr, n, largest);
  }
}

void heapsort (int *arr, int n) {
  int i;

  if (arr == NULL || n <= 0) {
    return;
  }

	// Build the initial MaxHeap. i = (n / 2) - 1 because the index of the first
	// non-leaf node in the complete binary tree begins there. Start at the first
	// non-leaf index and begin heapifying down as you go along to the root.
  for (i = n / 2 - 1; i >= 0; i--) {
    heapify (arr, n, i);
  }

	// Now that you've built your initial MaxHeap, you can find the max item at the
	// root of the tree. Swap it with the last item and be done with it. Heapify at
	// the root which now has a new element. Rinse and repeat till i > 0. Note that
	// i > 0 is sufficient and i >= 0 is not necessary, since you would be done with
	// sorting at i = 1.
  for (i = n - 1; i > 0; i--) {
    swap (arr, 0, i);

		// By passing in 'i' for the array size, you are gradually dealing with the array
		// that gets smaller and smaller, starting with n - 1, n - 2, ...., 1.
    heapify (arr, i, 0);
  }
}

int main () {
  int arr[] = {12, 11, 13, 5, 6, 7, 9};
  int i;

  heapsort (arr, 7);

  for (i = 0; i < 7; i++) {
    printf("%d ", arr[i]);
  }

  return 0;
}