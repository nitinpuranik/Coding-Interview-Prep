/* Approach 1: Sort and use the two pointer method. */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void RemovePrefix(vector<string>& input, vector<string>& output) {
    // Sort the input.
    sort(input.begin(), input.end());

    size_t i, j;

    for (i = 0, j = 1; j < input.size(); ++j) {
        if (input[j].find(input[i]) != 0) {
            output.push_back(input[i]);
            i = j;
        }
    }

    output.push_back(input[i]);
}

int main() {
    vector<string> input {"_finance_merchants", "_finance",  "_fin", "_data", "_merchants_dashboard",
    "_merchants_dashboard_pictures", "_dashboard", "_finance_pay"};

    /*
	{"_finance_merchants", "_finance",  "_fin", "_data", "_merchants_dashboard",
    "_merchants_dashboard_pictures", "_dashboard", "_finance_pay"};
    Output: {_fin, _data, _merchants_dashboard, _dashboard}

    {"dashboard", "board"};
	
	{"a", "aa"};

    {"_merchants_dashboard_pictures", "_merchants_dashboard"}
	*/

    vector<string> output {};

    RemovePrefix(input, output);

    for (const string& str: output) {
        cout << str << endl;
    }

    return 0;
}
//========================================================================
/* Approach 2: Use a Trie (prefix-tree) with vectors as children. */
#include <iostream>
#include <vector>
#include <string>

struct TrieNode {
    std::vector<TrieNode*> children;
    bool endOfWord {false};

    TrieNode(): children {std::vector<TrieNode*>(27, nullptr)} {}
};

void InsertTrie (TrieNode* root, const std::string& word) {
    TrieNode* curr {root};

    for (char c: word) {
        std::size_t childidx = (c == '\\') ? 26 : c - 'a';

        if (curr->children[childidx] == nullptr) {
            curr->children[childidx] = new TrieNode;
        }

        curr = curr->children[childidx];
    }

    curr->endOfWord = true;
}

void DFS (const TrieNode* node, std::vector<std::string>& output, std::string& prefix) {
    if (node->endOfWord) {
        output.push_back(prefix);
    } else {
        for (std::size_t idx {0}; idx < 27; ++idx) {
            if (node->children[idx] != nullptr) {
                if (idx < 26) {
                    prefix.push_back(idx + 'a');
                } else {
                    prefix.push_back('\\');
                }

                DFS (node->children[idx], output, prefix);
                prefix.pop_back();
            }
        }
    }
}

void RemovePrefix (const std::vector<std::string>& input, std::vector<std::string>& output) {
    TrieNode* root {new TrieNode};

    for (const std::string& word: input) {
        InsertTrie(root, word);
    }

    std::string prefix;
    DFS (root, output, prefix);
}

int main() {
    std::vector<std::string> input {"\\merchants\\dashboard\\pictures", "\\merchants\\dashboard"};

    std::vector<std::string> output;

    RemovePrefix (input, output);

    for (const std::string& prefix: output) {
        std::cout << prefix << std::endl; 
    }

    return 0;
}
//========================================================================
/* Approach 3: Use a Trie (prefix-tree) with unordered_map as children. */
#include <iostream>
#include <vector>
#include <unordered_map>

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool endOfWord {false};
};

void Insert(TrieNode* root, const std::string& word) {
    TrieNode* curr {root};

    for (char c: word) {
        if (curr->children.find(c) == curr->children.end()) {
            curr->children[c] = new TrieNode;
        }

        curr = curr->children[c];
    }

     curr->endOfWord = true;
}

void DFS(TrieNode* node, std::vector<std::string>& output, std::string& prefix) {
    if (node->endOfWord) {
        output.push_back(prefix);
    } else {
        for (auto& child: node->children) {
            prefix.push_back(child.first);
            DFS(child.second, output, prefix);
            prefix.pop_back();
        }
    }
}

void RemovePrefix(const std::vector<std::string>& input, std::vector<std::string>& output) {
    TrieNode* root {new TrieNode};

    for (const std::string& word: input) {
        Insert(root, word);
    }

    std::string prefix;
    DFS(root, output, prefix);
}

int main() {
    std::vector<std::string> input {"aa", "b"};

    std::vector<std::string> output;

    RemovePrefix(input, output);

    for (const std::string& prefix: output) {
        std::cout << prefix << std::endl;
    }

    return 0;
}