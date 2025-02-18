#include <iostream>
#include <vector>
using namespace std;

void Print (const vector<int>& arr) {
  for (unsigned i = 0; i < arr.size(); i++)
    cout << arr[i] << ' ';

  cout << endl;
}

void swap (vector<int>& arr, int i, int j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

unsigned Partition (vector<int>& arr, int low, int high) {
  int firsthigh = low;
  int pivot = high;

  // Intuition: We begin with choosing the last element in the array to be
  // the pivot element. Now during our single pass, we need to find the final
  // resting spot for this pivot element. To do that, we need to keep track of
  // the leftmost item that is higher than the pivot element. Then swap all items
  // lesser than the pivot element with this item. At the end, swap the pivot item
  // with this first highest item.

  for (int i = low; i < high; i++) {
    if (arr[i] < arr[pivot]) {
      if (i != firsthigh)
        swap (arr, i, firsthigh);

      firsthigh++;
    }
  }

  if (pivot != firsthigh)
    swap (arr, firsthigh, pivot);

  return firsthigh;
}

void QuickSortWorker (vector<int>& arr, int low, int high) {
  if (low < high) {
    int pivot = Partition (arr, low, high);
    QuickSortWorker (arr, low, pivot - 1);
    QuickSortWorker (arr, pivot + 1, high);
  }
}

void QuickSort (vector<int>& arr) {
  QuickSortWorker (arr, 0, arr.size() - 1);
}

int main() {
  vector<int> arr {81, 85, 73, 67, 75, 83, 79, 82, 84};

  Print(arr);
  QuickSort(arr);
  Print(arr);

  return 0;
}