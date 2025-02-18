// https://www.geeksforgeeks.org/merge-k-sorted-arrays/

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

void SortAll (const vector<vector<int>>& tbl) {
  vector<int> vsorted;
  vector<unsigned> vindex; // Vector to keep track of moving indexes through each array of tbl.
  priority_queue<int, vector<int>, greater<int>> pq;

  for (unsigned i = 0; i < tbl.size(); i++) {
    vindex.push_back(0);
    pq.push(tbl[i][0]);
  }

  // Once the top element of the min-heap becomes INT32_MAX, it means you are done.
  while (pq.top() != INT32_MAX) {
    vsorted.push_back(pq.top());

    for (unsigned i = 0; i < vindex.size(); i++) {
      if (tbl[i][vindex[i]] == pq.top()) {
        vindex[i]++;
        pq.pop();

        if (vindex[i] == tbl[i].size()) {
          pq.push(INT32_MAX);
        } else {
          pq.push(tbl[i][vindex[i]]);
        }

        break;
      }
    }
  }

  for (int item : vsorted)
    cout << item << ' ';
}

int main () {
  vector<vector<int>> table = {
                                {1,3,5,7,12},
                                {2,4,6,8,19},
                                {0,9,10,11,128}
                              };

  SortAll (table);
	// Output: 0 1 2 3 4 5 6 7 8 9 10 11 12 19 128

  return 0;
}