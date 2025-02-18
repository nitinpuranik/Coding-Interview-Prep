#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Person {
  private:
    static int s_age;
    int m_age;

  public:
    Person () : m_age(++s_age) {}

    int GetAge() const { return m_age; }
};

struct LessThanByAge
{
  bool operator()(const Person& lhs, const Person& rhs) const
  {
    return lhs.GetAge() < rhs.GetAge();
  }
};

int Person::s_age = 0;

int main() {
  priority_queue<Person, vector<Person>, LessThanByAge> pq;

  pq.push(Person());

  const Person& P1 = pq.top();

  cout << P1.GetAge();

  return 0;
}