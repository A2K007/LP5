#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int src, int des)
    {
        adj[src].push_back(des);
        adj[des].push_back(src);
    }

    void parallelBFS(int src)
    {
        vector<bool> visited(adj.size(), false);
        queue<int> q;
        q.push(src);
        visited[src] = true;
        while (!q.empty())
        {
            int now;
#pragma omp parallel shared(q, visited)
            {
#pragma omp single
                {
                    now = q.front();
                    cout << now << " ";
                    q.pop();
                }
                if (adj[now].size() != 0)
                {
#pragma omp for
                    for (int i = 0; i < adj[now].size(); i++)
                    {
                        if (!visited[adj[now][i]])
                        {
#pragma omp critical
                            {
                                q.push(adj[now][i]);
                                visited[adj[now][i]] = true;
                            }
                        }
                    }
                }
            }
        }
    }

    void parallelDFSUtil(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";

#pragma omp parallel for
        for (int i = 0; i < adj[v].size(); i++)
        {
            int u = adj[v][i];
            if (!visited[u])
            {
                parallelDFSUtil(u, visited);
            }
        }
    }

    void parallelDFS(int src)
    {
        vector<bool> visited(V, false);
        parallelDFSUtil(src, visited);
    }
};

int main()
{
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    cout << "Parallel Breadth First Search (BFS) starting from vertex 0: ";
    g.parallelBFS(0);
    cout << endl;

    cout << "Parallel Depth First Search (DFS) starting from vertex 0: ";
    g.parallelDFS(0);
    cout << endl;
    return 0;
}