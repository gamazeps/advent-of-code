#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

int main() {

    string buff;
    vector<int> in;

    while(getline(cin, buff)) {
        istringstream iss(buff);
        int tmp;
        iss >> tmp;
        in.push_back(tmp);
    }

    int pos(0);
    int steps(0);

    do {
        int tmp(in[pos]);

        steps+=1;
        if (in[pos] > 2) {
            in[pos]--;
        } else {
            in[pos]++;
        }

        pos += tmp;
    } while (pos < in.size());

    cout << steps << endl;

    return 0;
}
