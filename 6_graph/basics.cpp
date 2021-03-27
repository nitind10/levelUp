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

//DFS ========================================================================================================

//since we are asked whether any path existes or not => no need to mark false in backtrcking
bool hasPath(int src, int dest, vector<bool>& visited){
    if(src == dest)
        return true;

    visited[src] = true;
    bool res = false;

    for(Edge e : graph[src])
        if(!visited[e.v])
            res = res || hasPath(e.v, dest, visited);
    
    return res;
}

int printAllPaths(int src, int dest, vector<bool>& visited, string psf){
    if(src == dest){
        psf = psf + to_string(src) + " ";
        cout << psf << endl;
        return 1;
    }

    psf = psf + to_string(src) + " ";
    int count = 0;

    visited[src] = true;

    for(Edge e : graph[src])
        if(!visited[e.v])
            count += printAllPaths(e.v, dest, visited, psf);

    visited[src] = false;
    return count;
}

class heavyPair{
    public:
        int weight = 0;
        string path = "";

        heavyPair(int weight, string path){
            this -> weight = weight;
            this -> path = path;
        }
};
heavyPair heavyPath(int src, int dest, vector<bool>& visited){
    if(src == dest){
        heavyPair base(0, to_string(dest));
        return base;
    }

    visited[src] = true;
    heavyPair myAns(-1e8, "");

    for(Edge e : graph[src]){
        if(!visited[e.v]){
            heavyPair rres = heavyPath(e.v, dest, visited);
            if(rres.weight != -1e8 && e.w + rres.weight > myAns.weight){
                myAns.weight = e.w + rres.weight;
                myAns.path = to_string(src) + " " + rres.path;
            }
        }
    }

    visited[src] = false;
    return myAns;
}

int hamiltonialPathAndCycle(int src, int osrc, vector<bool>& visited, string psf, int numOfEdges){
    if(numOfEdges == N - 1){
        psf += to_string(src);
        int idx = findEdge(src, osrc);
        if(idx != -1)
            cout << "Cycle : " << psf << endl;
        else
            cout << "Path : " << psf << endl;
        return 1;
    }
    
    int count = 0;
    psf = psf + to_string(src) + " ";

    visited[src] = true;
    for(Edge e : graph[src]){
        if(!visited[e.v]){
            count += hamiltonialPathAndCycle(e.v, osrc, visited, psf, numOfEdges + 1);
        }
    }
    visited[src] = false;

    return count;
}

void GCC_(int src, vector<bool>& visited){
    visited[src] = true;
    for(Edge e : graph[src]){
        if(!visited[e.v]){
            GCC_(e.v, visited);
        }
    }
}
int GCC(){
    vector<bool> visited(N, false);
    int components = 0;
    for(int i = 0; i < N; ++i){
        if(!visited[i]){
            GCC_(i, visited);
            components++;
        }
    }
    return components;
}

//BFS ==========================================================================================================

//use this for detecting cycle only,
//its a bit inefficient i.e pushes extra nodes in queue, but makes things easier for cycle detection
void BFS_Cycle(int src){
    int dest = 6;
    bool isCycle = false;

    int level = 0;
    int atLevel = -1;

    vector<bool> visited(N, false);

    queue<int> que;
    que.push(src);

    while(que.size() != 0){
        int size = que.size();
        cout << level << " -> ";

        while(size--){
            int rv = que.front();
            que.pop();

            if(visited[rv]){
                isCycle = true;
                continue;
            }

            visited[rv] = true;
            cout << rv << ", ";

            if(rv == dest)
                atLevel = level;

            for(Edge e : graph[rv]){
                if(!visited[e.v])
                    que.push(e.v);
            }
        }
        level++;
        cout << endl;
    }

    cout << dest << " present at edge distance : " << atLevel << endl;
    cout << "isCycle : " << boolalpha << isCycle << endl;
}

//most optmized bfs, every node is pushed only once, use for shortest path
//can be used for cycle detection(putting else if condition in for loop, but a bit complex, as we'll need a parent array too), so avoid
void BFS_shortestPath(int src, vector<bool>& visited){
    int level = 0;
    int atLevel = -1;
    int dest = 6;

    queue<int> que;
    que.push(src);

    //imp
    visited[src] = true;

    while(que.size() != 0){
        int size = que.size();

        while(size--){
            int rv = que.front();
            que.pop();

            if(rv == dest)
                atLevel = level;

            for(Edge e : graph[rv]){
                if(!visited[e.v]){
                    visited[e.v] = true;
                    que.push(e.v);
                }
            }
        }
        level++;
    }

    cout << "Shortest path for " << dest << " is : " << atLevel << endl;
}

void BFS_printShortestPath(int src, int dest, vector<bool>& visited){
    int level = 0;
    int atLevel = -1;
    vector<int> par(N, -1);

    queue<int> que;
    que.push(src);

    //imp
    visited[src] = true;

    while(que.size() != 0){
        int size = que.size();

        while(size--){
            int rv = que.front();
            que.pop();

            if(rv == dest)
                atLevel = level;

            for(Edge e : graph[rv]){
                if(!visited[e.v]){
                    visited[e.v] = true;
                    que.push(e.v);
                    par[e.v] = rv;
                }
            }
        }
        level++;
    }

    cout << "Shortest path for " << dest << " is : ";
    int idx = dest;
    while(idx != -1){
        cout << idx << " -> ";
        idx = par[idx];
    }
}

void BFS_GCC(){
    int components = 0;
    vector<bool> visited(N, false);

    for(int i = 0; i < N; ++i){
        if(!visited[i]){
            BFS_shortestPath(i, visited);
            components++;
        }
    }
    cout << "Totoal components in the graph are : " << components << endl;
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

    //addEdge(6, 0, 10);
    addEdge(2, 8, 3);
    addEdge(2, 7, 1);
}

int main(){
    constructGraph();
    vector<bool> visited(N, false);
    //BFS_Cycle(0);
    //BFS_shortestPath(0, visited);
    //BFS_printShortestPath(0, 8, visited);
    BFS_GCC();
    return 0;
}