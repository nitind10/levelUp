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

const int N = 9;
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

void DFS_topo_helper(int src, vector<bool>& visited, vector<int>& ans){
    visited[src] = true;
    for(Edge e : graph[src])
        if(!visited[e.v])
            DFS_topo_helper(e.v, visited, ans);

    ans.push_back(src);
}
void DFS_topo(){
    vector<bool> visited(N, false);
    vector<int> ans;
    for(int i = 0; i < N; ++i){
        if(!visited[i])
            DFS_topo_helper(i, visited, ans);
    }
    cout << "Dependencies should be resolved in order : ";
    for(int ele : ans)
        cout << ele << " ";
    cout << endl; 
}

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

void constructGraph(){
    addEdge(0, 1, 10);
    addEdge(0, 3, 10);
    addEdge(1, 2, 10);
    addEdge(2, 3, 40);
    addEdge(3, 4, 2);
    addEdge(4, 5, 2);
    addEdge(4, 6, 8);
    addEdge(5, 6, 3);
    addEdge(2, 8, 3);
    addEdge(2, 7, 1);

    // addEdge(8, 7, 3);
    // addEdge(7, 2, 3);

}

int main(){
    constructGraph();
    DFS_topo();
    kahnsAlgo();
    return 0;
}