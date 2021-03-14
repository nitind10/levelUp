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

    //173 ===============================================================================================

    /*will be traversed as 
        while(obj.hasNext())
            print obj.next(); */
    class BSTIterator {

        //implemented as a stack using addFirst and removeFirst fns of linked list
        LinkedList<TreeNode> st = new LinkedList<>();
         BSTIterator(TreeNode root) {
             addAllLeft(root);
         }
         
         void addAllLeft(TreeNode node){
             if(node == null)
                 return;
             
             TreeNode temp = node; 
             while(temp != null){
                 st.addFirst(temp);
                 temp = temp.left;
             }
         }
         int next() {
            TreeNode rn = new TreeNode((int)-1e9);
            if(hasNext()){
                rn = st.removeFirst();
                addAllLeft(rn.right);
            }
            return rn.val;
         }
         
         boolean hasNext() {
             return st.size() > 0;
         }
     }

     //510 ======================================================================================
     //here Node has a pointer pointing to its parent also
    public static Node inorderSuccessorII(Node node){
        if(node.right != null){
            node = node.right;
            while(node.left != null)
                node = node.left;
            return node;
        }
        else{
            while(node != null){
                if(node.parent != null && node.parent.left == node)
                    return node.parent;
                node = node.parent;
            }
            return null;
        }
     }

     //105 =========================================================================================
     int idx = 0;
    public int findIdx(int[] inorder, int data, int si, int ei){
        for(int i = si; i <= ei; ++i){
            if(inorder[i] == data)
                return i;
        }
        //wont reach here
        return -1;
    }
    
    public void buildTree(TreeNode node, int[] preorder, int[] inorder, int si, int ei){
        if(si > ei)
            return;
        
        int pos = findIdx(inorder, node.val, si, ei);
        if( pos > si){
            node.left = new TreeNode(preorder[++idx]);
            buildTree(node.left, preorder, inorder, si, pos - 1);
        }
        if(pos < ei){
            node.right = new TreeNode(preorder[++idx]);
            buildTree(node.right, preorder, inorder, pos + 1, ei);
        }
    }
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        TreeNode root = new TreeNode(preorder[0]);
        buildTree(root, preorder, inorder, 0, preorder.length - 1);
        return root;
    }

    //106 ===========================================================================================
    public TreeNode buildInPost(int[] inorder, int isi, int iei, int[] postorder, int psi, int pei){
        if(psi > pei)
            return null;
        
        int idx = isi;
        while(inorder[idx] != postorder[pei])
            idx++;
        
        int tnel = idx - isi;
        
        TreeNode node = new TreeNode(postorder[pei]);
        node.left = buildInPost(inorder, isi, idx - 1, postorder, psi, psi + tnel - 1);
        node.right = buildInPost(inorder, idx + 1, iei, postorder, psi + tnel, pei - 1);
        
        return node;
    }
    public TreeNode buildTree(int[] inorder, int[] postorder) {
        int n = inorder.length;
        return buildInPost(inorder, 0, n - 1, postorder, 0, n - 1);
    }

    //889 =================================================================================================
    public TreeNode PrePost(int[] pre, int psi, int pei, int[] post, int ppsi, int ppei){
        
        if(psi > pei)
            return null;
        
        TreeNode node = new TreeNode(pre[psi]);
        
        if(psi == pei)
            return node;
        
        int idx = ppsi;
        while(post[idx] != pre[psi + 1])
            idx++;
        int tnel = idx - ppsi + 1;
        
        node.left = PrePost(pre, psi + 1, psi + tnel, post, ppsi, idx);
        node.right = PrePost(pre, psi + tnel + 1, pei, post, idx + 1, ppei - 1);
        
        return node;
    }
    public TreeNode constructFromPrePost(int[] pre, int[] post) {
        int n = pre.length;
        return PrePost(pre, 0, n - 1, post, 0, n - 1);
    }

    //114 ============================================================================================================
    //O(N^2) sol : sub work can be done iterativelty too
    public class pair{
        TreeNode head = null;
        TreeNode lastPre = null;
        pair(TreeNode head, TreeNode lastPre){
            this.head = head;
            this.lastPre = lastPre;
        }
    }
    public void recPreOrder(TreeNode root, TreeNode[] arr){
        if(root == null)
            return;
        arr[0] = root;
        recPreOrder(root.left, arr);
        recPreOrder(root.right, arr);
    }
    public pair flat(TreeNode root){
        if(root == null)
            return new pair(null, null);
        if(root.left == null && root.right == null)
            return new pair(root, root);
        
        pair leftans = flat(root.left);
        pair rightans = flat(root.right);
        
        if((leftans.head != null && rightans.head != null) || (rightans.head == null)){
            root.right = leftans.head;
            leftans.lastPre.right = rightans.head;
        }
        if(leftans.head == null){
            root.right = rightans.head;
        }
        root.left = null;
        
        TreeNode[] arr = new TreeNode[1];
        arr[0] = null;
        recPreOrder(root, arr);
        return new pair(root, arr[0]);
    }
    public void flatten(TreeNode root) {
        flat(root);
    }


    //O(N) sol
    public TreeNode flat(TreeNode root){
        if(root == null)
            return null;
         
        TreeNode leftTail = flat(root.left);
        TreeNode rightTail =  flat(root.right);
        
        if(leftTail != null){
            leftTail.right = root.right;
            root.right = root.left;
            root.left = null;
        }
         
        if(leftTail == null && rightTail == null)
            return root;
         
         return rightTail != null ? rightTail : leftTail;
     }
    public void flatten(TreeNode root) {
        flat(root);
    }


    //426 locked / https://practice.geeksforgeeks.org/problems/binary-tree-to-dll/1#
    class Solution
    {   Node dummy = new Node(-1);
        Node prev = dummy;
    
        void convert(Node root){
            if(root == null)
                return;
            convert(root.left);
            
            prev.right = root;
            root.left = prev;
            prev = root;
            
            convert(root.right);
        }
        
        Node bToDLL(Node root)
        {
        //  Your code here	
            convert(root);
            Node head = dummy.right;
            head.left = null;
            dummy.right = null;
            return head;
        }
    }




    public static void main(String[] args){

    }
}
