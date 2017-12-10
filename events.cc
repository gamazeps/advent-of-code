#include <algorithm>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

class Event {
  public:
    int begin;
    int end;
    int id; // lowest the better

    Event(int begin, int end, int id) : begin(begin), end(end), id(id) {}
    Event() : begin(0), end(0), id(0) {}

    bool operator==(const Event& other) const {
        return this->begin == other.begin && this->end == other.end && this->id == other.id;
    }

    friend std::ostream & operator<<(std::ostream &os, const Event& p);
};

ostream& operator<<(ostream& os, const Event& p)  {  
    os << "{" << p.begin << ","<< p.end << ","<< p.id << "}";
    return os;
}  


bool starts_before(Event a, Event b) {
    return a.begin < b.begin;
}

bool ends_before(Event a, Event b) {
    return a.end < b.end;
}

vector<Event> schedule(vector<Event> input) {
    // First generate the list of starts and ends
    vector<Event> begs(input);
    sort(begs.begin(), begs.end(), starts_before);
    vector<Event> ends(input);
    sort(ends.begin(), ends.end(), ends_before);

    vector<Event> res;

    set<int> currents;
    int b(0), e(0);
    bool done_beg(false);
    Event curr_e;

    while (e < ends.size()) {
        Event beg = begs[b];
        Event end = ends[e];
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

template <class T>
void dumpv(const vector<T>& vec) {
    for (const T& e : vec) {
        cout << e << " ";
    }
    cout << endl;
}

template <class T>
bool all_eq(const vector<T>& a, const vector<T>& b) {
    if (a.size() != b.size()) {
        return false;
    }

    for (int i(0); i<a.size(); i++) {
       if (!(a[i] == b[i])) {
          return false;
       }
    }

   return true; 
}

bool test_case(const vector<Event>& input, const vector<Event>& expected) {
    vector<Event> res = schedule(input);
    if (!all_eq(expected, res)) {
        cout << "expected: ";
        dumpv(expected);
        cout << "got: ";
        dumpv(res);
        return false;
    }
    return true;
}

int main() {
    {
        vector<Event> v = {Event(10, 20, 1), Event(0, 30, 2)};
        vector<Event> res = schedule(v);
        vector<Event> v_ref = {Event(0, 10, 2), Event(10, 20, 1), Event(20, 30, 2)};
        test_case(v, v_ref);

    }

    return 0;
}
