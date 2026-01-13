#include "DoublyList.h"
#include <iostream>
#include <fstream>

using namespace std;

void LADD_HEAD(DoublyList& list, const string& value) {
    LNode* newNode = new LNode(value, list.head, nullptr);
    
    if (!list.head) {
        list.head = list.tail = newNode;
    } else {
        newNode->next = list.head;
        list.head->prev = newNode;
        list.head = newNode;
    }
    list.size++;
}

void LADD_TAIL(DoublyList& list, const string& value) {
    LNode* newNode = new LNode(value, nullptr, list.tail);
    
    if (!list.head) {
        list.head = list.tail = newNode;
    } else {
        newNode->prev = list.tail;
        list.tail->next = newNode;
        list.tail = newNode;
    }
    list.size++;
}

void LADD_BEFORE(DoublyList& list, const string& value, const string& target) {
    if (!list.head) {
        cout << "Список пуст!\n";
        return;
    }
    
    LNode* curr = list.head;
    while (curr && curr->data != target) {
        curr = curr->next;
    }
    
    if (!curr) {
        cout << "Элемент " << target << " не найден!\n";
        return;
    }
    
    LNode* newNode = new LNode(value, curr, curr->prev);
    
    if (curr == list.head) {
        newNode->next = list.head;
        list.head->prev = newNode;
        list.head = newNode;
    } else {
        newNode->prev = curr->prev;
        newNode->next = curr;
        curr->prev->next = newNode;
        curr->prev = newNode;
    }
    list.size++;
}

void LADD_AFTER(DoublyList& list, const string& value, const string& target) {
    if (!list.head) {
        cout << "Список пуст!\n";
        return;
    }
    
    LNode* curr = list.head;
    while (curr && curr->data != target) {
        curr = curr->next;
    }
    
    if (!curr) {
        cout << "Элемент " << target << " не найден!\n";
        return;
    }
    
    LNode* newNode = new LNode(value, curr->next, curr);
    
    if (curr == list.tail) {
        newNode->prev = list.tail;
        list.tail->next = newNode;
        list.tail = newNode;
    } else {
        newNode->prev = curr;
        newNode->next = curr->next;
        curr->next->prev = newNode;
        curr->next = newNode;
    }
    list.size++;
}

void LREMOVE_HEAD(DoublyList& list) {
    if (!list.head) {
        cout << "Список пуст!\n";
        return;
    }
    
    LNode* temp = list.head;
    if (list.head == list.tail) {
        list.head = list.tail = nullptr;
    } else {
        list.head = list.head->next;
        list.head->prev = nullptr;
    }
    
    delete temp;
    list.size--;
}

void LREMOVE_TAIL(DoublyList& list) {
    if (!list.head) {
        cout << "Список пуст!\n";
        return;
    }
    
    LNode* temp = list.tail;
    if (list.head == list.tail) {
        list.head = list.tail = nullptr;
    } else {
        list.tail = list.tail->prev;
        list.tail->next = nullptr;
    }
    
    delete temp;
    list.size--;
}

void LREMOVE_BEFORE(DoublyList& list, const string& target) {
    if (!list.head || !list.head->next) {
        cout << "Недостаточно элементов!\n";
        return;
    }
    
    LNode* curr = list.head;
    while (curr && curr->data != target) {
        curr = curr->next;
    }
    
    if (!curr) {
        cout << "Элемент " << target << " не найден!\n";
        return;
    }
    
    if (!curr->prev) {
        cout << "Нет элемента до " << target << "!\n";
        return;
    }
    
    LNode* toRemove = curr->prev;
    
    if (toRemove == list.head) {
        list.head = curr;
        list.head->prev = nullptr;
    } else {
        toRemove->prev->next = curr;
        curr->prev = toRemove->prev;
    }

    delete toRemove;
    list.size--;
}

void LREMOVE_AFTER(DoublyList& list, const string& target) {
    if (!list.head || !list.head->next) {
        cout << "Недостаточно элементов!\n";
        return;
    }
    
    LNode* curr = list.head;
    while (curr && curr->data != target) {
        curr = curr->next;
    }
    
    if (!curr) {
        cout << "Элемент " << target << " не найден!\n";
        return;
    }
    
    if (!curr->next) {
        cout << "Нет элемента после " << target << "!\n";
        return;
    }
    
    LNode* toRemove = curr->next;
    
    if (toRemove == list.tail) {
        list.tail = curr;
        list.tail->next = nullptr;
    } else {
        curr->next = toRemove->next;
        toRemove->next->prev = curr;
    }
    
    delete toRemove;
    list.size--;
}

bool LREMOVE_BY_VALUE(DoublyList& list, const string& value) {
    LNode* curr = list.head;
    while (curr) {
        if (curr->data == value) {
            if (curr == list.head) {
                list.head = curr->next;
                if (list.head) list.head->prev = nullptr;
            } else if (curr == list.tail) {
                list.tail = curr->prev;
                if (list.tail) list.tail->next = nullptr;
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }
            
            delete curr;
            list.size--;
            return true;
        }
        curr = curr->next;
    }
    
    cout << "Элемент " << value << " не найден!\n";
    return false;
}

bool LFIND(const DoublyList& list, const string& value) {
    LNode* curr = list.head;
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

void LPRINT_FORWARD(const DoublyList& list) {
    if (!list.head) { 
        cout << "Список пуст!\n"; 
        return; 
    }
    cout << "Двусвязный вперед (" << list.size << "): ";
    LNode* curr = list.head;
    while (curr) {
        cout << curr->data;
        if (curr->next) cout << " <-> ";
        curr = curr->next;
    }
    cout << endl;
}

void LPRINT_BACKWARD(const DoublyList& list) {
    if (!list.head) { 
        cout << "Список пуст!\n"; 
        return; 
    }
    cout << "Двусвязный назад (" << list.size << "): ";
    LNode* curr = list.tail;
    while (curr) {
        cout << curr->data;
        if (curr->prev) cout << " <-> ";
        curr = curr->prev;
    }
    cout << endl;
}

void LPRINT(const DoublyList& list) {
    LPRINT_FORWARD(list);
}

void LCLEAR(DoublyList& list) {
    while (list.head) {
        LNode* temp = list.head;
        list.head = list.head->next;
        delete temp;
    }
    list.tail = nullptr;
    list.size = 0;
    cout << "Список очищен" << endl;
}
