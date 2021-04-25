//after dijkstra algo
public class questions{


    //743 ================================================================
public int networkDelayTime(int[][] times, int n, int k) {

    ArrayList<int[]>[] graph = new ArrayList[n + 1];
    for (int i = 0; i < n + 1; i++)
        graph[i] = new ArrayList<>();

    // {u -> {v,w} }
    for (int[] ar : times) {
        graph[ar[0]].add(new int[] { ar[1], ar[2] });
    }

    int[] dis = new int[n + 1];
    Arrays.fill(dis, (int) 1e9);
    boolean[] vis = new boolean[n + 1];

    // {vtx,wsf}
    PriorityQueue<int[]> que = new PriorityQueue<>((a, b) -> {
        return a[1] - b[1];
    });

    que.add(new int[] { k, 0 });
    dis[k] = 0;
    int NoOfEdges = 0;
    int maxvalue = 0;
    while (que.size() != 0) {
        int[] p = que.remove();
        int vtx = p[0], wsf = p[1];

        if (vis[vtx])
            continue;
        if (vtx != k)
            NoOfEdges++;

        maxvalue = Math.max(maxvalue, wsf);

        vis[vtx] = true;
        for (int[] e : graph[vtx]) {
            if (!vis[e[0]] && e[1] + wsf < dis[e[0]]) {
                dis[e[0]] = e[1] + wsf;
                que.add(new int[] { e[0], e[1] + wsf });
            }
        }
    }

    if (NoOfEdges != n - 1)
        return -1;

    return maxvalue;
}


//787 ==================================================================================================================
 //using bellman ford algo
 public int findCheapestPrice(int n, int[][] flights, int src, int dst, int K) {
    int[] dis = new int[n];
    Arrays.fill(dis, (int) 1e9);
    dis[src] = 0;

    for (int EdgeCount = 1; EdgeCount <= K + 1; EdgeCount++) {
        int[] ndis = new int[n];
        for (int i = 0; i < n; i++)
            ndis[i] = dis[i];

        for (int[] e : flights) {
            int u = e[0], v = e[1], w = e[2];
            if (dis[u] != (int) 1e9 && dis[u] + w < ndis[v])
                ndis[v] = dis[u] + w;
        }

        dis = ndis;
    }

    return dis[dst] != (int) 1e9 ? dis[dst] : -1;
}


//924 ===============================================================================================================
int [] size,par;
    
public int findPar(int u){
    return par[u] == u ? u : (par[u] = findPar(par[u]));
}
public int minMalwareSpread(int[][] graph, int[] initial) {
    int n = graph.length;
    size = new int[n];
    par = new int[n];

    for (int i = 0; i < n; i++) {
        par[i] = i;
        size[i] = 1;
    }

    Arrays.sort(initial);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && graph[i][j] == 1) {
                int p1 = findPar(i);
                int p2 = findPar(j);

                if (p1 != p2) {
                    par[p1] = p2;
                    size[p2] += size[p1];
                }
            }
        }
    }

    int[] InfectedNodesInCity = new int[n];
    for (int i : initial) {
        int leader = findPar(i);
        InfectedNodesInCity[leader]++;
    }

    int ans = initial[0];
    int maxPopulatedCity = 0;
    for (int i : initial) {
        int NoOfNodesInfected = InfectedNodesInCity[findPar(i)];
        if (NoOfNodesInfected == 1 && size[findPar(i)] > maxPopulatedCity) {
            maxPopulatedCity = size[findPar(i)];
            ans = i;
        }
    }

    return ans;
}

}//end of class {}
