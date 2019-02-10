#include <iostream>
#include <vector>
using namespace std;

// To get an array in the ascending order, build a MaxHeap.
// To get an array in the descending order, build a MinHeap.
void Heapify (vector<int>& arr, int i, int n) {
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  int largest = i;

  // Get the largest item among node, left child and right child.
  if (left < n && arr[left] > arr[largest])
    largest = left;

  if (right < n && arr[right] > arr[largest])
    largest = right;

  if (largest != i) {
    int temp = arr[i];
    arr[i] = arr[largest];
    arr[largest] = temp;

    // You heapified the node at index i. Now heapify down.
    Heapify (arr, largest, n);
  }
}

void Heapsort (vector<int>& arr) {
  if (arr.empty())
    return;

  // Build the initial MaxHeap. i = (n / 2) - 1 because the index of the first
  // non-leaf node in the complete binary tree begins there. Start at the first
  // non-leaf index and begin heapifying down as you go along to the root.
  for (int i = arr.size() / 2 - 1; i >= 0; i--)
    Heapify (arr, i, arr.size());

  // Now that you've built your initial MaxHeap, you can find the max item at the
  // root of the tree. Swap it with the last item and be done with it. Heapify at
  // the root which now has a new element. Rinse and repeat till i > 0. Note that
  // i > 0 is sufficient and i >= 0 is not necessary, since you would be done with
  // sorting at i = 1.
  for (int i = arr.size() - 1; i > 0; i--) {
    int temp = arr[i];
    arr[i] = arr[0];
    arr[0] = temp;

    // By passing in 'i' for the array size, you are gradually dealing with the array
    // that gets smaller and smaller, starting with n - 1, n - 2, ...., 1.
    Heapify (arr, 0, i);
  }
}

int main() {
  vector<int> arr {12, 11, 13, 5, 6, 7, 9};

  Heapsort (arr);

  for (unsigned i = 0; i < arr.size(); i++)
    cout << arr[i] << ' ';

  return 0;
}