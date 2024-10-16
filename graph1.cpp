#include <iostream>
#include<queue>
#include<stack>
#include<vector>

using namespace std;


const int INF = 10000;

void FillVectorWith(vector<int>& v, int value, int size = 0)
{
	if (size != 0)
	{
		v.resize(0);
		for (int i = 0; i < size; i++)
			v.push_back(value);
	}
	for (int i = 0; i < v.size(); i++)
		v[i] = value;
}

void FillMatrixWith(vector<vector<int> >& matrix, int value, int width = 0, int height = 0)
{
	if (width != 0 && height != 0)
	{
		matrix.resize(0);
		int i, j;
		for (i = 0; i < height; i++)
		{
			vector<int> v1;
			for (j = 0; j < width; j++)
			{
				v1.push_back(value);
			}
			matrix.push_back(v1);
		}
	}
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
			matrix[i][j] = value;
	}
}

int FindPath(vector<vector<int> >& f, vector<vector<int> >& c, int source, int target, int vertices) // source - исток, target - сток
{
	int i;
	int CurVertex;
	// Flow - значение потока через данную вершину на данном шаге поиска
	// Link[i] хранит номер предыдущей вешины на пути i -> исток
	vector<int> Flow; FillVectorWith(Flow, 0, vertices);
	vector<int> Link; FillVectorWith(Link, -1, vertices);
	Flow[source] = INF;
	vector<int> used(vertices, 0);
	//queue<int> q; q.push(source);
	stack<int> s; s.push(source);
	//while (!q.empty())
	while(!s.empty())
	{
		//int vertex = q.front();
		int vertex = s.top();
		if (vertex == target) break;
		s.pop();
		//q.pop();

		for (int i = 0; i < vertices; i++)
		{
			//есть ребро vertex->i, в i не заходили
			if (c[vertex][i]-f[vertex][i] > 0 && used[i]==0)
			{
				s.push(i);//q.push(i);
				Flow[i] = (c[vertex][i] - f[vertex][i] < Flow[vertex]) ? c[vertex][i] - f[vertex][i] : Flow[vertex];
				Link[i] = vertex;
			}
		}
		used[vertex] = 1;
	}

	if (Link[target] == -1) return 0;
	CurVertex = target;
	while (CurVertex != source)
	{
		f[Link[CurVertex]][CurVertex] += Flow[target];
		CurVertex = Link[CurVertex];
	}
	//cout << "\n" << Flow[target] << ": ";
	//for (int i = 0; i < vertices; i++) cout << Link[i] << " ";
	return Flow[target];
}

// основная функция поиска максимального потока
int MaxFlow(vector<vector<int> >& f, vector<vector<int> >& c, int source, int target, int vertices) // source - исток, target - сток
{
	FillMatrixWith(f, 0);
	int MaxFlow = 0;
	int AddFlow;
	do
	{
		AddFlow = FindPath(f, c, source, target, vertices);
		MaxFlow += AddFlow;
	} while (AddFlow > 0);
	return MaxFlow;
}

bool hamilton(vector<vector<int> >& mat, vector <bool>& visited, vector <int>& path, int curr)
{
	path.push_back(curr);
	//путь содержит все вершины: если есть связь последней вершины с исходной, цикл найден
	//если нет, откатываемся на шаг назад
	//вершина использована в пути
    for (int i = 0; i < path.size(); i++) {
        cout << " " << path[i] << " ";
    } cout << "\n";
	visited[curr] = true;
	//проверить всех непосещенных соседей вершины curr
	if (path.size() == mat[0].size() && mat[path[path.size() - 1]][path[0]] != 0) return true;
	if (path.size() == mat[0].size() && mat[path[path.size() - 1]][path[0]] == 0)
	{
		visited[curr] = false;
		path.pop_back();
		return false;
	}

	for (int i = 0; i < mat[0].size(); i++)
	{
		if (mat[curr][i] > 0 && !visited[i])
			if (hamilton(mat, visited, path, i)) return true;
	}

	//этот путь не подходит, убираем вершину и откатываемся
	visited[curr] = false;
	path.pop_back();
	return false;
}



void colorGraph(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> colors(n, -1); 

    for (int v = 0; v < n; ++v) {
        vector<bool> available(n, true);
        for (int i = 0; i < n; ++i) {
            if (graph[v][i]) {
                if (colors[i] != -1) { 
                    available[colors[i]] = false;
                }
            }
        }

        int c;
        for (c = 0; c < n; ++c) { 
            if (available[c])
                break;
        }
        colors[v] = c;
    }

    for (int v = 0; v < n; ++v) {
        cout << v << " - " << colors[v] << endl;
    }
}

int main()
{
    vector <vector <int> > g = { { 0, 1, 3, 0, 1, 3, 6, 6, 7, 1 },
    { 1, 0, 1, 8, 6, 0, 0, 0, 8, 8 },
    { 3, 1, 0, 6, 6, 4, 5, 7, 6, 2 },
    { 0, 8, 6, 0, 1, 3, 0, 3, 4, 3 },
    { 1, 6, 6, 1, 0, 4, 6, 8, 5, 7 },
    { 3, 0, 4, 3, 4, 0, 1, 3, 6, 1 },
    { 6, 0, 5, 0, 6, 1, 0, 4, 7, 1 },
    { 6, 0, 7, 3, 8, 3, 4, 0, 1, 8 },
    { 7, 8, 6, 4, 5, 6, 7, 1, 0, 1 },
    { 1, 8, 2, 3, 7, 1, 1, 8, 1, 0 }};
    int n = g.size();
	int source = 0; 
	int target = n-1; 
	vector<vector<int> > f;
	FillMatrixWith(f, 0, n, n);

	cout << "Max flow: " << MaxFlow(f, g, source, target, n) << "\n";
    vector<bool> visited(n, 0);
	vector<int> path;
    cout << "Hamilton\n";
    if(hamilton(g, visited, path, 0)){ 
        for (int i = 0; i < path.size(); i++) {
            cout << " " << path[i] << " ";
        } cout << "\n";
    } else{
        cout << "Hemiltonian cycle is not possible on graph G" << "\n";
    }
    colorGraph(g);
	return 0;
}