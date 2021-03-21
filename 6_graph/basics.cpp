#include<iostream>
#include<vector>

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

const int N = 7;
vector<vector<Edge>> graph(N);

void addEdge(int u, int v, int w){
    //bi
    graph[u].push_back(Edge(v, w));
    graph[v].push_back(Edge(u, w));
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

int findEdge(int u, int v){
    int idx = -1;

    for(int i = 0; i < graph[u].size(); ++i)
        if(graph[u][i].v == v){
            idx = i;
            break;
        }
    
    return idx;
}

void removeEdge(int u, int v){ //T(N) : O(V + E)
    int idx1 = findEdge(u, v); //O(V)
    int idx2 = findEdge(v, u); //O(V)

    if(idx1 != -1)
        graph[u].erase(graph[u].begin() + idx1); //O(E)
    if(idx2 != -1)
    graph[v].erase(graph[v].begin() + idx2); //O(E)
}

void removeVtx(int u){
    for(int i = graph[u].size() - 1; i > -1; --i){
        int v = graph[u][i].v;
        removeEdge(u, v);
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
}

int main(){
    constructGraph();
    display();
    //removeEdge(4,3);
    removeVtx(3);
    display();
    return 0;
}