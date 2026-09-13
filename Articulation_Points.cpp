#include <iostream>                      // Ujjawal roy
#include <vector>                        // 25/DA/061
#include <algorithm>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

    void DFS(int u, int parent, vector<int>& disc,
             vector<int>& low, vector<bool>& visited,
             vector<bool>& articulation, int& timer) {

        visited[u] = true;

        disc[u] = low[u] = timer++;

        int children = 0;

        for (int v : adj[u]) {

            if (v == parent)
                continue;

            if (!visited[v]) {

                children++;

                DFS(v, u, disc, low, visited, articulation, timer);

                low[u] = min(low[u], low[v]);

                if (parent == -1 && children > 1)
                    articulation[u] = true;

                if (parent != -1 && low[v] >= disc[u])
                    articulation[u] = true;
            }

            else {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void findArticulationPoints() {

        vector<int> disc(V, -1);
        vector<int> low(V, -1);

        vector<bool> visited(V, false);
        vector<bool> articulation(V, false);

        int timer = 0;

        for (int i = 0; i < V; i++) {

            if (!visited[i]) {
                DFS(i, -1, disc, low,
                   visited, articulation, timer);
            }
        }

        cout << "Articulation Points: ";

        bool found = false;

        for (int i = 0; i < V; i++) {

            if (articulation[i]) {
                cout << i << " ";
                found = true;
            }
        }

        if (!found)
            cout << "None";

        cout << endl;
    }
};

int main() {

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter edges:\n";

    for (int i = 0; i < E; i++) {

        int u, v;
        cin >> u >> v;

        g.addEdge(u, v);
    }

    g.findArticulationPoints();

    return 0;
}
