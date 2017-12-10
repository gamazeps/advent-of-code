

void bfs(const vector<vector<int>>& graph, int node) {
    vector<int> fifo;
    unorder_set<int> visisted;

    visisted.insert(node);

    fifo.push_back(node);
    while(!fifo.empty()) {
        int curr = fifo.pop_front();
        cout << curr << endl;
        for (int e : graph[curr]) {
            if (visited.count(e) < 1) {
                visited.insert(e);
                fifo.push_back(e);
            }
        }
    }
}

void dfs(const vector<vector<int>>& graph, int node, vector<bool>& visited) {
    visited[node] = true;
    for (const auto& e in graph[node]) {
        if (!visited[e]) {
            visited[e] = true;
            bfs(graph, e, visited);
        }
    }
    cout << node << endl;
}

int main() {

}
