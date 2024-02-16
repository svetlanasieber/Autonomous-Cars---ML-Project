// Here's a more complex example of path planning for autonomous cars considering multimodal transportation options, such as integrating public transit and ride-sharing services.

// This example demonstrates how Dijkstra's algorithm can be adapted for path planning in autonomous cars considering multimodal transportation options, 
// such as integrating public transit and ride-sharing services, to optimize travel time and efficiency in urban environments.

// The dijkstra function is modified to perform path planning considering both road-based and transit-based options. 
// It explores road segments and transit edges to find the shortest path from a source intersection to a destination intersection or transit stop.
// The main function initializes both the road and transit networks, performs multimodal path planning using Dijkstra's algorithm, and outputs the shortest path considering both road-based and transit-based options.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

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


struct TransitStop {
    int id; // Stop ID
    bool isTransfer; // Indicates if it's a transfer stop (e.g., subway station)
    TransitStop(int _id, bool _isTransfer = false) : id(_id), isTransfer(_isTransfer) {}
};


struct TransitEdge {
    int from; // Source stop ID
    int to; // Destination stop ID
    int weight; // Weight representing travel time or waiting time
    TransitEdge(int _from, int _to, int _weight) : from(_from), to(_to), weight(_weight) {}
};


struct CompareDistance {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // Compare distances (for min heap)
    }
};


vector<int> dijkstra(const vector<vector<Edge>>& roadGraph, const vector<vector<TransitEdge>>& transitGraph,
                     int source, int destination) {
    vector<int> roadDistances(roadGraph.size(), numeric_limits<int>::max()); // Initialize road distances to infinity
    vector<int> transitDistances(transitGraph.size(), numeric_limits<int>::max()); // Initialize transit distances to infinity
    vector<int> predecessors(roadGraph.size(), -1); // Store predecessors for backtracking
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareDistance> pq; // Priority queue for selecting the next node

    roadDistances[source] = 0; // Distance from source to source is 0
    pq.push({source, 0}); // Add source node to the priority queue

    while (!pq.empty()) {
        int currentIntersection = pq.top().first; // Get the intersection with the smallest distance
        int currentDistance = pq.top().second;
        pq.pop();

        if (currentIntersection == destination) {
            break; // Found shortest path to destination
        }

        
        for (const Edge& roadEdge : roadGraph[currentIntersection]) {
            int neighborIntersection = roadEdge.to;
            int newDistance = currentDistance + roadEdge.weight;

            if (newDistance < roadDistances[neighborIntersection]) {
                roadDistances[neighborIntersection] = newDistance; // Update distance to neighbor
                predecessors[neighborIntersection] = currentIntersection; // Record predecessor for backtracking
                pq.push({neighborIntersection, newDistance}); // Add neighbor to priority queue
            }
        }

     
        for (const TransitEdge& transitEdge : transitGraph[currentIntersection]) {
            int neighborStop = transitEdge.to;
            int newDistance = currentDistance + transitEdge.weight;

            if (newDistance < transitDistances[neighborStop]) {
                transitDistances[neighborStop] = newDistance; // Update distance to neighbor transit stop
                pq.push({neighborStop, newDistance}); // Add neighbor transit stop to priority queue
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
    
    vector<vector<Edge>> roadGraph(10); // 10 intersections in the simplified road network

    vector<vector<TransitEdge>> transitGraph(5); // 5 transit stops in the simplified transit network



    int sourceIntersection = 0;
    int destinationIntersection = 9;
    vector<int> shortestPath = dijkstra(roadGraph, transitGraph, sourceIntersection, destinationIntersection);

    cout << "Shortest path from intersection " << sourceIntersection << " to intersection " << destinationIntersection << ": ";
    for (int intersection : shortestPath) {
        cout << intersection << " ";
    }
    cout << endl;

    return 0;
}
