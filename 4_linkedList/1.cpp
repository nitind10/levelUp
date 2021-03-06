struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 };


//876
ListNode* middleNode(ListNode* head) {
    if(head == nullptr || head -> next == nullptr)
        return head;
    
    ListNode *slow = head, *fast = head;
    
    while(fast != nullptr && fast -> next != nullptr){
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    
    return slow;
}

//206
//iterative
ListNode* reverseList(ListNode* head) {
    if(head == nullptr || head -> next == nullptr)
        return head;
    ListNode *prev = nullptr, *curr = head, *forw = head;
    while(curr != nullptr){
        forw = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = forw;
    }
    //prev becomes the new head
    return prev;
}
//recursive
ListNode* reverseRec(ListNode* head){
    if(head -> next == nullptr){
        return head;
    }
    ListNode *nextNode = head -> next;
    head -> next = nullptr;
    ListNode *returnedHead = reverseRec(nextNode);
    nextNode -> next = head;
    return returnedHead;
}
ListNode* reverseList(ListNode* head) {
    if(head == nullptr || head -> next == nullptr)
        return head;
    
    return reverseRec(head);
}

//234
ListNode* reverseList(ListNode* head){
    ListNode *prev = nullptr, *curr = head, *forw = head;
    while(curr != nullptr){
        forw = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = forw;
    }
    return prev;
}
ListNode* middle(ListNode* head){
    ListNode *slow = head, *fast = head;
    while(fast -> next != nullptr && fast -> next -> next != nullptr){
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    return slow;
}
bool isPalindrome(ListNode* head) {
    if(head == nullptr || head -> next == nullptr)
            return true;
    
    ListNode *mid = middle(head);
    ListNode *head2 = mid -> next;
    mid -> next = nullptr;
    
    head2 = reverseList(head2);
    
    ListNode *temp1 = head, *temp2 = head2;
    bool res = true;

    while(temp1 != nullptr && temp2 != nullptr){
        if(temp1 -> val != temp2 -> val){
            res = false;
            break;
        }
        temp1 = temp1 -> next;
        temp2 = temp2 -> next;
    }
    mid -> next = reverseList(head2);
    return res;
}

//143
ListNode * middle(ListNode* head){
        ListNode *slow = head, *fast = head;
        while(fast -> next != nullptr && fast -> next -> next != nullptr){
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        return slow;
    }
    ListNode* reverse(ListNode* head){
        ListNode *prev = nullptr, *curr = head, *forw = head;
        while(curr != nullptr){
            forw = curr -> next;
            curr -> next = prev;
            prev = curr;
            curr = forw;
        }
        return prev;
    }
    void reorderList(ListNode* head) {
        if(head == nullptr || head -> next == nullptr)
            return;
        
        ListNode *mid = middle(head);
        ListNode *head2 = mid -> next;
        mid -> next = nullptr;
        
        head2 = reverse(head2);
        
        ListNode *curr1 = head, *curr2 = head2, *forw1 = curr1, *forw2 = curr2;
        while(curr1 != nullptr && curr2 != nullptr){
            forw1 = forw1 -> next;
            forw2 = forw2 -> next;
            curr1 -> next = curr2;
            curr2 -> next = forw1;
            curr1 = forw1;
            curr2 = forw2;
        }
    }

//recovering orignal list from reordered list
void linkedlist :: reorderToOrignal(){
    if(this -> head == nullptr || this -> head -> next == nullptr)
        return;

    Node *c1 = this -> head, *c2 = this -> head -> next, *head2 = c2;

    //makes 1 6 2 5 3 4 to two diff lists 1 2 3, 6 5 4
    while(c1 != nullptr && c2 != nullptr){
        c1 -> next = c2 -> next;
        c1 = c1 -> next;

        if(c1 != nullptr)
            c2 -> next = c1 -> next;
        c2 = c2 -> next;
    }

    //makes list2 i.e 6 5 4 to 4 5 6
    head2 = reverse(head2);  

    //joins the two lists and updates the tail
    c1 = this -> head;
    while(c1 -> next != nullptr){
        c1 = c1 -> next;
    }
    c1 -> next = head2; 
    while(c1 -> next != nullptr){
        c1 = c1 -> next;
    }
    this -> tail = c1;
} 

//21
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(l1 == nullptr || l2 == nullptr)
        return l1 == nullptr ? l2 : l1;
    
    ListNode *dummy = new ListNode(-1);
    ListNode *prev = dummy, *c1 = l1, *c2 = l2;
    
    while(c1 != nullptr && c2 != nullptr){
        if(c1 -> val < c2 -> val){
            prev -> next = c1;
            c1 = c1 -> next;
        }else{
            prev -> next = c2;
            c2 = c2 -> next;
        }
        prev = prev -> next;   
    }
    
    prev -> next = c1 == nullptr ? c2 : c1;
    
    ListNode *head = dummy -> next;
    dummy -> next = nullptr;
    delete dummy;
    
    return head;
}

//148
ListNode* mergeTwoLists(ListNode *l1, ListNode *l2){
    ListNode *dummy = new ListNode(-1);
    ListNode *c1 = l1, *c2 = l2, *prev = dummy;
    
    while(c1 != nullptr && c2 != nullptr){
        if(c1 -> val < c2 -> val){
            prev -> next = c1;
            c1 = c1 -> next;
        }else{
            prev -> next = c2;
            c2 = c2 -> next;
        }
        prev = prev -> next;
    }
    prev -> next = c1 == nullptr ? c2 : c1;
    ListNode *head = dummy -> next;
    dummy -> next = nullptr;
    delete dummy;
    return head;
}
ListNode* middle(ListNode* head){
    ListNode *slow = head, *fast = head;
    while(fast -> next != nullptr && fast -> next -> next != nullptr){
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    return slow;
}
ListNode* mergeSort(ListNode *head){
    if(head -> next == nullptr)
        return head;
    
    ListNode *mid = middle(head);
    ListNode *nextToMid = mid -> next;
    mid -> next = nullptr;
    
    return mergeTwoLists(mergeSort(head), mergeSort(nextToMid));
}
ListNode* sortList(ListNode* head) {
    if(head == nullptr || head -> next == nullptr)
        return head;
    return mergeSort(head);
}

//23
ListNode* mergeTwoLists(ListNode *l1, ListNode *l2) {
    if(l1 == nullptr || l2 == nullptr)
        return l1 == nullptr ? l2 : l1;
    
    ListNode *dummy = new ListNode(-1);
    ListNode *prev = dummy, *c1 = l1, *c2 = l2;
    
    while(c1 != nullptr && c2 != nullptr){
        if(c1 -> val < c2 -> val){
            prev -> next = c1;
            c1 = c1 -> next;
        }else{
            prev -> next = c2;
            c2 = c2 -> next;
        }
        prev = prev -> next;   
    }
    
    prev -> next = c1 == nullptr ? c2 : c1;
    
    ListNode *head = dummy -> next;
    dummy -> next = nullptr;
    delete dummy;
    
    return head;
}
ListNode* recMerge(vector<ListNode*>& lists, int si, int ei){
    if(si == ei)
        return lists[si];
    
    int mid = (si + ei) / 2;
    ListNode *l1 = recMerge(lists, si, mid);
    ListNode *l2 = recMerge(lists, mid + 1, ei);
    
    ListNode *newHead = mergeTwoLists(l1, l2);
    return newHead;
}
ListNode* mergeKLists(vector<ListNode*>& lists) {
    int n = lists.size();
    
    if(n == 0)
        return nullptr;
    
    return recMerge(lists, 0, n-1);
}

//141
bool hasCycle(ListNode *head) {
    if(head == nullptr || head -> next == nullptr)
        return false;
    ListNode *slow = head, *fast = head;
    
    while(fast != nullptr && fast -> next != nullptr){
        fast = fast -> next -> next;
        slow = slow -> next;
        
        if(fast == slow)
            return true;
    }
    return false;
}

//142
ListNode *detectCycle(ListNode *head) {
    if(head == nullptr || head -> next == nullptr)
        return nullptr;
    ListNode *slow = head, *fast = head;
    while(fast != nullptr && fast -> next != nullptr){
        slow = slow -> next;
        fast = fast -> next -> next;
        
        if(fast == slow)
            break;
    }
    
    if(fast != slow)
        return nullptr;
    
    int count = 0, cycleLen, rotation = 0;
    ListNode *temp = fast;
    
    slow = head;
    while(fast != slow){
        fast = fast -> next;
        slow = slow -> next;
        count++;
        if(fast == temp){
            rotation++;
            cycleLen = count/rotation;
        }
    }
    cout << "In terms of edge length : \n";
    cout << "(a = " << count << ") (m - 1 = " << rotation << ") (b + c = " << cycleLen 
            << ") (c = " << count - cycleLen * rotation << ")";
    return slow;
}

//160
ListNode *detectCycle(ListNode *head) {
    //not possible here
    // if(head == nullptr || head -> next == nullptr)
    //     return nullptr;
    
    ListNode *slow = head, *fast = head;
    while(fast != nullptr && fast -> next != nullptr){
        slow = slow -> next;
        fast = fast -> next -> next;
        
        if(fast == slow)
            break;
    }
    
    if(fast != slow)
        return nullptr;
    
    slow = head;
    while(fast != slow){
        fast = fast -> next;
        slow = slow -> next;
    }
    return slow;
}
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if(headA == nullptr || headB == nullptr) return nullptr;
    
    ListNode *tail = headA;
    while(tail -> next != nullptr) 
        tail = tail -> next;
    
    tail -> next = headB;
    ListNode *ans = detectCycle(headA);
    tail -> next = nullptr;
    return ans;
}

//19
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode *c1 = head, *c2 = head;
    
    while(n--)
        c2 = c2 -> next;
    
    //removing sizeTH node from end i.e 1st from start
    if(c2 == nullptr){
        head = c1 -> next;
        c1 -> next = nullptr;
        delete c1;
        return head;
    }
    
    while(c2 -> next != nullptr){
        c2 = c2 -> next;
        c1 = c1 -> next;
    }
    
    ListNode *removed = c1 -> next;
    c1 -> next = removed -> next;
    removed -> next = nullptr;
    delete removed;
    
    return head;    
}

//25
// - my approach
ListNode *forward = nullptr;
int size(ListNode *head){
    int count = 0;
    while(head != nullptr){
        head = head -> next;
        count++;
    }
    return count;
}
ListNode* reverseK(ListNode *head, int k){
    ListNode *prev = nullptr, *curr = head;
    forward = head;
    while(k--){
        forward = forward -> next;
        curr -> next = prev;
        prev = curr;
        curr = forward;
    }
    return prev;
}
ListNode* reverseKGroup(ListNode* head, int k) {
    
    ListNode *currHead = head;
    ListNode *prevTail = nullptr;
    
    int n = size(head) / k;
    
    for(int i = 1; i <= n; ++i){
        ListNode *newHead = reverseK(currHead, k);
        if(i == 1) head = newHead;
        else prevTail -> next = newHead;
        prevTail = currHead;
        currHead = forward;
    }
    
    prevTail -> next = forward;
    
    return head;
}
//- sir's approach
ListNode *th = nullptr;
ListNode *tt = nullptr;

void addFirstNode(ListNode *node)
{
    if (th == nullptr)
    {
        th = node;
        tt = node;
    }
    else
    {
        node->next = th;
        th = node;
    }
}
int size(ListNode *head){
    int count = 0;
    while(head != nullptr){
        head = head -> next;
        count++;
    }
    return count;
}
ListNode *reverseKGroup(ListNode *head, int k)
{
    if (head == nullptr || head->next == nullptr || k == 1)
        return head;

    // original head, original tail
    ListNode *oh = nullptr;
    ListNode *ot = nullptr;

    int len = size(head);
    ListNode *curr = head;

    while (len >= k)
    {
        int tempK = k;
        while (tempK-- > 0)
        {
            ListNode *forw = curr->next;
            curr->next = nullptr;
            addFirstNode(curr);
            curr = forw;
        }

        if (oh == nullptr)
        {
            oh = th;
            ot = tt;
        }
        else
        {
            ot->next = th;
            ot = tt;
        }

        th = nullptr;
        tt = nullptr;
        len -= k;
    }

    ot->next = curr;
    return oh;
}

//92
//- my approach
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if(m == n)
        return head;
    
    int diff = n - m + 1;
    int mCopy = m;
    
    ListNode *curr = head, *prev = nullptr;
    
    while(mCopy-- > 1){
        prev = curr;
        curr = curr -> next;
    }
    
    ListNode *heldHead = prev, *revStart = curr, *forw = curr;
    
    while(diff--){
        forw = forw -> next;
        curr -> next = prev;
        prev = curr;
        curr = forw;
    }
    
    if(m != 1)
        heldHead -> next = prev;
    
    revStart -> next = forw;
    
    if(m == 1) head = prev;
    
    return head;
}
//- sir's approach
//making them global or creating in main then passing by refference to addFirstNode, same thing
ListNode *tempHead = nullptr, *tempTail = nullptr;

void addFirstNode(ListNode *node){
    if(tempHead == nullptr)
        tempHead = tempTail = node;
    else{
        node -> next = tempHead;
        tempHead = node;
    }
}

ListNode* reverseBetween(ListNode* head, int m, int n) {
    if(m == n)
        return head;
    int idx = 1;
    ListNode *curr = head, *prev = nullptr, *forw = nullptr;
    
    while(idx <= n){
        if(idx < m){
            prev = curr;
            curr = curr -> next;
        }else{
            forw = curr -> next;
            curr -> next = nullptr;
            addFirstNode(curr);
            curr = forw;
        }
        idx++;
    }
    tempTail -> next = forw;
    
    if(prev != nullptr) prev -> next = tempHead;
    else head = tempHead;
    
    return head;
}

//138
void addNodesInBetween(Node *head){
    Node *curr = head, *forw = head;
    while(curr != nullptr){
        forw = curr -> next;
        Node *node = new Node(curr -> val);
        curr -> next = node;
        node -> next = forw;
        curr = forw;
    }
}
void assignRandomPointers(Node *head){
    Node *curr = head;
    while(curr != nullptr){
        curr -> next -> random = (curr -> random != nullptr) ? curr -> random -> next : nullptr;
        curr = curr -> next -> next;
    }
}
Node* breakList(Node *head){
    Node *curr = head, *forw = head;
    Node *ans = head -> next;
    while(curr -> next != nullptr){
        forw = curr -> next;
        curr -> next = forw -> next;
        curr = forw;
    }
    return ans;
}
Node* copyRandomList(Node* head) {
    if(head == nullptr) return head;
    addNodesInBetween(head);
    assignRandomPointers(head);
    return breakList(head);
}

//https://practice.geeksforgeeks.org/problems/segregate-even-and-odd-nodes-in-a-linked-list/0#
class Node{
            public:
                int data = 0;
                Node *next = nullptr;

                Node(int data){
                    this -> data = data;
                }
        };
void print(Node *head){
    while(head != nullptr){
        cout << head -> data << " ";
        head = head -> next;
    }
    cout << endl;
}
int mainfn()
 {
	//code
	int t;
	cin >> t;
	while(t--){
	    int n;
	    cin >> n;
	    Node *head = nullptr, *tail = nullptr;
	    int val;
	    while(n--){
	        cin >> val;
	        Node *node = new Node(val);
	        if(head == nullptr){
	            head = node;
	            tail = head;
	        }else{
	            tail -> next = node;
	            tail = tail -> next;
	        }
	    }
	
	    Node *dummyOdd = new Node(-1);
	    Node *dummyEven = new Node(-2);
	    Node *currOdd = dummyOdd, *currEven = dummyEven;
	    Node *curr = head;
	    while(curr != nullptr){
	        if(curr -> data & 1){
	            currOdd -> next = curr;
	            currOdd = curr;
	        }else{
	            currEven -> next = curr;
	            currEven = curr;
	        }
	        curr = curr -> next;
	    }
	    currOdd -> next = nullptr;
	    currEven -> next = dummyOdd -> next;
	    
	    head = dummyEven -> next;
	    print(head);
	}
	return 0;
}