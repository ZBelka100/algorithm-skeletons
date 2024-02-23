#include <bits/stdc++.h>

template <typename T>
class Graph {
private:
    int64_t vertices;
    std::vector<std::vector<T>> adjacencyList; // список смежности
    std::vector<bool> visited; //Для отслеживание перемещений в алгоритмах bfs, dfs
    std::vector<T> path; // Вектор для хранения пути

public:
    Graph(int64_t vertices) : vertices(vertices), adjacencyList(vertices), visited(vertices, false) {} //в adjacencyList пустые векторы в количестве vertices штук

    void addEdge(int64_t u, int64_t v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u); // для неориентированного графа
    }

    void displayGraph() {
        for (int64_t i = 0; i < vertices; ++i) {
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

template <typename T>
class Grid {
private:
    int64_t rows;
    int64_t cols;
    std::vector<std::vector<T>> grid;

public:
    Grid(int64_t rows, int64_t cols) : rows(rows), cols(cols), grid(rows, std::vector<T>(cols)) {}

    void setCell(int64_t row, int64_t col, const T& value) {
        grid[row][col] = value;
    }

    T getCell(int64_t row, int64_t col) const {
        return grid[row][col];
    }

    void displayGrid() const {
        for (int64_t i = 0; i < rows; ++i) {
            for (int64_t j = 0; j < cols; ++j) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::pair<int64_t, int64_t>> bfs(int64_t startRow, int64_t startCol) const {
        std::vector<std::pair<int64_t, int64_t>> result;
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
        std::queue<std::pair<int64_t, int64_t>> queue;

        visited[startRow][startCol] = true;
        queue.push({startRow, startCol});

        while (!queue.empty()) {
            std::pair<int64_t, int64_t> current = queue.front();
            result.push_back(current);
            queue.pop();

            const int64_t directions[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};//всевозможные мувы

            for (const auto& direction : directions) {
                int64_t newRow = current.first + direction[0];
                int64_t newCol = current.second + direction[1];

                if (isValid(newRow, newCol) && !visited[newRow][newCol]) {
                    visited[newRow][newCol] = true;
                    queue.push({newRow, newCol});
                }
            }
        }

        return result;
    }

private:
    //метод для проверки допустимости координат
    bool isValid(int64_t row, int64_t col) const {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }
};

int main() {
    return 0;
}