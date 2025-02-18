struct FilterExp {
	FilterExp(vector<FilterExp*>& children): mychildren{children} {}
	
	virtual vector<size_t> compute(const vector<size_t>& inputSelection) = 0;
	
	vector<FilterExp*> m_children;
};

// InputSelection is an ordered set of integers. Return a subset of that that's also ordered.
struct OrExpr: public FilterExp {
	vector<size_t> compute(const vector<size_t>& inputSelection) override {
		vector<size_t> resultset;
		unordered_set<size_t> indices;

		for (const FilterExp* child: m_children) {
			vector<size_t> child_resultset = child->compute(inputSelection);

			for(size_t val: child_resultset) {
				if (indices.find(val) == indices.end()) {
					indices.insert(val);
				}
			}
		}

		for(size_t val: indices) {
			resultset.push_back(val);
		}

		sort(resultset.begin(), resultset.end());
		return resultset;
	}
};

struct AndExpr: public FilterExp {
	vector<size_t> compute<const vector<size_t>& inputSelection) override {
		vector<size_t> resultSet {inputSelection};
		
		for(const FilterExp* child: m_children) {
			resultSet = child->compute(resultSet);
		}
		
		return resultSet;
	}
};
=====================
#include <iostream>
#include <vector>
using namespace std;

struct FilterExpr {
    vector<FilterExpr*> m_children;

    FilterExpr(): m_children{vector<FilterExpr*>()} {}
    FilterExpr(const vector<FilterExpr*>& children): m_children{children} {}

    virtual vector<size_t> compute(const vector<size_t>& inputSelection) const = 0;
};

struct AndExpr: public FilterExpr {
    AndExpr(const vector<FilterExpr*>& children): FilterExpr(children) {}

    vector<size_t> compute(const vector<size_t>& inputSelection) const override {
        vector<size_t> resultSet {inputSelection};

        for(const FilterExpr* child: m_children) {
            resultSet = child->compute(resultSet);

            if (resultSet.empty()) {
                break;
            }
        }

        return resultSet;
    }
};

bool overlap(const vector<size_t>& v1, const vector<size_t>& v2) {
    return v1.front() <= v2.back() && v1.back() >= v2.front();
}

bool BinarySearch(const vector<size_t>& inputSelection, size_t item) {
    size_t left{0}, right{inputSelection.size()-1};

    while (left <= right) {
        if (item == inputSelection[left]) {
            return true;
        }

        if (item == inputSelection[right]) {
            return true;
        }

        size_t mid = (left+right)/2;

        if (mid == left) {
            return false;
        }

        if (item == inputSelection[mid]) {
            return true;
        }
        
        if (item < inputSelection[mid]) {
            ++left;
            right = mid-1;
        } else {
            left = mid+1;
            --right;
        }
    }

    return false;
}

vector<size_t> merge(const vector<size_t>& vec, const vector<size_t>& inputSelection) {
    vector<size_t> result;

    size_t leftidx{0};
    // Get the first overlapping item.
    for(; leftidx < vec.size() && vec[leftidx] < inputSelection[0]; ++leftidx);

    size_t rightidx{vec.size()-1};
    // Get the last overlapping item.
    for(; rightidx >=0 && vec[rightidx] > inputSelection.back(); --rightidx);

    for (; leftidx <= rightidx; ++leftidx) {
        if (BinarySearch(inputSelection, vec[leftidx])) {
            result.push_back(vec[leftidx]);
        }
    }

    return result;
}

struct c1: public FilterExpr {
    vector<size_t> compute(const vector<size_t>& inputSelection) const override {
        vector<size_t> vec {3,4,15,19};
        vector<size_t> result;
        
        if (overlap(vec, inputSelection)) {
            result = merge(vec, inputSelection);
        }
        
        return result;
    }
};

struct c2: public FilterExpr {
    vector<size_t> compute(const vector<size_t>& inputSelection) const override {
        vector<size_t> vec {4,7,15};
        vector<size_t> result;
        
        if (overlap(vec, inputSelection)) {
            result = merge(vec, inputSelection);
        }
        
        return result;
    }
};

struct c3: public FilterExpr {
    vector<size_t> compute(const vector<size_t>& inputSelection) const override {
        vector<size_t> vec {4,12,15,19};
        vector<size_t> result;
        
        if (overlap(vec, inputSelection)) {
            result = merge(vec, inputSelection);
        }

        return result;
    }
};

struct c4: public FilterExpr {
    vector<size_t> compute(const vector<size_t>& inputSelection) const override {
        vector<size_t> vec {3,4,15,19};
        vector<size_t> result;
        
        if (overlap(vec, inputSelection)) {
            result = merge(vec, inputSelection);
        }
        
        return result;
    }
};

int main() {
    c1 o1; c2 o2; c3 o3; c4 o4;
    vector<FilterExpr*> children {&o1, &o2, &o3, &o4};
    AndExpr andObj(children);

    vector<size_t> result = andObj.compute(vector<size_t>{1,3,4,6,7,12,15,19});

    for(size_t val: result) {
        cout << val << ' ';
    }

    return 0;
}

main: {0,1,3,6,7,12,15,17,19,20,23,26,27,30,32,35}
c1: {4,15,21,24}
c2: {4,7,15,19}
c3: {4,6,12,19,30}
c4: {3,4,15,19}
----------------
AndResult: {4,15,19}

OrResult: {3,4,6,7,12,15,19,21,24,30}

InputAfterC1: {0,1,3,6,7,12,17,19,20,23}