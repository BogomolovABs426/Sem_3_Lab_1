#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include <string>

using namespace std;

struct FNode {
    string data;
    FNode* next;
    
    FNode(const string& val, FNode* nxt = nullptr) : data(val), next(nxt) {}
};

struct SingleList { 
    FNode* head = nullptr; 
    size_t size = 0; 
    string filename; 
};

void FADD_HEAD(SingleList& list, const string& value);
void FADD_TAIL(SingleList& list, const string& value);
void FADD_BEFORE(SingleList& list, const string& value, const string& target);
void FADD_AFTER(SingleList& list, const string& value, const string& target);

void FREMOVE_HEAD(SingleList& list);
void FREMOVE_TAIL(SingleList& list);
void FREMOVE_BEFORE(SingleList& list, const string& target);
void FREMOVE_AFTER(SingleList& list, const string& target);

bool FREMOVE_BY_VALUE(SingleList& list, const string& value);
bool FFIND(const SingleList& list, const string& value);

void FPRINT_FORWARD(const SingleList& list);
void FPRINT_BACKWARD(const SingleList& list);
void FPRINT(const SingleList& list);

void FCLEAR(SingleList& list);

#endif
