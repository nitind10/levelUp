
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

//450 ====================================================================================
int maximumOfTree(TreeNode* node){
    TreeNode *temp = node;
    while(temp -> right != nullptr)
        temp = temp -> right;
    return temp -> val;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if(root == nullptr)
        return root;
    if(root -> val > key)
        root -> left = deleteNode(root -> left, key);
    else if(root -> val < key)
        root -> right = deleteNode(root -> right, key);
    //key found
    else{
        //leaf node, single parent (both cases) handeled
        if(root -> left == nullptr || root -> right == nullptr)
            return root -> left == nullptr ? root -> right : root -> left;
        
        //node has both sub trees
        int maxOfLST = maximumOfTree(root -> left);
        root -> val = maxOfLST;
        root -> left = deleteNode(root -> left, maxOfLST); 
    }
    return root;
}

//235 ==============================================================
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode *temp = root;
    while(temp != nullptr){
        if(temp -> val > p -> val && temp -> val > q -> val)
            temp = temp -> left;
        else if(temp -> val < p -> val && temp -> val < q -> val)
            temp = temp -> right;
        //cant decide where to go => this is the LCA
        else
            return temp;
    }
    return nullptr;
}

//108 =======================================================================
TreeNode* createBST(vector<int>& nums, int si, int ei){
    if(si > ei)
        return nullptr;
    
    int mid = (si + ei)/2;
    TreeNode* node = new TreeNode(nums[mid]);
    
    node -> left = createBST(nums, si, mid - 1);
    node -> right = createBST(nums, mid + 1, ei);
    
    return node;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
    return createBST(nums, 0, nums.size() - 1);
}