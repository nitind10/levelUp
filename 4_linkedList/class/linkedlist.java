public class linkedlist{

    //we dont want user to acces our Node class directly therefore it is private
    private class Node{
        private int data = 0;
        private Node next = null;

        Node(int data){
            this.data = data;
        }
    }

    //if head is not secured, anyone can acces it and point it to null, which will make us lose our linkedlist
    private Node head = null;
    private Node tail = null;
    private int NumberOfNodes = 0;

    public int size(){
        return this.NumberOfNodes;
    }

    public boolean isEmpty(){
        return size() == 0;
    }

    // ======================================

    protected void handleZeroSize(Node node){
        this.head = node;
        this.tail = node;
    }

    //capable of accepting a node and adding that to the linkedlist
    protected void addFirstNode(Node node){
        if(size() == 0)
            handleZeroSize(node);
        else{
            node.next = this.head;
            this.head = node;
        }
        this.NumberOfNodes++;
    }

    //capable of accepting int variable and add a node with that value
    public void addFirst(int data){
        Node node = new Node(data);
        addFirstNode(node);
    }

    // =========================================
    
    protected void addLastNode(Node node){
        if(size() == 0)
            handleZeroSize(node);
        else{
            this.tail.next = node;
            this.tail = node;
        }
        this.NumberOfNodes++;
    }

    public void addLast(int data){
        Node node = new Node(data);
        addLastNode(node);
    }

    // ============================

    protected void addNodeAt(Node node, int idx){
        if(idx == 0)
            addFirstNode(node);
        else if(idx == size())
            addLastNode(node);
        else{
            Node nodeAt = getNodeAt(idx - 1);
            Node forw = nodeAt.next;

            nodeAt.next = node;
            node.next = forw;
            this.NumberOfNodes++;
        }
    }

    public void addAt(int data, int idx) throws Exception{
        if(idx < 0 || idx > size()){
            //function will terminate after throwing this exception
            throw new Exception("Invalid Index");
        }
        
        Node node = new Node(data);
        addNodeAt(node, idx);
    }

    // ==============================

    protected Node getNodeAt(int idx){
        Node temp = this.head;
        while(idx-- > 0){
            temp = temp.next;
        }
        return temp;
    }

    public int getAt(int idx) throws Exception{
        if(size() == 0)
            throw new Exception("LinkedList is Empty");
        else if(idx < 0 || idx >= size())
            throw new Exception("Invalid Index");
        
        Node node = getNodeAt(idx);
        return node.data;
    }

    // ===================================

    protected void handleSize1(){
        this.head = null;
        this.tail = null;
    }

    protected Node removeFirstNode(){
        Node temp = head;
        if(size() == 1)
            handleSize1();
        else
            this.head = this.head.next;

        temp.next = null;
        this.NumberOfNodes--;
        return temp;
    }

    public int removeFirst() throws Exception{
        if(size() == 0)
            throw new Exception("LinkedList is Empty");
        
        Node node = removeFirstNode();
        return node.data;
    }

    // ==============================

    protected Node removeLastNode(){
        Node temp = tail;
        if(size() == 1)
            handleSize1();
        else{
            Node secondLastNode = getNodeAt(size() - 2);
            secondLastNode.next = null;
            this.tail = secondLastNode;
        }
        this.NumberOfNodes--;
        return temp;
    }

    public int removeLast() throws Exception{
        if(size() == 0)
            throw new Exception("LinkedList is Empty");
        Node node = removeLastNode();
        return node.data;
    }

    // =================================

    protected Node removeNodeAt(int idx){ 
        if(idx == 0)
            return removeFirstNode();
        else if(idx == size() - 1)
            return removeLastNode();
        else{
            Node prev = getNodeAt(idx - 1);
            Node curr = prev.next;
            Node nextNode = curr.next;
            prev.next = nextNode;
            curr.next = null;
            this.NumberOfNodes--;
            return curr;
        }
    }

    public int removeAt(int idx) throws Exception{
        if(size() == 0)
            throw new Exception("LinkedList is Empty");
        else if(idx < 0 || idx >= size())
            throw new Exception("Invalid Index");
        
        Node node = removeNodeAt(idx);
        return node.data;
    }

    // ====================

    public int getFirst() throws Exception{
        if(size() == 0)
            throw new Exception("LinkedList is Empty");
        
        return this.head.data;
    }

    public int getLast() throws Exception{
        if(size() == 0)
            throw new Exception("LinkedList is Empty");

        return this.tail.data;
    }

    //function for getAt() is @ 104 line
}