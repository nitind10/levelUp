//questions started from 16 feb 2021 class

public class questions3 {
    public static class TreeNode{
        int val = 0;
        TreeNode left = null;
        TreeNode right = null;

        TreeNode(int val){
            this.val = val;
        }
    }

    //morris inorder traversal ======================================================================
    TreeNode rightMostNode(TreeNode curr, TreeNode next){
        while(next.right != null && next.right != curr)
            next = next.right;
        return next;
    }
    void morrisInOrder(TreeNode root){
        TreeNode curr = root;
        while(curr != null){
            TreeNode next = curr.left;
            if(next == null){
                System.out.print(curr.val + " ");
                curr = curr.right;
            }
            else{
                TreeNode rightMost = rightMostNode(curr, next);
                if(rightMost.right == null){ //make thread
                    rightMost.right = curr;
                    curr = curr.left;
                }
                else{ //break thread
                    rightMost.right = null;
                    System.out.print(curr.val + " ");
                    curr = curr.right;
                }
            }
        }
    }
    public static void main(String[] args){

    }
}
