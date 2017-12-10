#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

int part_2(const vector<vector<int>>& in) {
    int res(0);
    for (int i(0); i < in.size(); i++) {
        int min(INT_MAX), max(0);
        for (int j(0); j < in[i].size(); j++) {
            if (in[i][j] < min)
                min = in[i][j];
            if (in[i][j] > max)
                max = in[i][j];
        }
        res += max - min;
    }
    return res;
}


int part_2(const vector<vector<int>>& in) {
    int res(0);
    for (int i(0); i < in.size(); i++) {
        bool found(false);

        for (int j(0); j < in[i].size(); j++) {
            for (int k(0); k < in.size(); k++) {
                if (in[i][j] % in[i][k] == 0 and j != k) {
                    res += in[i][j] / in[i][k];
                    found = true;
                    break;
                }
                if (found)
                    break;
            }
        }
    }
    return res;
}

int main() {
    string buff;
    vector<vector<int> > in;

    while(getline(cin, buff)) {
        istringstream iss(buff);
        vector<int> tmp_vec;

        do
        {
            int tmp;
            iss >> tmp;
            tmp_vec.push_back(tmp);
        } while (iss);

        in.push_back(tmp_vec);
    }

    cout << part_1(in) << endl;
    cout << part_2(in) << endl;

    return 0;
}
