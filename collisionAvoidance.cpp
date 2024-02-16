//  include collision detection with obstacles such as pedestrians, cyclists, or vehicles
// A threshold distance is used for collision detection, and Dijkstra's algorithm ensures that the calculated path avoids collisions with obstacles by considering them during path planning.
// The main function initializes the road network (graph), defines obstacles, and performs
// collision avoidance path planning using Dijkstra's algorithm. 
// The resulting path ensures safety by avoiding collisions with obstacles while reaching the destination efficiently

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

struct Node {
    int id; // Intersection ID
    double x, y; // Coordinates of the intersection (for collision detection)
    Node(int _id, double _x, double _y) : id(_id), x(_x), y(_y) {}
};

struct Edge {
    int from; // Source intersection ID
    int to; // Destination intersection ID
    double weight; // Weight representing distance or travel time
    Edge(int _from, int _to, double _weight) : from(_from), to(_to), weight(_weight) {}
};

struct CompareDistance {
    bool operator()(const pair<int, double>& a, const pair<int, double>& b) {
        return a.second > b.second; // Compare distances (for min heap)
    }
};

double computeDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}


vector<int> dijkstra(const vector<vector<Edge>>& graph, const vector<Node>& intersections,
                     int source, int destination, const vector<Node>& obstacles) {
    vector<double> distances(graph.size(), numeric_limits<double>::max()); // Initialize distances to infinity
    vector<int> predecessors(graph.size(), -1); // Store predecessors for backtracking
    priority_queue<pair<int, double>, vector<pair<int, double>>, CompareDistance> pq; // Priority queue for selecting the next node

    distances[source] = 0; // Distance from source to source is 0
    pq.push({source, 0}); // Add source node to the priority queue

    while (!pq.empty()) {
        int currentIntersection = pq.top().first; // Get the intersection with the smallest distance
        double currentDistance = pq.top().second;
        pq.pop();

        if (currentIntersection == destination) {
            break; // Found shortest path to destination
        }

        for (const Edge& edge : graph[currentIntersection]) {
            int neighborIntersection = edge.to;
            double newDistance = currentDistance + edge.weight;

            if (newDistance < distances[neighborIntersection]) {
                // Check for collision with obstacles
                bool collision = false;
                for (const Node& obstacle : obstacles) {
                    double distanceToObstacle = computeDistance(intersections[neighborIntersection].x,
                                                                 intersections[neighborIntersection].y,
                                                                 obstacle.x, obstacle.y);
                    if (distanceToObstacle < 5.0) { // Threshold distance for collision detection
                        collision = true;
                        break;
                    }
                }

                if (!collision) {
                    distances[neighborIntersection] = newDistance; // Update distance to neighbor
                    predecessors[neighborIntersection] = currentIntersection; // Record predecessor for backtracking
                    pq.push({neighborIntersection, newDistance}); // Add neighbor to priority queue
                }
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
  
    vector<Node> intersections = {
        Node(0, 0.0, 0.0), // Example intersection 0
        Node(1, 10.0, 5.0), // Example intersection 1
        Node(2, 15.0, 10.0), // Example intersection 2
        // Add more intersections as needed
    };

    vector<vector<Edge>> graph(intersections.size()); // Graph representing road network
    // Populate graph with road segments (edges) between intersections

 
    vector<Node> obstacles = {
        Node(3, 5.0, 2.0), // Example obstacle 1
        Node(4, 12.0, 7.0), // Example obstacle 2
        // Add more obstacles as needed
    };

 
    int sourceIntersection = 0;
    int destinationIntersection = 2;
    vector<int> shortestPath = dijkstra(graph, intersections, sourceIntersection, destinationIntersection, obstacles);

 
    cout << "Shortest path from intersection " << sourceIntersection << " to intersection " << destinationIntersection << ": ";
    for (int intersection : shortestPath) {
        cout << intersection << " ";
    }
    cout << endl;

    return 0;
}
