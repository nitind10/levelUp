public class bst {
    public class TreeNode{
        int val = 0;
        TreeNode left = null;
        TreeNode right = null;

        TreeNode(int val){
            this.val = val;
        }
    }

    public int size(TreeNode node){
        return node == null ? 0 : size(node.left) + size(node.right) + 1;
    }

    //for calculating in terms of nodes, return 0 if node is null
    public int height(TreeNode node){
        return node == null ? -1 : Math.max(height(node.left), heigth(node.right)) + 1;
    }

    public int maximumOfTree(TreeNode node){
        TreeNode temp = node;
        while(temp.right != null)
            temp = temp.right;
        return temp.val;
    }

    public int minimumOfTree(TreeNode node){
        TreeNode temp = node;
        while(temp.left != null)
            temp = temp.left;
        return temp.val;
    }

    //iterative
    public boolean findData1(TreeNode node, int data){
        TreeNode temp = node;
        while(temp != null){
            if(temp.val == data)
                return true;
            else if(temp.val > data)
                temp = temp.left;
            else
                temp = temp.right;
        }
        return false;
    }

    //recursive, vImp for adding, in AVL concepts etc..
    public boolean findData2(TreeNode node, int data){
        if(node == null)
            return false;
        if(node.val == data)
            return true;

        if(node.val > data)
            return findData2(node.left, data);
        else
            return findData2(node.right, data);
    }
}
