//Bread-First-Search
//level order type questions

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

  //level order prints =======================================================================
  //1: simple
void levelOrder1(TreeNode* node){
    queue<TreeNode*> q;
    q.push(node);
    
    while(!q.empty()){
        TreeNode* rn = q.front();  //rn : removed node
        cout << rn -> val << " ";
        q.pop();
        
        if(rn -> left != nullptr) q.push(rn -> left);
        if(rn -> right != nullptr) q.push(rn -> right);
    }
    cout << endl;
}

//2: using 2 queues, orignal queue and child queue
void levelOrder2(TreeNode* node){
    queue<TreeNode*> q, cq;
    q.push(node);
    int level = 0;
    cout << "Level " << level << ": ";
    
    while(!q.empty()){
        TreeNode *rn = q.front();
        cout << rn -> val << " ";
        q.pop();
        
        if(rn -> left != nullptr) cq.push(rn -> left);
        if(rn -> right != nullptr) cq.push(rn -> right);
        
        if(q.empty()){
            if(!cq.empty())
                cout << "\nLevel " << ++level << ": ";
            swap(q, cq);
        }
    }
}

//3: using delimiter
void levelOrder3(TreeNode* node){
    queue<TreeNode*> q;
    q.push(node);
    q.push(nullptr);
    
    int level = 0;
    cout << "Level " << level << ": ";
    
    while(q.size() != 1){
        TreeNode *rn = q.front();
        cout << rn -> val << " ";
        q.pop();
        
        if(rn -> left != nullptr) q.push(rn -> left);
        if(rn -> right != nullptr) q.push(rn -> right);
        
        if(q.front() == nullptr && q.size() != 1){
            cout << "\nLevel " << ++level << ": ";
            q.pop();
            q.push(nullptr);
        }  
    }
}

//4: 
void levelOrder4(TreeNode* node){
    queue<TreeNode*> q;
    q.push(node);
    
    int level = 0;
    cout << "Level " << level << ": ";
    
    while(!q.empty()){
        int size_ = q.size();
        
        while(size_--){
            TreeNode *rn = q.front();
            cout << rn -> val << " ";
            q.pop();
            
            if(rn -> left != nullptr) q.push(rn -> left);
            if(rn -> right != nullptr) q.push(rn -> right);
        }
        if(!q.empty())
            cout << "\nLevel " << ++level << ": "; 
    }
}


