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
        for(auto y : graph[i])
            cout << "(" << y.v << "," << y.w << ") ";
        cout << endl;
    }
}

void removeEdge(int u, int v){
    for(int i = 0; i < graph[u].size(); ++i){
        if(graph[u][i].v == v)
            graph[u].erase(graph[u].begin() + i);
    }
    for(int i = 0; i < graph[v].size(); ++i){
        if(graph[v][i].v == u)
            graph[v].erase(graph[v].begin() + i);
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
    removeEdge(4,3);
    display();
    return 0;
}