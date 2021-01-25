#include<iostream>
#include "linkedlist.h"

using namespace std;

int main(){
    //on the stack
    //linkedlist ll;

    //on heap
    linkedlist *l = new linkedlist();
    l->addLast(4);
    l->removeFirst();
    l->removeLast();
    l->addFirst(5);
    l->print();
    cout << l->getAt(1) << endl;
    cout << l->getLast() << endl;
    cout << l->size() << endl;
    return 0;
}