#include <iostream>
using namespace std;

#define QSIZE 5

class Queue {
  private:
    int m_arr[QSIZE];
    int m_head, m_tail;
    int m_count;

  public:
    Queue () : m_head(0), m_tail(0), m_count(0) {}

    void push (int data);
    int pop ();
    int peek (int index);
};

void Queue::push (int data) {
  if (count == QSIZE)
    throw "Queue full.";

  m_arr[m_head] = data;
  m_count++;

  m_head = (m_head + 1) % QSIZE;
}

int Queue::pop () {
  if (m_count == 0)
    throw "Empty queue.";

  int data = m_arr[m_tail];
  m_count--;

  m_tail = (m_tail + 1) % QSIZE;

  return data;
}

int Queue::peek (int index) {
  if (m_count == 0)
    throw "Empty queue.";

  if (index < 0 || index >= QSIZE)
    throw "Index out of bounds.";

  if (m_tail <= m_head && (index < m_tail || index > m_head))
    throw "Invalid index.";

  // if head < tail check is implied below. But not necessary to state explicitly.
  if (index > m_head && index < m_tail)
    throw "Invalid index.";

  return m_arr[index];
}