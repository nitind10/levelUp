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

