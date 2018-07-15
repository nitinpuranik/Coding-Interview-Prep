#include <stdio.h>

void Print(int *arr, int size) {
  int i;

  for (i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void Swap(int *arr, int i, int j) {
  int temp;

  temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

 int Partition (int *arr, int low, int high) {
   int pivot;
   int firsthigh;
   int i;

  /*
   * Intuition: We begin with choosing the last element in the array to be
   * the pivot element. Now during our single pass, we need to find the final
   * resting spot for this pivot element. To do that, we need to keep track of
   * the first item that is higher than the pivot element. Then swap all items
   * lesser than the pivot element with this first highest element. At the end,
   * swap the pivot item with this first highest item.
   */

  pivot = high;
  firsthigh = low;

  for (i = low; i < high; i++) {
    if (arr[i] < arr[pivot]) {
      Swap(arr, i, firsthigh);
      firsthigh++;
    }
  }

  Swap(arr, firsthigh, pivot);
  return firsthigh;
}

void QuickSortWorker(int *arr, int low, int high) {
   int pivot;

  if (low < high) {
    pivot = Partition(arr, low, high);
    QuickSortWorker(arr, low, pivot - 1);
    QuickSortWorker(arr, pivot + 1, high);
  }
}

void QuickSort(int *arr, int size) {
  QuickSortWorker(arr, 0, size - 1);
}

int main() {
  int arr[] = {81, 85, 73, 67, 75, 83, 79, 82, 84};

  Print(arr, sizeof(arr)/sizeof(int));
  QuickSort(arr, sizeof(arr)/sizeof(int));
  Print(arr, sizeof(arr)/sizeof(int));

  return 0;
}