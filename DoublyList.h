#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <string>

using namespace std;

struct LNode {
    string data;
    LNode* next;
    LNode* prev;
    
    LNode(const string& val, LNode* nxt = nullptr, LNode* prv = nullptr) : data(val), next(nxt), prev(prv) {}
};

struct DoublyList { 
    LNode* head = nullptr; 
    LNode* tail = nullptr; 
    size_t size = 0; 
    string filename; 
};

void LADD_HEAD(DoublyList& list, const string& value);
void LADD_TAIL(DoublyList& list, const string& value);
void LADD_BEFORE(DoublyList& list, const string& value, const string& target);
void LADD_AFTER(DoublyList& list, const string& value, const string& target);

void LREMOVE_HEAD(DoublyList& list);
void LREMOVE_TAIL(DoublyList& list);
void LREMOVE_BEFORE(DoublyList& list, const string& target);
void LREMOVE_AFTER(DoublyList& list, const string& target);

bool LREMOVE_BY_VALUE(DoublyList& list, const string& value);
bool LFIND(const DoublyList& list, const string& value);

void LPRINT_FORWARD(const DoublyList& list);
void LPRINT_BACKWARD(const DoublyList& list);
void LPRINT(const DoublyList& list);

void LCLEAR(DoublyList& list);

#endif
