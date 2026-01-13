#include "SinglyList.h"
#include <iostream>
#include <fstream>

using namespace std;

void FADD_HEAD(SingleList& list, const string& value) {
    FNode* newNode = new FNode(value, list.head);
    list.head = newNode;
    list.size++;
}

void FADD_TAIL(SingleList& list, const string& value) {
    FNode* newNode = new FNode(value, nullptr);
    
    if (!list.head) {
        list.head = newNode;
    } else {
        FNode* curr = list.head;
        while (curr->next) curr = curr->next;
        curr->next = newNode;
    }
    list.size++;
}

void FADD_BEFORE(SingleList& list, const string& value, const string& target) {
    if (!list.head) {
        cout << "Список пуст!\n";
        return;
    }
    
    if (list.head->data == target) {
        FADD_HEAD(list, value);
        return;
    }
    
    FNode* curr = list.head;
    while (curr->next && curr->next->data != target) {
        curr = curr->next;
    }
    
    if (!curr->next) {
        cout << "Элемент " << target << " не найден!\n";
        return;
    }
    
    FNode* newNode = new FNode(value, curr->next);
    curr->next = newNode;
    list.size++;
}

void FADD_AFTER(SingleList& list, const string& value, const string& target) {
    if (!list.head) {
        cout << "Список пуст!\n";
        return;
    }
    
    FNode* curr = list.head;
    while (curr && curr->data != target) {
        curr = curr->next;
    }
    
    if (!curr) {
        cout << "Элемент " << target << " не найден!\n";
        return;
    }
    
    FNode* newNode = new FNode(value, curr->next);
    curr->next = newNode;
    list.size++;
    cout << "-> вставлен " << value << " после " << target << endl;
}

void FREMOVE_HEAD(SingleList& list) {
    if (!list.head) {
        cout << "Список пуст!\n";
        return;
    }
    
    FNode* temp = list.head;
    list.head = list.head->next;
    delete temp;
    list.size--;
}

void FREMOVE_TAIL(SingleList& list) {
    if (!list.head) {
        cout << "Список пуст!\n";
        return;
    }
    
    if (!list.head->next) {
        delete list.head;
        list.head = nullptr;
    } else {
        FNode* curr = list.head;
        while (curr->next->next) curr = curr->next;
        delete curr->next;
        curr->next = nullptr;
    }
    list.size--;
}

void FREMOVE_BEFORE(SingleList& list, const string& target) {
    if (!list.head || !list.head->next) {
        cout << "Недостаточно элементов!\n";
        return;
    }
    
    if (list.head->next->data == target) {
        FREMOVE_HEAD(list);
        return;
    }
    
    FNode* curr = list.head;
    while (curr->next && curr->next->next && curr->next->next->data != target) {
        curr = curr->next;
    }
    
    if (!curr->next || !curr->next->next) {
        cout << "Элемент " << target << " не найден или нет элемента перед ним!\n";
        return;
    }
    
    FNode* temp = curr->next;
    curr->next = curr->next->next;
    delete temp;
    list.size--;
}

void FREMOVE_AFTER(SingleList& list, const string& target) {
    if (!list.head) {
        cout << "Список пуст!\n";
        return;
    }
    
    FNode* curr = list.head;
    while (curr && curr->data != target) {
        curr = curr->next;
    }
    
    if (!curr || !curr->next) {
        cout << "Элемент " << target << " не найден или нет элемента после него!\n";
        return;
    }
    
    FNode* temp = curr->next;
    curr->next = curr->next->next;
    delete temp;
    list.size--;
}

bool FREMOVE_BY_VALUE(SingleList& list, const string& value) {
    if (!list.head) return false;
    
    if (list.head->data == value) {
        FNode* temp = list.head;
        list.head = list.head->next;
        delete temp;
        list.size--;
        return true;
    }
    
    FNode* curr = list.head;
    while (curr->next && curr->next->data != value) {
        curr = curr->next;
    }
    
    if (curr->next) {
        FNode* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
        list.size--;
        return true;
    }
    
    cout << "Элемент " << value << " не найден!\n";
    return false;
}

bool FFIND(const SingleList& list, const string& value) {
    FNode* curr = list.head;
    int position = 0;
    while (curr) {
        if (curr->data == value) {
            cout << "Элемент " << value << " найден на позиции " << position << endl;
            return true;
        }
        curr = curr->next;
        position++;
    }
    cout << "Элемент " << value << " не найден!\n";
    return false;
}

void FPRINT_FORWARD(const SingleList& list) {
    if (!list.head) { 
        cout << "Список пуст!\n"; 
        return; 
    }
    cout << "Список вперед (" << list.size << "): ";
    FNode* curr = list.head;
    while (curr) {
        cout << curr->data;
        if (curr->next) cout << " -> ";
        curr = curr->next;
    }
    cout << endl;
}

void FPRINT_BACKWARD(const SingleList& list) {
    if (!list.head) { 
        cout << "Список пуст!\n"; 
        return; 
    }
    
    int count = 0;
    FNode* curr = list.head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    
    string* arr = new string[count];
    curr = list.head;
    for (int i = 0; i < count; i++) {
        arr[i] = curr->data;
        curr = curr->next;
    }
    
    cout << "Список назад (" << list.size << "): ";
    for (int i = count - 1; i >= 0; i--) {
        cout << arr[i];
        if (i > 0) cout << " <- ";
    }
    cout << endl;
    
    delete[] arr;
}

void FPRINT(const SingleList& list) {
    FPRINT_FORWARD(list);
}

void FCLEAR(SingleList& list) {
    while (list.head) {
        FNode* temp = list.head;
        list.head = list.head->next;
        delete temp;
    }
    list.size = 0;
    cout << "Список очищен" << endl;
}
