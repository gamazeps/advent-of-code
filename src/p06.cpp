#include <algorithm>
#include <climits>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


int part_1(const vector<int>& input) {
    unordered_set<<vector<int>>> states;
    vector<int> curr = input; 

    do {
        states.insert(curr); 
        auto m = max_elem(curr.begin(), curr.end());
        int v = *m;
        *m = 0;

    } while (states.count(curr) < 1);
}

int main() {
    vector<int> input = {14, 0, 15, 12, 11, 11, 3, 5, 1, 6, 8, 4, 9, 1, 8, 4};
}
