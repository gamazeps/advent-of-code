#include <algorithm>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

struct event_t {
    int begin;
    int end;
    int id; // lowest the better

    friend std::ostream & operator<<(std::ostream &os, const struct event_t& p);
    bool operator ==(const struct event_t &b) const {
        return this->begin == b.begin && this->end == b.end && this->id == b.id;
    }
};

std::ostream& operator<<(
        std::ostream& os, // stream object
        const struct event_t& foo
        ) {
    os << "{" << foo.begin << ","<< foo.end << ","<< foo.id << "}";
    return os;
}

bool starts_before(event_t a, event_t b) {
    return a.begin < b.begin;
}

bool ends_before(event_t a, event_t b) {
    return a.end < b.end;
}

vector<event_t> schedule(vector<event_t> input) {
    // First generate the list of starts and ends
    vector<event_t> begs(input);
    sort(begs.begin(), begs.end(), starts_before);
    vector<event_t> ends(input);
    sort(ends.begin(), ends.end(), ends_before);

    vector<event_t> res;

    set<int> currents;
    int b(0), e(0);
    bool done_beg(false);
    event_t curr_e;

    while (e < ends.size()) {
        event_t beg = begs[b];
        event_t end = ends[e];
        cout << "step: #beg " << beg <<  " #end " << end << endl;
        if(!done_beg && beg.begin < end.end) {
            currents.insert(beg.id);
            if (currents.size() == 1) {
                curr_e = beg; // this is now our only event.
            }
            else if (beg.id < curr_e.id) {
                curr_e.end = beg.begin;
                res.push_back(curr_e); // we finish our event;
                curr_e = beg; // The end is false but we will change it.
            }
            b++;
            if (b == begs.size()) {
                done_beg = true;
                b--;
            }
        } else {
            currents.erase(end.id);
            if (curr_e.id == end.id) {
                curr_e.end = end.end;
                res.push_back(curr_e);
                // Note, could be implemented with a heap, but too lazy.
                if (currents.size() > 0) {
                    set<int>::iterator new_id = min_element(currents.begin(), currents.end());
                    curr_e.id = *new_id;
                    curr_e.begin = end.end;
                }
            }
            e++;
        }
    }

    return res;
}

void dumpv(vector<struct event_t> vec) {
    for (int i=0; i<vec.size();i++) {
        cout << vec[i];
        if (i < (vec.size()-1)) {
            cout << ",";
        }
    }
    cout << endl;
}

int main() {
    {
        vector<event_t> v = {{10, 20, 1}, {0, 30, 2}};
        vector<event_t> res = schedule(v);

        vector<event_t> v_ref = {{0, 10, 2}, {10, 20, 1}, {20, 30, 2}};

        cout << "expected: ";
        dumpv(v_ref);
        cout << "got: ";
        dumpv(res);
    }

    return 0;
}
