// simulate a simplified road network with various road conditions, such as one-way streets, intersections with traffic lights, and different speed limits
// Dijkstra's algorithm is used to find the shortest path from a source intersection to a destination intersection.
// The graph weights represent factors such as distance or travel time between intersections.
// The main function initializes the road network, performs path planning using Dijkstra's algorithm, and outputs the shortest path from a source intersection to a destination intersection.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

using namespace std;


struct Node {
    int id; // Intersection ID
    Node(int _id) : id(_id) {}
};


struct Edge {
    int from; // Source intersection ID
    int to; // Destination intersection ID
    int weight; // Weight representing distance or travel time
    Edge(int _from, int _to, int _weight) : from(_from), to(_to), weight(_weight) {}
};


struct CompareDistance {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // Compare distances (for min heap)
    }
};


vector<int> dijkstra(const vector<vector<Edge>>& graph, int source, int destination) {
    vector<int> distances(graph.size(), numeric_limits<int>::max()); // Initialize distances to infinity
    vector<int> predecessors(graph.size(), -1); // Store predecessors for backtracking
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareDistance> pq; // Priority queue for selecting the next node

    distances[source] = 0; // Distance from source to source is 0
    pq.push({source, 0}); // Add source node to the priority queue

    while (!pq.empty()) {
        int currentIntersection = pq.top().first; // Get the intersection with the smallest distance
        int currentDistance = pq.top().second;
        pq.pop();

        if (currentIntersection == destination) {
            break; // Found shortest path to destination
        }

        for (const Edge& edge : graph[currentIntersection]) {
            int neighborIntersection = edge.to;
            int newDistance = currentDistance + edge.weight;

            if (newDistance < distances[neighborIntersection]) {
                distances[neighborIntersection] = newDistance; // Update distance to neighbor
                predecessors[neighborIntersection] = currentIntersection; // Record predecessor for backtracking
                pq.push({neighborIntersection, newDistance}); // Add neighbor to priority queue
            }
        }
    }

    
    vector<int> shortestPath;
    int currentIntersection = destination;
    while (currentIntersection != source) {
        shortestPath.push_back(currentIntersection);
        currentIntersection = predecessors[currentIntersection];
    }
    shortestPath.push_back(source); // Add source intersection to the shortest path
    reverse(shortestPath.begin(), shortestPath.end()); // Reverse the path to get it in correct order

    return shortestPath;
}

int main() {
 
    vector<vector<Edge>> graph(10); // 10 intersections in the simplified road network

    // Add road segments between intersections (edges in the graph)
    graph[0].push_back(Edge(0, 1, 10)); // Road from intersection 0 to intersection 1 with weight 10 (distance or travel time)
    graph[0].push_back(Edge(0, 2, 15)); // Road from intersection 0 to intersection 2 with weight 15
    graph[1].push_back(Edge(1, 3, 20)); // Road from intersection 1 to intersection 3 with weight 20
    graph[2].push_back(Edge(2, 4, 25)); // Road from intersection 2 to intersection 4 with weight 25
    graph[3].push_back(Edge(3, 5, 15)); // Road from intersection 3 to intersection 5 with weight 15
    graph[4].push_back(Edge(4, 5, 10)); // Road from intersection 4 to intersection 5 with weight 10
    graph[5].push_back(Edge(5, 6, 10)); // Road from intersection 5 to intersection 6 with weight 10
    graph[5].push_back(Edge(5, 7, 15)); // Road from intersection 5 to intersection 7 with weight 15
    graph[6].push_back(Edge(6, 8, 20)); // Road from intersection 6 to intersection 8 with weight 20
    graph[7].push_back(Edge(7, 8, 25)); // Road from intersection 7 to intersection 8 with weight 25
    graph[8].push_back(Edge(8, 9, 10)); // Road from intersection 8 to intersection 9 with weight 10


    int sourceIntersection = 0;
    int destinationIntersection = 9;
    vector<int> shortestPath = dijkstra(graph, sourceIntersection, destinationIntersection);
    cout << "Shortest path from intersection " << sourceIntersection << " to intersection " << destinationIntersection << ": ";
    for (int intersection : shortestPath) {
        cout << intersection << " ";
    }
    cout << endl;

    return 0;
}
