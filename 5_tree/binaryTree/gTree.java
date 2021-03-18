import java.util.ArrayList;

public class gTree {
    public static class Node{
        int val = 0;
        ArrayList<Node> childs;

        Node(int val){
            this.val = val;
            this.childs = new ArrayList<>();
        }
    }

    public static int size(Node node){
        //only needed if whole tree is given empty(generaly not the case), also check it in calling fn, otherwise it will be checked everytime in recursion
        // if(node == null)
        //     return 0;

        int sz = 0;
        for(Node child : node.childs)
            sz += size(child);
        return sz + 1;
    }

    public static int height(Node node){
        int h = -1;
        for(Node child : node.childs)
            h = Math.max(h, height(child));
        return h  +1;
    }

    public static int maximum(Node node){
        int maxEle = node.val;
        for(Node child : node.childs)
            maxEle = Math.max(maxEle, maximum(child));
        return maxEle;
    }

    public static int minimum(Node node){
        int minEle = node.val;
        for(Node child : node.childs)
            minEle = Math.min(minEle, minimum(child));
        return minEle;
    }

    //find ======================================================
    public static boolean find(Node node, int data){
        if(node.val == data)
            return true;
        for(Node child : node.childs)
            if(find(child, data))
                return true;
        
        return false;
    }

    //depth of a node ========================================================================
    public static int find01(Node node, int data) {
        if (node.val == data)
            return 0;

        int depth = -1;
        for (Node child : node.childs) {
            depth = find01(child, data);
            if (depth != -1)
                break;
        }

        if (depth != -1)
            depth++;

        return depth;
    }

    //node to root path ====================================================
    public static boolean nodeToRootPath(Node node, ArrayList<Node> ans, int data){
        if(node.val == data){
            ans.add(node);
            return true;
        }
        boolean res = false;
        for(Node child : node.childs){
            res = res || nodeToRootPath(child, ans, data);
        }
        if(res) 
            ans.add(node);
        return res;
    }

    //LCA ============================================================================
    public static Node LCA(Node root, int d1, int d2){
        ArrayList<Node> ans1 = new ArrayList<>();
        nodeToRootPath(root, ans1, d1);
        ArrayList<Node> ans2 = new ArrayList<>();
        nodeToRootPath(root, ans2, d2);

        Node lca = null;
        int i = ans1.size() - 1, j = ans2.size() - 1;
        while(i > -1 && j > -1){
            if(ans1.get(i) != ans2.get(j))
                break;
            lca = ans1.get(i);
            i--;
            j--;
        }
        return lca;
    }

    //burning tree ===================================================================================================
    public void kDown(Node root, Node blockNode, int time, List<List<Integer>> ans) {
        if (root == blockNode)
            return;

        if (ans.size() == time)
            ans.add(new ArrayList<>());

        ans.get(time).add(root.val);
        for (Node child : root.childs)
            kDown(child, blockNode, time + 1, ans);

    }

    // Method_01
    public List<List<Integer>> burningTree_01(Node root, int target) {
        ArrayList<Node> list = new ArrayList<>();
        rootToNodePath(root, target, list);

        List<List<Integer>> ans = new ArrayList<>();
        Node blockNode = null;

        for (int i = 0; i < list.size(); i++) {
            kDown(list.get(i), blockNode, i, ans);
            blockNode = list.get(i);
        }

        return ans;
    }

    // Method_02
    public int burningTree_02(Node root, int target, List<List<Integer>> ans) {
        if (root.val == target) {
            kDown(root, null, 0, ans);
            return 1;
        }

        int time = -1;
        Node blockNode = null;
        for (Node child : root.childs) {
            time = burningTree_02(child, target, ans);
            if (time != -1) {
                blockNode = child;
                break;
            }
        }

        if (time != -1) {
            kDown(root, blockNode, time, ans);
            time++;
        }
        return time;
    }


    public static void main(String[] args){

    }
}
