import java.util.ArrayList;

public class basics{
    public static class Edge{
        int v = 0;
        int w = 0;

        Edge(int v, int w){
            this.v = v;
            this.w = w;
        }
    }

    static int N = 7;

    //used because on left we are using Edge dataType but on left we aren't specifying
    @SuppressWarnings("unchecked")
    //wee created array of arraylist not arraylist of arraylist, so that syntax can be short i.e graph[i].get(j);
    static ArrayList<Edge>[] graph = new ArrayList[N];

    public static void addEdge(int u, int v, int w){
        //bi
        graph[u].add(new Edge(v, w));
        graph[v].add(new Edge(u, w));
    }
    
    public static void display(){
        int vertices = graph.length;
    
        for(int i = 0; i < vertices; ++i){
            System.out.print(i + " -> ");
            for(Edge y : graph[i])
                System.out.print("(" + y.v + "," + y.w + ") ");
            System.out.println();
        }
    }

    public static int findEdge(int u, int v){
        int idx = -1;
    
        for(int i = 0; i < graph[u].size(); ++i)
            if(graph[u].get(i).v == v){
                idx = i;
                break;
            }
        
        return idx;
    }
    
    public static void removeEdge(int u, int v){ //T(N): O(V + E)
        int idx1 = findEdge(u, v); //O(V)
        int idx2 = findEdge(v, u); //O(V)

        if(idx1 != -1)
            graph[u].remove(idx1); //O(E)
        if(idx2 != -1)
        graph[v].remove(idx2); //O(E)
    }

    public static void removeVtx(int u){
        for(int i = graph[u].size() - 1; i > -1; --i){
            int v = graph[u].get(i).v;
            removeEdge(u, v);
        }
    }
    
    public static void constructGraph(){
        for(int i = 0; i < N; ++i)
            graph[i] = new ArrayList<>();
        
        addEdge(0, 1, 10);
        addEdge(0, 3, 10);
        addEdge(1, 2, 10);
        addEdge(2, 3, 40);
        addEdge(3, 4, 2);
        addEdge(4, 5, 2);
        addEdge(4, 6, 8);
        addEdge(5, 6, 3);
    }
    public static void main(String[] args){
        // constructGraph();
        // display();
        // //removeEdge(0,1);
        // removeVtx(3);
        // display();
    }
}