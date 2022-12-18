#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

// used chatGPT for dijkstras implementation

using namespace std;

const int INF = numeric_limits<int>::max();

vector<pair<int, int>> adj[1001]; // adjacency list representation of the graph
int dist[1001]; // distance from the source to each node
bool visited[1001]; // whether the node has been visited in the search

void dijkstra(int source, int num_nodes) {
    // initialize distances and visited array
    for (int i = 1; i <= num_nodes; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    // set distance of source to 0
    dist[source] = 0;

    // create a priority queue to store nodes
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // insert the source node into the priority queue
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // skip the node if it has already been visited
        if (visited[u]) continue;
        visited[u] = true;

        // iterate through all the neighbors of the node
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            // relax the edge if the distance to the neighbor can be shortened
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

int main() {
    int num_nodes, num_edges, source;
    cin >> num_nodes >> num_edges >> source;

    // read in the edges and add them to the adjacency list
    for (int i = 0; i < num_edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
    }

    // run Dijkstra's algorithm from the source node
    dijkstra(source, num_nodes);

    return 0;
}
