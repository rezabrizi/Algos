#include <bits/stdc++.h>

class Graph {
    std::vector<std::unordered_set<int>> adj_list; 
    std::vector<bool> visited; 

    void dfs(int node, int& count) {
        visited[node] = true;
        for (const int neighbor : adj_list[node]) {
            if (!visited[neighbor]) {
                count++;
                dfs(neighbor, count);
            }
        }
    }

public: 
    Graph(int n): adj_list(n), visited(n, false) {}

    void add_edge(int u, int v) {
        adj_list[u].insert(v);
        adj_list[v].insert(u);
    }

    void reset_visited() {
        std::fill(visited.begin(), visited.end(), false);
    }

    int find_min_steps_node() {
        int min_steps = std::numeric_limits<int>::max();
        int min_steps_node = -1;

        for (int i = 0; i < adj_list.size(); ++i) {
            int steps = 0;
            reset_visited();
            dfs(i, steps);
            
            if (steps < min_steps) {
                min_steps = steps;
                min_steps_node = i;
            }
        }

        return min_steps_node;
    }
};

int main() {
    Graph g(5); // Create a graph with 5 nodes

    // Add edges to the graph
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);

    int min_steps_node = g.find_min_steps_node();
    std::cout << "Node with minimum steps to visit all nodes: " << min_steps_node << std::endl;

    return 0;
}
