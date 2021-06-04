public class questions {

    // 407 Trapping Rain Water II ===================================================================================
    public int trapRainWater(int[][] heightMap) {
        int n = heightMap.length, m = heightMap[0].length;

        //java has lambda fn, which is written in this scope only => it can communicate with matrix, not in c++, bcoz comparable class cant access matrix heightMap
        PriorityQueue<Integer> pq = new PriorityQueue<>((a, b) -> {
            int i1 = a / m, j1 = a % m;
            int i2 = b / m, j2 = b % m;

            return heightMap[i1][j1] - heightMap[i2][j2];
        });

        boolean[][] vis = new boolean[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                    vis[i][j] = true;
                    pq.add(i * m + j);
                }
            }
        }

        int[][] dir = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

        int minBoun = 0, water = 0;

        while (pq.size() != 0) {
            int idx = pq.remove();
            int i = idx / m, j = idx % m;

            minBoun = Math.max(minBoun, heightMap[i][j]);
            water += minBoun - heightMap[i][j];

            for (int d = 0; d < 4; d++) {
                int r = i + dir[d][0];
                int c = j + dir[d][1];

                if (r >= 0 && c >= 0 && r < n && c < m && !vis[r][c]) {
                    vis[r][c] = true;
                    pq.add(r * m + c);
                }
            }
        }

        return water;
    }

}

