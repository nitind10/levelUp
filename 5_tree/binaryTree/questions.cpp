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

//https://practice.geeksforgeeks.org/problems/maximum-path-sum/1#   ==========================================================
pair<int,int> maxSumLeafToLeaf(Node *node){
        if(node == nullptr)
            return {INT_MIN, INT_MIN};
        if(node -> left == nullptr && node -> right == nullptr)
            return {INT_MIN, node -> data};
            
        pair<int,int> leftAns = maxSumLeafToLeaf(node -> left);
        pair<int,int> rightAns = maxSumLeafToLeaf(node -> right);
        
        int leftNodeToRoot = leftAns.second;
        int rightNodeToRoot = rightAns.second;
        
        int pathCrossingMe;
        if(node -> left != nullptr && node -> right != nullptr)
            pathCrossingMe = leftNodeToRoot + rightNodeToRoot + node -> data;
        else
            pathCrossingMe = node -> left == nullptr ? rightAns.first : leftAns.first;
            
        return { max(max(leftAns.first, rightAns.first), pathCrossingMe),  max(leftNodeToRoot, rightNodeToRoot) + node -> data };
    }
int maxPathSum(Node* root)
{ 
    // code here
    return maxSumLeafToLeaf(root).first;
}

//124 =========================================================================
//pair [maxPathSum, fromMeToAnyNodeMaxSumPath]
pair<int,int> maxPathSumHelper(TreeNode *node){
    if(node == nullptr)
        return {-1e9, -1e9};
    if(node -> left == nullptr && node -> right == nullptr)
        return {node -> val, node -> val};
    
    pair<int,int> leftAns = maxPathSumHelper(node -> left);
    pair<int,int> rightAns = maxPathSumHelper(node -> right);
    
    // max of left and right call
    int maxLR = max(leftAns.first, rightAns.first);
    //maxDistFromLeftNodeToAnyNode
    int leftToAnyNode = leftAns.second;
    int rightToAnyNode = rightAns.second;
    
    //max path which includes root, 3 case, left + root, right + root, left + root + right
    int maxIncRoot;
    
    if(node -> left != nullptr && node -> right != nullptr)
        maxIncRoot = max(max(leftToAnyNode, rightToAnyNode) + node -> val, leftToAnyNode + rightToAnyNode + node -> val);
    else
        maxIncRoot = node -> left == nullptr ? node -> val + rightToAnyNode : leftToAnyNode + node -> val;
    
    return { max(max(maxLR, maxIncRoot), node -> val) , max( max(leftToAnyNode, rightToAnyNode) + node -> val , node -> val) }; 
}
int maxPathSum(TreeNode* root) {
    return maxPathSumHelper(root).first;
}

//98 =======================================================================================
// pair = {isBstOrNot, {min of tree, max of tree}}

pair<bool, pair<long, long>> checkBST(TreeNode* node){
    if(node == nullptr)
        return {true, {1e13, -1e13}};
    
    pair<bool, pair<long, long>> left = checkBST(node -> left);
    pair<bool, pair<long, long>> right = checkBST(node -> right);

    pair<bool, pair<int, int>> ans;
    ans.first = false;
    if(left.first && right.first && node -> val > left.second.second && node -> val < right.second.first)
        ans.first = true;
    
    long data = node -> val;
    ans.second.first = min(left.second.first, data);
    ans.second.second = max(right.second.second, data);
    
    return ans;
}
bool isValidBST(TreeNode* root) {
    return checkBST(root).first;
}

//99 =====================================================================
TreeNode *prev = nullptr, *a = nullptr, *b = nullptr;
bool findFaulty(TreeNode *node){
    if(node == nullptr)
        return true;
    if(!findFaulty(node -> left))
        return false;
    
    if(prev != nullptr && prev -> val > node -> val){
        b = node;
        //first mistake found
        if(a == nullptr)
            a = prev;
        //second mistake found, a and b are at correct position
        //therefore return false and reach to root quickly by not traversing nodes ahead
        else
            return false;
    }
    //updating prev
    prev = node;
    
    if(!findFaulty(node -> right))
        return false;
    
    return true;
}
void recoverTree(TreeNode* root) {
    findFaulty(root);
    swap(a -> val, b -> val);
}



