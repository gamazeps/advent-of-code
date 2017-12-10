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
        )
        {
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
    sort(begs.begin(), begs.end(), ends_before);

    vector<event_t> res;

    set<int> currents;
    int b(0), e(0);
    event_t curr_e;

    while (e < ends.size()) {
        std::cout << "LOOP: " << b << "," << e << std::endl;
        event_t beg = begs[b];
        event_t end = ends[e];
        if(beg.begin < end.end) {
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
                b--;
            }
        } else {
            currents.erase(end.id);
            if (curr_e.id == end.id) {
                curr_e.end = end.end;
                res.push_back(curr_e);
                // Note, could be implemented with a heap, but too lazy.
                if (currents.size() > 0) {
                    set<int>::iterator new_id = max_element(currents.begin(), currents.end());
                    curr_e.id = *new_id;
                    curr_e.begin = end.end;
                }
            }
            e++;
        }
    }

    return res;
}

void dumpv(vector<struct event_t> &vec) {
    for (int i=0; i<vec.size();i++) {
        cout << vec[i];
        if (i < (vec.size()-1)) {
            cout << ",";
        }
    }
}

int main() {
    bool ok = true;

    {
    struct event_t e1 = { 10, 20, 1 };
    struct event_t arr[] = { e1 };
    vector<struct event_t> v(arr, arr+ sizeof(arr)/sizeof(event_t));
    vector<struct event_t> res = schedule(v);

    struct event_t e1_ref = { 10, 20, 1 };
    struct event_t arr_ref[] = { e1_ref };
    vector<struct event_t> v_ref(arr_ref, arr_ref + sizeof(arr_ref)/sizeof(event_t));

    bool eq = v == v_ref;
    ok &= eq;
    std::cout << (eq ? "OK" : "KO") << " : expected " ; dumpv(v); std::cout << ", got " ; dumpv(v_ref) ; std::cout << std::endl;
    }

    return 0;
}
