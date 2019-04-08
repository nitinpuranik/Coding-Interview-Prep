/*
 * You are given utility function that returns nearby characters.
 * Another function that tells whether a word is a valid word.
 * Find all possible nearby words for the given word.
 * An input of Hello should return gekko, gimme, jelly, jello and jimmy.
 */

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

unordered_map<char, vector<char>> m_nearby;
unordered_set<string> words {"jello", "jelly", "gekko", "gimme", "jimmy"};

void Init () {
  m_nearby.insert({'h', {'j','g'}});
  m_nearby.insert({'e', {'i'}});
  m_nearby.insert({'l', {'m', 'k'}});
  m_nearby.insert({'o', {'y', 'e', 's'}});
}

vector<char> nearby_chars (char c) {
  if (m_nearby.find(c) != m_nearby.end())
    return m_nearby[c];

  return vector<char>();
}

bool IsWord (const string& str) {
  return words.find(str) != words.end();
}

void PrintNearby (string& str, auto& vnearby) {
  static unsigned idx = 0;

  if (str.empty() || idx >= str.length())
    return;

  vector<char> c_nearby = nearby_chars(str[idx]);
  c_nearby.push_back(str[idx]);

  char orig = str[idx];

  for (char ch : c_nearby) {
    str[idx] = ch;

    if (IsWord(str)) {
      vnearby.insert(str);
    }

    idx++;
    PrintNearby (str, vnearby);

    idx--;
  }

  str[idx] = orig;
}

int main() {
  string str {"hello"};
  unordered_set<string> vnearby;

  Init();

  PrintNearby (str, vnearby);

  for (const string& str : vnearby)
    cout << str << ' ';
  cout << endl;

  return 0;
}