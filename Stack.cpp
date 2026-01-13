#include "Stack.h"
#include <iostream>
#include <fstream>

using namespace std;

void SPUSH(Stack& stack, const string& value) {
    SNode* newNode = new SNode(value, stack.top);
    stack.top = newNode;
    stack.size++;
}

void SPOP(Stack& stack) {
    if (!stack.top) { 
        cout << "Стек пуст!\n"; 
        return; 
    }
    SNode* temp = stack.top;
    stack.top = stack.top->next;
    delete temp;
    stack.size--;
}

void SPRINT(const Stack& stack) {
    if (!stack.top) { 
        cout << "Стек пуст!\n"; 
        return;
    }
    cout << "Стек (" << stack.size << "): ";
    SNode* curr = stack.top;
    while (curr) {
        cout << curr->data;
        if (curr->next) cout << " -> ";
        curr = curr->next;
    }
    cout << endl;
}

void SCLEAR(Stack& stack) {
    while (stack.top) {
        SNode* temp = stack.top;
        stack.top = stack.top->next;
        delete temp;
    }
    stack.size = 0;
    cout << "Стек очищен" << endl;
}
