#include <iostream>
#include <vector>
using namespace std;

vector<int> MergeSortWorker (vector<int>& arr, unsigned low, unsigned high) {
  vector<int> mergearr;

  if (low < high) {
    unsigned mid = (low + high) / 2;

    vector<int> v1 = MergeSortWorker (arr, low, mid);
    vector<int> v2 = MergeSortWorker (arr, mid + 1, high);

    unsigned i, j;
    int *p1 = v1.data();
    int *p2 = v2.data();

    for (i = 0, j = 0; i < v1.size() && j < v2.size();) {
      if (*p1 < *p2) {
        mergearr.push_back(*p1);
        i++; p1++;
      } else {
        mergearr.push_back(*p2);
        j++; p2++;
      }
    }

    while (i < v1.size()) {
      mergearr.push_back(*p1);
      i++; p1++;
    }

    while (j < v2.size()) {
      mergearr.push_back(*p2);
      j++; p2++;
    }
  } else {
    mergearr.push_back(arr[low]);
  }

  return mergearr;
}

vector<int> MergeSort (vector<int>& arr) {
  if (arr.size() <= 1)
    return arr;

  return MergeSortWorker (arr, 0, arr.size() - 1);
}

int main () {
  vector<int> arr {12, 11, 13, 5, 6, 7, 9};

  arr = MergeSort(arr);

  for (unsigned i = 0; i < arr.size(); i++)
    cout << arr[i] << ' ';

  return 0;
}