#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Edge{
    public:
        int v = 0;
        int w = 0;

        Edge(int v, int w){
            this -> v = v;
            this -> w = w;
        }
};

const int N = 11;
vector<vector<Edge>> graph(N);

void addEdge(int u, int v, int w){
    //directed
    graph[u].push_back(Edge(v, w));
}

void display(){
    int vertices = graph.size();

    for(int i = 0; i < vertices; ++i){
        cout << i << " -> ";
        for(Edge e : graph[i])
            cout << "(" << e.v << "," << e.w << ") ";
        cout << endl;
    }
}

//topological sort works for a directed acyclic graph i.e DAG

//gives topological sort order using DFS ==============================================
//will also give answer when there is cycle(gotta use in kosaraju step1), but that wont make sense when considering it as the order to solve dependencies
void DFS_topo_helper(int src, vector<bool>& visited, vector<int>& ans){
    visited[src] = true;
    for(Edge e : graph[src])
        if(!visited[e.v])
            DFS_topo_helper(e.v, visited, ans);

    ans.push_back(src);
}
vector<int> DFS_topo(){
    vector<bool> visited(N, false);
    vector<int> ans;
    for(int i = 0; i < N; ++i){
        if(!visited[i])
            DFS_topo_helper(i, visited, ans);
    }
    // cout << "Dependencies should be resolved in order : ";
    // for(int ele : ans)
    //     cout << ele << " ";
    // cout << endl; 

    return ans;
}

//gives topological sort order using BFS (if cycle not present), otherwise flag the presence of cycle ================================================
void kahnsAlgo(){
    vector<int> indegree(N, 0);

    for(int i = 0; i < N; ++i){
        for(Edge e : graph[i])
            indegree[e.v]++;
    }

    int level = 0;
    queue<int> que;
    vector<int> ans;

    for(int i = 0; i < N; ++i)
        if(indegree[i] == 0)
            que.push(i);
    
    while(que.size() != 0){
        int size = que.size();

        while(size--){
            int rv = que.front();
            que.pop();
            ans.push_back(rv);

            for(Edge e : graph[rv]){
                if(--indegree[e.v] == 0)
                    que.push(e.v);
            }
        }
        level++;
    }

    if(ans.size() < N){
        cout << "There is a a cycle in graph, hence dependencies can not be resolved" << endl;
    }
    else{
        cout << "Dependencies should be resloved in order : ";
        for(int i = ans.size() - 1; i > -1; --i)
            cout << ans[i] << " ";
        cout << endl;
    }
}

//gives topological sort order using DFS (if cycle not present), otherwise flag the presence of cycle ================================================
bool isCyclePresent_DFSTopo(int src, vector<int> &vis, vector<int> &ans)
{
    vis[src] = 0;
    bool res = false;
    for (Edge e : graph[src])
    {
        if (vis[e.v] == -1)
        { // unvisited
            res = res || isCyclePresent_DFSTopo(e.v, vis, ans);
        }
        else if (vis[e.v] == 0)
        {
            
            vis[src] = 1; // ***************** required acc to me, sir forgot maybe

            return true; // there is cycle.
        }
    }

    vis[src] = 1;
    ans.push_back(src);
    return res;
}

vector<int> isCyclePresent_DFS()
{
    vector<int> vis(N, -1);
    vector<int> ans;

    bool res = false;
    for (int i = 0; i < N; i++)
    {
        if (vis[i] == -1)
        {
            res = res || isCyclePresent_DFSTopo(i, vis, ans);
        }
    }

    if (res)
        ans.clear();
    return ans;
}

//kosaraju algo  to find strongly connected components(SCC) =======================================================
void SCC(int src, vector<bool>& visited, vector<int>& component, vector<vector<Edge>>& ngraph){
    visited[src] = true;
    component.push_back(src);
    for(Edge e : ngraph[src])
        if(!visited[e.v])
            SCC(e.v, visited, component, ngraph);
}
void kosaraju(){
    //step 1: topolocial sort
    vector<int> ans = DFS_topo();

    //step 2 : create an inverse graph
    vector<vector<Edge>> ngraph(N);
    for(int i = 0; i < N; ++i){
        for(Edge e : graph[i]){
            ngraph[e.v].push_back(Edge(i, 1));
        }
    }

    //step 3: find SCC
    vector<bool> visited(N, false);
    for(int i = ans.size() - 1; i > -1; --i){
        if(!visited[ans[i]]){
            vector<int> component;
            SCC(ans[i], visited, component, ngraph);
            for(int ele : component)
                cout << ele << " ";
            cout << endl;
        }
    }
}


void constructGraph(){
    // addEdge(0, 1, 10);
    // addEdge(0, 3, 10);
    // addEdge(1, 2, 10);
    // addEdge(2, 3, 40);
    // addEdge(3, 4, 2);
    // addEdge(4, 5, 2);
    // addEdge(4, 6, 8);
    // addEdge(5, 6, 3);
    // addEdge(2, 8, 3);
    // addEdge(2, 7, 1);

    // addEdge(8, 7, 3);
    // addEdge(7, 2, 3);

    //kosaraju
    addEdge(0, 1, 1);
    addEdge(1, 2, 1);
    addEdge(1, 10, 1);
    addEdge(2, 0, 1);
    addEdge(2, 3, 1);
    addEdge(2, 4, 1);
    addEdge(3, 5, 1);
    addEdge(3, 6, 1);
    addEdge(3, 7, 1);
    addEdge(4, 3, 1);
    addEdge(5, 4, 1);
    addEdge(6, 5, 1);
    addEdge(6, 9, 1);
    addEdge(7, 8, 1);
    addEdge(8, 9, 1);
    addEdge(9, 7, 1);
    addEdge(10, 7, 1);
    addEdge(10, 8, 1);
}

int main(){
    constructGraph();
    // DFS_topo();
    // kahnsAlgo();
    kosaraju();
    return 0;
}

