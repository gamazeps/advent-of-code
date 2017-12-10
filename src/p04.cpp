#include <algorithm>
#include <climits>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<vector<string>> parse_input() {
    string buff;
    vector<vector<string> > in;

    while(getline(cin, buff)) {
        istringstream iss(buff);
        vector<string> tmp_vec;

        do
        {
            string tmp;
            iss >> tmp;
            tmp_vec.push_back(tmp);
        } while (iss);

        in.push_back(tmp_vec);
    }

    return in;
}

bool valid_pp(const vector<string>& pp) {
    unordered_map<string, int> wc;
    for(const auto& w : pp) {
        wc[w]++;
        if (wc[w] > 1) {
            return false;
        }
    }
    return true;
}

bool valid_spp(const vector<string>& pp) {
    unordered_map<string, int> wc;
    for(const auto& w : pp) {
        string sw = w;
        sort(sw.begin(), sw.end());
        wc[sw]++;
        if (wc[sw] > 1) {
            return false;
        }
    }
    return true;
}

int part_1(const vector<vector<string>>& input) {
    int valids(0);
    for (const auto& pp : input) {
        if (valid_pp(pp)) {
            valids++;
        }
    }
    return valids;
}

int part_2(const vector<vector<string>>& input) {
    int valids(0);
    for (const auto& pp : input) {
        if (valid_spp(pp)) {
            valids++;
        }
    }
    return valids;
}

void test() {
    vector<string> t1 = {"aa", "bb", "cc", "dd", "ee"};
    cout << valid_pp(t1) << endl;
    vector<string> t2 = {"aa", "bb", "cc", "dd", "aa"};
    cout << valid_pp(t2) << endl;
    vector<string> t3 = {"aa", "bb", "cc", "dd", "aaa"};
    cout << valid_pp(t3) << endl;
}

int main() {
    vector<vector<string>> input = parse_input();
    cout << part_1(input) << endl;
    cout << part_2(input) << endl;
    return 0;
}

