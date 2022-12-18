#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

#include "Funcs.h"

// used chatGPT for dijkstras implementation (worked really well made 1 mistake though)

using namespace std;

const int INF = numeric_limits<int>::max();

int dist[ROWS * COLS]; // distance from the source to each node
bool visited[ROWS * COLS]; // whether the node has been visited in the search

void dijkstra(int source, int num_nodes, vector<pair<int, int>> adj[ROWS * COLS]) {
    // initialize distances and visited array
    for (int i = 1; i < num_nodes; i++) {
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

int DoDijkstra(vector<pair<int, int>> adj[ROWS * COLS], int source, int num_nodes) {
    // run Dijkstra's algorithm from the source node
    dijkstra(source, num_nodes, adj);

    return 0;
}
