// https://www.geeksforgeeks.org/merge-k-sorted-arrays/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct MinHeapNode {
  int data;
  unsigned row;
  unsigned idx;
};

void swap (auto& heap, unsigned i, unsigned j) {
  heap[i]->data = heap[i]->data ^ heap[j]->data;
  heap[j]->data = heap[i]->data ^ heap[j]->data;
  heap[i]->data = heap[i]->data ^ heap[j]->data;
  
  heap[i]->row = heap[i]->row ^ heap[j]->row;
  heap[j]->row = heap[i]->row ^ heap[j]->row;
  heap[i]->row = heap[i]->row ^ heap[j]->row;
  
  heap[i]->idx = heap[i]->idx ^ heap[j]->idx;
  heap[j]->idx = heap[i]->idx ^ heap[j]->idx;
  heap[i]->idx = heap[i]->idx ^ heap[j]->idx;
}

void Heapify (auto& heap, unsigned idx) {
  unsigned left;
  unsigned right;
  
  left = 2 * idx + 1;
  right = left + 1;
  
  unsigned smallest = idx;
  
  if (left < heap.size()) {
    if (heap[left]->data < heap[smallest]->data)
      smallest = left;
  }
  
  if (right < heap.size()) {
    if (heap[right]->data < heap[smallest]->data)
      smallest = right;
  }
  
  if (smallest != idx) {
    swap (heap, idx, smallest);
    
    Heapify (heap, smallest);
  }
}

void SortAll (const auto& table) {
  vector<MinHeapNode*> heap;
  vector<int> SortedArr;
  unsigned rowsize = table.size();
  
  for (unsigned idx = 0; idx < rowsize; idx++) {
    if (table[idx].size()) {
      MinHeapNode *node = new MinHeapNode {table[idx][0], idx, 0};
      
      heap.push_back(node);
    }
  }
  
  for (unsigned idx = 0; idx <= rowsize / 2 - 1; idx++) {
    Heapify (heap, idx);
  }
  
  while(true) {
    SortedArr.push_back (heap[0]->data);
    
    if (heap[0]->idx + 1 == table[heap[0]->row].size()) {
      heap[0]->data = INT_MAX;
    } else {
      heap[0]->data = table[heap[0]->row][heap[0]->idx + 1];
      heap[0]->idx++;
    }
    
    Heapify (heap, 0);
    if (heap[0]->data == INT_MAX)
      break;
  }
  
  //SortedArr.push_back (heap[0]->data);
  
  for (const int item : SortedArr)
    cout << item << ' ';
}

int main () {
  vector<vector<int>> table = {
                                {1,3,5,7,12},
                                {2,4,6,8,19},
                                {0,9,10,11,128}
                              };
  
  SortAll (table);
  
  return 0;
}