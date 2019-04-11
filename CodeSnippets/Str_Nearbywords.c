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

unordered_map<char, vector<char>> nchars;
unordered_set<string> words {"jello", "jelly", "gekko", "gimme", "jimmy"};

void Init() {
  nchars['h'] = {'j','g'};
  nchars['e'] = {'i'};
  nchars['l'] = {'m', 'k'};
  nchars['o'] = {'y', 'e', 's'};
}

void Print (const string& str, vector<string>& vnearby) {
  static string res {str};
  static unsigned index = 0;

  if (index == str.length()) {
    if (words.find(res) != words.end())
      vnearby.push_back (res);

    return;
  }

  index++;
  Print (str, vnearby);
  index--;

  for (char ch : nchars[str[index]]) {
    res[index] = ch;

    index++;
    Print (str, vnearby);
    index--;
  }

  res[index] = str[index];
}

int main() {
  Init();

  vector<string> vnearby;
  Print ("hello", vnearby);

  for (const string& str : vnearby)
    cout << str << ' ';

  return 0;
}