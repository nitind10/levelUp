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

} //end of class{}
