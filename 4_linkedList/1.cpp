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
