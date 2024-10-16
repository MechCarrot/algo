#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const int INF = 1e9;
vector <int> dfs(const vector <vector <int> >& g) {
    vector <int> nodes;
    int n = g.size();
    stack <int> Stack;
    vector <int> used(n, 0);
    int iter = 0;
    Stack.push(0);
    while (!Stack.empty())
    {
        int node = Stack.top();
        Stack.pop();
        if (used[node] == 2) continue;
        used[node] = 2; // отмечаем ее как посещенную
        iter++;
        for (int j = 0; j < n; j++)
        {
            if (g[node][j] > 0 && used[j] != 2)
            {
                Stack.push(j);
                used[j] = 1;
            }
        }
        nodes.push_back(node);
    }
    return nodes;
}



vector<int> dijkstra(const vector<vector<int>>& g, int s) {
    int n = g.size();
    vector<int> dist(n, INF);

    // Создаем приоритетную очередь, где first - расстояние, second - вершина
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({ 0, s }); // Начальная вершина s
    dist[s] = 0;

    while (!pq.empty()) {
        int cur_vertex = pq.top().second;
        int cur_dist = pq.top().first;
        pq.pop();

        // Проходим по смежным вершинам
        for (int i = 0; i < n; i++) {
            if (g[cur_vertex][i] != 0 && dist[i] > cur_dist + g[cur_vertex][i]) {
                dist[i] = cur_dist + g[cur_vertex][i];
                pq.push({ dist[i], i });
            }
        }
    }

    return dist;
}

void degreesAVG(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> degrees(n, 0);
    float sumDegrees = 0;

    vector<bool> visited(n, 0);

    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int curr_vertex = q.front();
        q.pop();

        if (visited[curr_vertex]) continue;
        visited[curr_vertex] = 1;

        for (int i = 0; i < n; ++i) {
            if (g[curr_vertex][i]) {
                q.push(i);
                degrees[curr_vertex]++;
            }
        }
    }

    cout << "Degrees:\n";
    for (int i = 0; i < degrees.size(); i++) {
        cout << degrees[i] << " ";
        sumDegrees += degrees[i];
    }
    cout << "\n";
    float avg = sumDegrees / n;
    cout << "AVG: " << avg << "\n";
}
vector<vector<int>> prim(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> parent(n, -1);
    vector<int> w(n, INF);
    vector<bool> used(n, false);

    w[0] = 0;

    // Создаем приоритетную очередь, где first - вес, second - вершина
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({ 0, 0 }); // Начинаем с вершины 0

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        used[u] = true;

        for (int v = 0; v < n; ++v) {
            if (g[u][v] && !used[v] && g[u][v] < w[v]) {
                parent[v] = u;
                w[v] = g[u][v];
                pq.push({ w[v], v }); // Обновляем приоритетную очередь
            }
        }
    }

    vector<vector<int>> MST(n, vector<int>(n, 0));
    for (int i = 1; i < n; ++i) {
        MST[parent[i]][i] = g[i][parent[i]];
        MST[i][parent[i]] = g[i][parent[i]];
    }

    return MST;
}

int main() {
    vector <vector <int> > g = {
        { 0, 1, 3, 0, 1, 3, 6, 6, 7, 1 },
        { 1, 0, 1, 8, 6, 0, 0, 0, 8, 8 },
        { 3, 1, 0, 6, 6, 4, 5, 7, 6, 2 },
        { 0, 8, 6, 0, 1, 3, 0, 3, 4, 3 },
        { 1, 6, 6, 1, 0, 4, 6, 8, 5, 7 },
        { 3, 0, 4, 3, 4, 0, 1, 3, 6, 1 },
        { 6, 0, 5, 0, 6, 1, 0, 4, 7, 1 },
        { 6, 0, 7, 3, 8, 3, 4, 0, 1, 8 },
        { 7, 8, 6, 4, 5, 6, 7, 1, 0, 1 },
        { 1, 8, 2, 3, 7, 1, 1, 8, 1, 0 }
    };

    // Номер 1
    cout << "DFS: \n";
    vector <int> vertices = dfs(g);
    for (int i = 0; i < vertices.size(); i++) {
        cout << vertices[i] << endl;
    }

    //Номер 2
    cout << "BFS: \n";
    int s1 = 0;
    vector <int> distance = dijkstra(g, s1);
    for (int i = 0; i < distance.size(); i++) {
        cout << distance[i] << " ";
    }
    cout << "\n";

    //номер 4
    vector <vector <int> > mst = prim(g);
    cout << "--------------------------------\n";
    cout << "MST\n";
    cout << "--------------------------------\n";
    for (int i = 0; i < mst.size(); i++) {
        for (int j = 0; j < mst[i].size(); j++) {
            cout << mst[i][j] << " ";
        }
        cout << "\n";
    }

    degreesAVG(mst);

    cout << "DFS MST: \n";
    vector <int> verticesMST = dfs(mst);
    for (int i = 0; i < verticesMST.size(); i++) {
        cout << verticesMST[i] << endl;
    }

    cout << "Dijkstra MST: \n";
    vector <int> distanceMST = dijkstra(mst, 0);
    for (int i = 0; i < distanceMST.size(); i++) {
        cout << distanceMST[i] << " ";
    }
    cout << "\n";
    return 0;
}