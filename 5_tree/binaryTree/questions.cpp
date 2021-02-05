//leetcode problems

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


