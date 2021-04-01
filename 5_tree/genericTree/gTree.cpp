#include<iostream>
#include<vector>
using namespace std;

class Node{
    public:
        int val = 0;
        vector<Node*> childs;

        Node(int val){
            this -> val = val;
        }
};
