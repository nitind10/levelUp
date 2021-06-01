//stack using our own linked list

public class stack {
    private class ListNode {
        int data = 0;
        ListNode next = null;

        public ListNode(int data) {
            this.data = data;
        }
    }

    private ListNode head = null;
    private ListNode tail = null;
    private int NoOfElements = 0;

    private void addFirst(ListNode node) {
        if (this.head == null) {
            this.head = node;
            this.tail = node;
        } else {
            node.next = this.head;
            this.head = node;
        }
    }

    private ListNode removeFirst() {
        ListNode rn = this.head;
        if (this.head == this.tail) {
            this.head = null;
            this.tail = null;
        } else {
            this.head = rn.next;
        }

        rn.next = null;

        return rn;
    }

    public int size() {
        return this.NoOfElements;
    }

    public boolean isEmpty() {
        return this.NoOfElements == 0;
    }

    protected void StackEmptyException() throws Exception {
        if (this.NoOfElements == 0)
            throw new Exception("StackISEmpty");
    }

    public void push(int data) {
        ListNode node = new ListNode(data);
        addFirst(node);
        this.NoOfElements++;
    }

    protected int top_() {
        return this.head.data;
    }

    public int top() throws Exception{
        StackEmptyException();
        return top_();
    }

    protected int pop_(){
       ListNode node = removeFirst();
       this.NoOfElements--;
       return node.data;
    }

    public int pop() throws Exception{
        StackEmptyException();
        return pop_();
    }

}
