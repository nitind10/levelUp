import java.util.LinkedList;

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

    //morris pre order ======================================================================================
    void morrisPreOrder(TreeNode root){
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
                    System.out.print(curr.val + " ");
                    curr = curr.left;
                }
                else{ //break thread
                    rightMost.right = null;
                    curr = curr.right;
                }
            }
        }
    }

    //iterative traversals(pre in and post) ==========================================================================
    public static class tPair{
        TreeNode node = null;
        boolean leftDone = false;
        boolean selfDone = false;
        boolean rightDone = false;

        tPair(TreeNode node, boolean leftDone, boolean selfDone, boolean rightDone){
            this.node = node;
            this.leftDone = leftDone;
            this.selfDone = selfDone;
            this.rightDone = rightDone;
        }
    }
    //shift if else for pre and post
    public static void iterativeTraversal(TreeNode root){
        LinkedList<tPair> st = new LinkedList<>();
        st.addFirst(new tPair(root, false, false, false));

        while(st.size() != 0){
            tPair pair = st.getFirst();
            if(!pair.leftDone){
                pair.leftDone = true;
                if(pair.node.left != null)
                    st.addFirst(new tPair(pair.node.left, false, false, false));
            }
            else if(!pair.selfDone){
                pair.selfDone = true;
                System.out.print(pair,node.val + " ");
            }
            else if(!pair.rightDone){
                pair.rightDone = true;
                if(pair.node.right != null)
                    st.addFirst(new tPair(pair.node.right, false, false, false));
            }
            else{
                st.removeFirst();
            }
        }
    }

    //1008 ====================================================================================
    int idx = 0;
    public TreeNode bstFromPreorder_(int[] preorder, int lr, int rr){
        if(idx == preorder.length || preorder[idx] < lr || preorder[idx] > rr)
            return null;
        TreeNode node = new TreeNode(preorder[idx++]);
        node.left = bstFromPreorder_(preorder, lr, node.val);
        node.right = bstFromPreorder_(preorder, node.val, rr);
        
        return node;
    }
    public TreeNode bstFromPreorder(int[] preorder) {
        return bstFromPreorder_(preorder, -(int)1e9, (int)1e9);
    }

    //BST from level order ============================================================================================
    public static class levelPair{
        TreeNode par = null;
        int lb = -(int) 1e8;
        int rb = (int) 1e8;

        levelPair(){
        }

        levelPair(TreeNode par, int lb, int rb){
            this.par = par;
            this.lb = lb;
            this.rb = rb;
        }
    }
    public TreeNode bstFromLevelOrder(int[] levelOrder){
        int idx = 0;
        LinkedList<levelPair> que = new LinkedList<>();
        que.add(new levelPair());
        TreeNode root = null;

        while(que.size() != 0 && idx < levelOrder.length){
            levelPair pair = que.removeFirst();

            if(levelOrder[idx] < pair.lb || levelOrder[idx] > pair.rb)
                continue;
            
            TreeNode node = new TreeNode(levelOrder[idx++]);
            if(pair.par == null)
                root = node;
            else{
                if(node.val < pair.par.val)
                    pair.par.left = node;
                else
                    pair.par.right = node;
            }

            que.add(new levelPair(node, pair.lb, node.val));
            que.add(new levelPair(node, node.val, pair.rb));
        }
        return root;
    }



    public static void main(String[] args){

    }
}
