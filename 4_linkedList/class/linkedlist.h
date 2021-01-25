#include<iostream>
using namespace std;

class linkedlist{
    private:
        class Node{
            //we need to make things public, otherwise linkedlist class wont be able to access any of the members
            public:
                int data = 0;
                Node *next = nullptr;

                Node(int data){
                    this -> data = data;
                }
        };

        Node *head = nullptr;
        Node *tail = nullptr;
        int NumberOfNodes = 0;

    protected:
        void handleZeroSize(Node *node){
            this -> head = node;
            this -> tail = node;
        }

        void addFirstNode(Node *node){
            if(size() == 0)
                handleZeroSize(node);
            else{
                node -> next = this -> head;
                this -> head = node;
            }
            this -> NumberOfNodes++;
        }

        void addLastNode(Node *node){
            if(size() == 0)
                handleZeroSize(node);
            else{
                this -> tail -> next = node;
                this -> tail = node;
            }
            this -> NumberOfNodes++;
        }

        void addNodeAt(Node *node, int idx){
            if(idx == 0)
                addFirstNode(node);
            else if(idx == size())
                addLastNode(node);
            else{
                Node *nodeAt = getNodeAt(idx - 1);
                Node *forw = nodeAt -> next;

                nodeAt -> next = node;
                node -> next = forw;
                this -> NumberOfNodes++;
            }
        }

        Node* getNodeAt(int idx){
            Node *temp = this -> head;
            while(idx--){
                temp = temp -> next;
            }
            return temp;
        }

        void handleSize1(){
            this -> head = nullptr;
            this -> tail = nullptr;
        }

        Node* removeFirstNode(){
            Node *temp = this -> head;
            if(size() == 1)
                handleSize1();
            else
                this -> head = this -> head -> next;

            temp -> next = nullptr;
            this -> NumberOfNodes--;
            return temp;
        }

        Node* removeLastNode(){
            Node *temp = tail;
            if(size() == 1)
                handleSize1();
            else{
                Node *secondLastNode = getNodeAt(size() - 2);
                secondLastNode -> next = nullptr;
                this -> tail = secondLastNode;
            }
            this -> NumberOfNodes--;
            return temp;
        }

        Node* removeNodeAt(int idx){ 
            if(idx == 0)
                return removeFirstNode();
            else if(idx == size() - 1)
                return removeLastNode();
            else{
                Node *prev = getNodeAt(idx - 1);
                Node *curr = prev -> next;
                Node *nextNode = curr -> next;
                prev -> next = nextNode;
                curr -> next = nullptr;
                this -> NumberOfNodes--;
                return curr;
            }
        }

    public:
        int size(){
            return this -> NumberOfNodes;
        }

        bool isEmpty(){
            return size() == 0;
        }

        void addFirst(int data){
            Node *node = new Node(data);
            addFirstNode(node);
        }

        void addLast(int data){
            Node *node = new Node(data);
            addLastNode(node);
        }

        void addAt(int data, int idx){
            if(idx < 0 || idx > size()){
                cout << "Invalid Index" << endl;
                throw -1;
            }
            
            Node *node = new Node(data);
            addNodeAt(node, idx);
        }

        int getAt(int idx){
            if(size() == 0){
                cout << "LinkedList is Empty" << endl;
                throw -1;
            }
                
            else if(idx < 0 || idx >= size()){
                cout << "Invalid Index" << endl;
                throw -1;
            }
            
            Node *node = getNodeAt(idx);
            return node -> data;
        }

        int removeFirst(){
            if(size() == 0){
                cout << "LinkedList is Empty" << endl;
                throw -1;
            }
                
            Node *node = removeFirstNode();
            int data = node -> data;
            delete node;
            return data;
        }

        int removeLast(){
            if(size() == 0){
                cout << "LinkedList is Empty" << endl;
                throw -1;
            }
                
            Node *node = removeLastNode();
            int data = node -> data;
            delete node;
            return data;
        }

        int removeAt(int idx){
            if(size() == 0){
                cout << "LinkedList is Empty" << endl;
                throw -1;
            }
            else if(idx < 0 || idx >= size()){
                cout << "Invalid Index" << endl;
                throw -1;
            }
        
            Node *node = removeNodeAt(idx);
            int data = node -> data;
            delete node;
            return data;
        }

        int getFirst(){
            if(size() == 0){
                cout << "LinkedList is Empty" << endl;
                throw -1;
            }
            return this -> head -> data;
        }

        int getLast(){
            if(size() == 0){
                cout << "LinkedList is Empty" << endl;
                throw -1;
            }
            return this -> tail -> data;
        }

        void print(){
            if(size() == 0){
                cout << "LinkedList is Empty" << endl;
                throw -1;
            }
            Node *temp = this -> head;
            while(temp != nullptr){
                cout << temp -> data << " -> ";
                temp = temp -> next;
                if(temp == nullptr)
                    cout << "nullptr";
            }
            cout << endl;
        }

};