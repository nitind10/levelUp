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


    public static void main(String[] args){

    }
}
