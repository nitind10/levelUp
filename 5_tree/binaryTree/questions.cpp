//leetcode problems
 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


//863 =============================================================================
vector<int> ans;

void printKDown(TreeNode *node, int depth, TreeNode *block){
    if(node == nullptr  || depth < 0 || node == block)
        return;
    if(depth == 0){
        ans.push_back(node -> val);
        return;
    }
    printKDown(node -> left, depth - 1, block);
    printKDown(node -> right, depth - 1, block);
}
int rootToNodeDistance(TreeNode *node, TreeNode *target, int k){
    if(node == nullptr)
        return -1;
    if(node == target){
        printKDown(node, k, nullptr);
        return 0;
    }
    int leftAns = rootToNodeDistance(node -> left, target, k);
    if(leftAns != -1){
        printKDown(node, k - (leftAns + 1), node -> left);
        return leftAns + 1;
    }
    int rightAns = rootToNodeDistance(node -> right, target, k);
    if(rightAns != -1){
        printKDown(node, k - (rightAns + 1), node -> right);
        return rightAns + 1;
    }
    return -1;
}
vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
    rootToNodeDistance(root, target, K);
    return ans;
}

//543 ======================================================================================
//o(n^2)
int height(TreeNode* root){
    if(root == nullptr)
        return -1;
    return max(height(root -> left), height(root -> right)) + 1;
}
int diameter(TreeNode* root){
    if(root == nullptr)
        return -1;
    int leftDia = diameter(root -> left);
    int rightDia = diameter(root -> right);
    return max(max(leftDia, rightDia), height(root -> left) + height(root -> right) + 2);
}
int diameterOfBinaryTree(TreeNode* root) {
    if(root == nullptr)
        return 0;
    return diameter(root);
}
//o(n)
//pair has dia, height
pair<int, int> diameter(TreeNode* root){
    if(root == nullptr)
        return {-1, -1};
    pair<int, int> leftpair = diameter(root -> left);
    pair<int, int> rightpair = diameter(root -> right);
    return max(max(leftpair.first, rightpair.first), leftpair.second + rightpair.second + 2);
}
int diameterOfBinaryTree(TreeNode* root) {
    if(root == nullptr)
        return 0;
    return diameter(root).first;
}
//o(n) but with a global variable
int maxDia = 0;
int diameter(TreeNode *root){
    if(root == nullptr)
        return -1;
    int heightLeft = (root -> left);
    int heightRight = diameter(root -> right);

    maxDia = max(maxDia, heightLeft + heightRight + 2);
    return max(heightLeft, heigthRight) + 1;
}
int diameterOfBinaryTree(TreeNode* root) {
    if(root == nullptr)
        return 0;
    diameter(root);
    return maxDia;
}

//112 ============================================================================
bool pathSumHelper(TreeNode* node, int targetSum){
    if(node == nullptr)
        return false;
    if( node -> left == nullptr && node -> right == nullptr)
        return targetSum - node -> val == 0;
    return  pathSumHelper(node -> left, targetSum - node -> val) || pathSumHelper(node -> right, targetSum - node -> val);
}
bool hasPathSum(TreeNode* root, int targetSum) {
    return pathSumHelper(root, targetSum);
}

//113 ========================================================================================
void pathSumHelper(TreeNode* node, int targetSum, vector<int>& currPath, vector<vector<int>>& ans){
    if(node == nullptr)
        return;
    
    if(targetSum - node -> val == 0 && node -> left == nullptr && node -> right == nullptr){
        ans.push_back(currPath);
        ans.back().push_back(node -> val);
        return;
    }
    currPath.push_back(node -> val);
    pathSumHelper(node -> left, targetSum - node -> val, currPath, ans);
    pathSumHelper(node -> right, targetSum - node -> val, currPath, ans);
    currPath.pop_back();
}
vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> ans;
    vector<int> currPath;
    pathSumHelper(root, targetSum, currPath, ans);
    return ans;
}



