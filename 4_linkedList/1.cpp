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
