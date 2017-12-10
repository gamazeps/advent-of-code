typedef struct event_t {
    int begin;
    int end;
    int id; // lowest the better
} event_t;

vector<event_t> schedule(vector<event_t> input) {
    // First generate the list of starts and ends
    vector<event_t> begs(input);
    sort(begs.begin(), begs.end(), begin_time); // TODO: impl sort by begin;
    vector<event_t> ends(input);
    sort(begs.begin(), begs.end(), end_time); // TODO: impl sort by begin;

    vector<event_t> res;

    set<int> currents;
    int b(0), e(0);
    event_t curr_e;

    while (e < ends.size()) {
        event_t beg = begs[b];
        event_t end = ends[e];
        if(beg.begin < end.end) {
            currents.insert(beg.id);
            if (currents.size == 1) {
                curr_e = beg; // this is now our only event.
            }
            else if (beg.id < curr_e.id) {
                curr_e.end = beg.begin;
                res.push_back(curr_e); // we finish our event;
                curr_e = beg; // The end is false but we will change it.
            }
            b++;
        } else {
            currents.erase(end.id);
            if (curr_e.id == end.id) {
                curr_e.end = end.end;
                res.push_back(curr_e);
                // Note, could be implemented with a heap, but too lazy.
                if (currents.size() > 0) {
                    int new_id = max_elem(currents.begin(), currents.end());
                    curr_e.id = *new_id;
                    curr_e.begin = end.end;
                }
            }
        }
    }

    return res;
}
