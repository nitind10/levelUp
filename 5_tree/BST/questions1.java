//question started from 11 feb 2021 class

public class questions1 {
    public static class TreeNode{
        int val = 0;
        TreeNode left = null;
        TreeNode right = null;

        TreeNode(int val){
            this.val = val;
        }
    }

    public static class allSolPair{
        TreeNode prev = null;
        TreeNode pred = null;
        TreeNode succ = null;
    }

    //BINARY TREE : inorder predessor and successor O(N)
    void allSolution(Treenode node, int data, allSolPair pair){
        if(node == null)
            return;

        allSolution(node.left, data, pair);

        if(node.val == data && pair.pred == null)
            pair.pred = pair.prev;
        if(pair.prev != null && pair.prev.val == data && pair.succ == null)
            pair.succ = node;
        pair.prev = node;

        allSolution(node.right, data, pair);
    }

    //BST : predessor and successor O(LogN)\
    void bstPnS(TreeNode node, int data){
        TreeNode curr = node;
        TreeNode pred = null, succ = null;
        while(curr != null){
            if(curr.val == data){
                if(curr.left != null){
                    pred = curr.left;
                    while(pred.right != null)
                        pred = pred.right;
                }
                if(curr.right != null){
                    succ = curr.right;
                    while(succ.left != null)
                        succ = succ.left;
                }
                break;
            }
            else if(curr.val < data){
                pred = curr;
                curr = curr.right;
            }
            else{
                succ = curr;
                curr = curr.left;
            }
        }
    }
    public static void main(String[] args){

    }
}
