#include <iostream>
#include <vector>
using namespace std;

struct FilterExp {
    vector<FilterExp*> m_children;

    FilterExp(vector<FilterExp*>& children): m_children{children} {}

    virtual vector<size_t> compute(const vector<size_t>& inputSelection) const = 0;
};

enum class Equality { small, big };

size_t BinarySearch(const vector<size_t>& v, size_t target, Equality eq) {
    size_t left {0};
    size_t right {v.size() - 1};

    while (left < right) {
        if (target == v[left]) {
            return left;
        }

        if (target == v[right]) {
            return right;
        }

        size_t mid = (left + right) / 2;

        if (target == v[mid]) {
            return mid;
        }

        if (mid == left) {
            return eq == Equality::small? left : right;
        }

        if (target < v[mid]) {
            right = mid;
        } else {
            left = mid;
        }
    }
}

// Remove elements of v2 from v1.
vector<size_t> DisjointSet(const vector<size_t>& v1, const vector<size_t>& v2) {
    if (v2.back() < v1.front() || v1.back() < v2.front()) {
        return v1;
    }

    // Find overlap indices.
    size_t leftIndex = BinarySearch(v1, v2.front(), Equality::big);
    size_t rightIndex = BinarySearch(v1, v2.back(), Equality::small);

    // Copy the non-overlapping left values.
    vector<size_t> result;
    for (size_t idx{0}; idx < leftIndex; ++idx) {
        result.push_back(v1[idx]);
    }

    // Copy the non-overlapping right values.
    for (size_t idx{rightIndex+1}; idx < v1.size(); ++idx) {
        result.push_back(v1[idx]);
    }

    return result;
}

struct OrExp: public FilterExp {
    vector<size_t> compute(const vector<size_t>& inputSelection) const override {
        set<size_t> resultSet;
        vector<size_t> input {inputSelection};

        for (const FilterExp* child: m_children) {
            vector<size_t> output = child->compute(input);

            for(size_t val: output) {
                resultSet.insert(val);
            }

            input = DisjointSet(input, output);
        }

        vector<size_t> result;
        for(size_t val: resultSet) {
            result.push_back(val);
        }

        return result;
    }
}