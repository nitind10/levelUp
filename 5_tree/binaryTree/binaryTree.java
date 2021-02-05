public class binaryTree {
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
        return node == null ? -(int)1e9 : Math.max(node.val, Math.max(maximumOfTree(node.left), maximumOfTree(node.right)));
    }

    public int minimumOfTree(TreeNode node){
        return node == null ? (int)1e9 : Math.min(node.val, Math.min(minimumOfTree(node.left), minimumOfTree(node.right)));
    }

    public boolean find(TreeNode node, int data){
        if(node == null)
            return false;
        if(node.val == data)
            return true;
        return find(node.left, data) || find(node.right, data);
    }

    //arraylist passed as parameter, return type boolean
    public boolean nodeToRootPath(TreeNode node, int data, ArrayList<TreeNode> ans){
        if(node == null)
            return false;
        if(node.val == data){
            ans.add(node);
            return true;
        }

        boolean res = nodeToRootPath(node.left, data, ans) || nodeToRootPath(node.right, data, ans);
        if(res == true)
            ans.add(node);
        
        return res;
    }
    //arraylist is return type
    public ArrayList<TreeNode> nodeToRootPath2(TreeNode node, int data){
        if(node == null) 
            return new ArrayList<>();
        if(node.val == data){
            ArrayList<TreeNode> base = new ArrayList<>();
            base.add(node);
        }

        ArrayList<TreeNode> left = nodeToRootPath2(node.left, data);
        if(left.size() > 0){
            left.add(node);
            return left;
        }
        ArrayList<TreeNode> right = nodeToRootPath2(node.right, data);
        if(right.size() > 0){
            right.add(node);
            return right;
        }
        return new ArrayList<>();
    }

    




}
