#include <bits/stdc++.h>

template <typename T>
class BellmanFord {
private:
    int vertices;
    std::vector<std::tuple<int, int, T>> edges;

public:
    BellmanFord(int vertices) : vertices(vertices) {}

    void addEdge(int from, int to, T weight) {
        edges.emplace_back(from, to, weight);
    }

    std::vector<T> runAlgorithm(int start) const {
        std::vector<T> distance(vertices, std::numeric_limits<T>::max());
        distance[start] = 0;

        for (int i = 0; i < vertices - 1; ++i) {
            for (const auto& edge : edges) {
                int u, v;
                T weight;
                std::tie(u, v, weight) = edge;

                if (distance[u] != std::numeric_limits<T>::max() && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                }
            }
        }

        return distance;
    }
};

template <typename T>
class Dijkstra {
private:
    int vertices;
    std::vector<std::vector<std::pair<int, T>>> adjacencyList;

public:
    Dijkstra(int vertices) : vertices(vertices), adjacencyList(vertices) {}

    void addEdge(int from, int to, T weight) {
        adjacencyList[from].emplace_back(to, weight);
    }

    std::vector<T> runAlgorithm(int start) const {
        std::vector<T> distance(vertices, std::numeric_limits<T>::max());
        distance[start] = 0;

        std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const auto& neighbor : adjacencyList[u]) {
                int v = neighbor.first;
                T weight = neighbor.second;

                if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    pq.push({distance[v], v});
                }
            }
        }

        return distance;
    }
};

template <typename T>
class FloydWarshall {
private:
    int vertices;
    std::vector<std::vector<T>> distance;

public:
    FloydWarshall(int vertices) : vertices(vertices), distance(vertices, std::vector<T>(vertices, std::numeric_limits<T>::max())) {}

    void addEdge(int from, int to, T weight) {
        distance[from][to] = weight;
    }

    void runAlgorithm() {
        for (int k = 0; k < vertices; ++k) {
            for (int i = 0; i < vertices; ++i) {
                for (int j = 0; j < vertices; ++j) {
                    if (distance[i][k] != std::numeric_limits<T>::max() &&
                        distance[k][j] != std::numeric_limits<T>::max() &&
                        distance[i][k] + distance[k][j] < distance[i][j]) {
                        distance[i][j] = distance[i][k] + distance[k][j];
                    }
                }
            }
        }
    }

    void displayResult() const {
        std::cout << "Shortest distances between vertices:" << std::endl;
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (distance[i][j] == std::numeric_limits<T>::max()) {
                    std::cout << "INF ";
                } else {
                    std::cout << distance[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};

