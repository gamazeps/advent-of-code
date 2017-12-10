#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>

using namespace std;

int part_1(const vector<int>& input) {
    set<vector<int>> states; // Ugly but meh...
    vector<int> curr = input; 
    int steps(0);

    do {
        states.insert(curr); 
        steps++;

        // smallest elem and position
        int max(0);
        size_t pos(0);
        for (int i(0); i < curr.size(); i++) {
            if (curr[i] > max) {
                max = curr[i];
                pos = i;
            }
        }
        
        curr[pos] = 0;
        for (int i(0); i < curr.size(); i++) {
            curr[i] += max/curr.size();
        }

        max = max % curr.size();

        while (max > 0) {
            pos = (pos + 1) % curr.size();
            curr[pos]++;
            max--;
        }

    } while (states.count(curr) < 1);

    return steps;
}

int part_2(const vector<int>& input) {
    map<vector<int>, int> states; // Ugly but meh...
    vector<int> curr = input; 
    int steps(0);

    do {
        states[curr] = steps; 
        steps++;

        // smallest elem and position
        int max(0);
        size_t pos(0);
        for (int i(0); i < curr.size(); i++) {
            if (curr[i] > max) {
                max = curr[i];
                pos = i;
            }
        }
        
        curr[pos] = 0;
        for (int i(0); i < curr.size(); i++) {
            curr[i] += max/curr.size();
        }

        max = max % curr.size();

        while (max > 0) {
            pos = (pos + 1) % curr.size();
            curr[pos]++;
            max--;
        }

    } while (states.count(curr) < 1);

    return steps - states[curr];
}

int main() {
    vector<int> input = {14, 0, 15, 12, 11, 11, 3, 5, 1, 6, 8, 4, 9, 1, 8, 4};
    //vector<int> input = {0, 2, 7, 0};
    cout << part_1(input) << endl;
    cout << part_2(input) << endl;
    return 0;
}
