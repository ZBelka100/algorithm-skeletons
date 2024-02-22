#include <bits/stdc++.h>

template <typename T>
class Graph {
private:
    int vertices;
    std::vector<std::vector<T>> adjacencyList; // список смежности
    std::vector<bool> visited; //Для отслеживание перемещений в алгоритмах bfs, dfs
    std::vector<T> path; // Вектор для хранения пути

public:
    Graph(int vertices) : vertices(vertices), adjacencyList(vertices), visited(vertices, false) {} //в adjacencyList пустые векторы в количестве vertices штук

    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u); // для неориентированного графа
    }

    void displayGraph() {
        for (int i = 0; i < vertices; ++i) {
            std::cout << "Смежные вершины для вершины " << i << ": ";
            for (const auto &neighbor : adjacencyList[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << '\n';
        }
    }

    void displayPath() {
        for (auto elem : path) {
            std::cout << elem << ' ';
        }
    }

    void bfs(const T& start) {
        visited.assign(vertices, false); 
        path.clear();
        /*опасное место (то что выше) в случаях применения 
        на одном и том же графе:
        Если используем один раз на графе, то можно бех этого
        Если несколько, то оставляем
        */
        std::queue<T> queue;

        visited[start] = true;
        queue.push(start);

        while (!queue.empty()) {
            T current = queue.front();
            path.push_back(current);//конкретно в этом алгосе он просто вернет, как он шёл на bfs
            queue.pop();

            for (const auto &neighbor : adjacencyList[current]) {
                //условие на соседей, подсчет сумм и тп 
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
    }

    void dfs(const T& start) {
        visited.assign(vertices, false);
        path.clear();
        /*опасное место (то что выше) в случаях применения 
        на одном и том же графе:
        Если используем один раз на графе, то можно бех этого
        Если несколько, то оставляем
        */
        dfsHelper(start);
    }

private:
    void dfsHelper(const T& current) {
        visited[current] = true;
        path.push_back(current);

        for (const auto &neighbor : adjacencyList[current]) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor);
            }
        }
    }
};


int main() {
    Graph<int> myGraph(5);

    myGraph.addEdge(0, 1);
    myGraph.addEdge(0, 2);
    myGraph.addEdge(1, 3);
    myGraph.addEdge(2, 4);

    myGraph.displayGraph();

    std::cout << "DFS: ";
    myGraph.dfs(0);
    myGraph.displayPath();


    std::cout << "BFS: ";
    myGraph.bfs(0);
    myGraph.displayPath();

    return 0;
}