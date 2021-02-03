import java.util.HashMap;

class LRUCache{

    private class Node{
        int key = 0;
        int value = 0;
        Node next = null;
        Node prev = null;

        Node(int key, int value){
            this.key = key;
            this.value = value;
        }
    }
    private Node head = null;
    private Node tail = null;
    private int maxCapacity = 0;
    private int currSize = 0;

    private HashMap<Integer, Node> map = new HashMap<>();

    public LRUCache(int capacity) {
        this.maxCapacity = capacity;
    }

    public void removeTailNode() {
        if (this.currSize == 1) {
            this.head = null;
            this.tail = null;
        } else {
            Node next = this.tail.next;

            this.tail.next = null;
            next.prev = null;

            this.tail = next;
        }
        this.currSize--;
    }

    public void removeNode(Node node) {
        if (this.currSize == 1) {
            this.head = null;
            this.tail = null;
        } else if (node == this.tail) {
            removeTailNode();
            return;
        } else {
            Node prev = node.prev;
            Node next = node.next;

            node.prev = null;
            node.next = null;

            prev.next = next;
            next.prev = prev;
        }

        this.currSize--;
    }

    public void addFirstNode(Node node) {
        if (head == null) {
            this.head = node;
            this.tail = node;
        } else {
            this.head.next = node;
            node.prev = this.head;
            this.head = node;
        }

        this.currSize++;
    }
    
     public void makeMostRecent(Node node) {
        if (node == this.head)
            return;
        removeNode(node);
        addFirstNode(node);
    }
    
    public int get(int key) {
        if (!map.containsKey(key))
            return -1;

        Node node = map.get(key);
        makeMostRecent(node);
        return node.value;
    }
    
    public void put(int key, int value) {
        //app already open
        if(map.containsKey(key)){
            Node node = map.get(key);
            node.value = value;
            //will make it most recent
            get(key);
        }

        //app hasnt been opened yet
        else {
            if (this.currSize == this.maxCapacity) {
                map.remove(tail.key);
                removeTailNode();
            }

            Node node = new Node(key, value);
            addFirstNode(node);
            map.put(key, node);
        }
    }

}
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */