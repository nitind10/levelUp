
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

 //701 =================================================================================
 //recursive
TreeNode* insertNode(TreeNode* node, int val){
    if(node == nullptr){
            return new TreeNode(val);
    }
        
    if(node -> val > val)
        node -> left = insertNode(node -> left, val);  
    else
        node -> right = insertNode(node -> right, val);
    return node;
}
TreeNode* insertIntoBST(TreeNode* root, int val) {
    return insertNode(root, val);
}

//iterative
TreeNode* insertIntoBST(TreeNode* root, int val) {
    TreeNode *curr = root, *prev = nullptr;

    while(curr != nullptr){
        prev = curr;
        if(curr -> val > val)
            curr = curr -> left;
        else
            curr = curr -> right;
    }

    TreeNode* newNode = new TreeNode(val);

    //empty tree
    if(!prev)
        return newNode;
    else if(prev -> val > val)
        prev -> left = newNode;
    else
        prev -> right = newNode;

    return root;
}