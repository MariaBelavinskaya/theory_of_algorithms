#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <string>
#include <locale> // Добавлено для поддержки русской кодировки
#include <codecvt> // Добавлено для поддержки русской кодировки

using namespace std;

const int INF = numeric_limits<int>::max();

void dijkstra(int start, const vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);

    dist[start] = 0;

    for (int i = 0; i < n - 1; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        visited[u] = true;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    cout << "Кратчайшие расстояния от вершины " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "До вершины " << i << " расстояние: " << (dist[i] == INF ? "бесконечность" : std::to_string(dist[i])) << endl;
    }
}

int main() {
    // Установка локали для поддержки русского языка
    setlocale(LC_ALL, "Russian");

    int n, m;
    cout << "Введите количество вершин и рёбер: ";
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);

    cout << "Введите рёбра в формате (u v вес):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u].emplace_back(v, weight);
        graph[v].emplace_back(u, weight); // Для неориентированного графа
    }

    int start;
    cout << "Введите начальную вершину: ";
    cin >> start;

    dijkstra(start, graph);

    return 0;
}
