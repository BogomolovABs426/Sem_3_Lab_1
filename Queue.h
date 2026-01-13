#ifndef QUEUE_H
#define QUEUE_H

#include <string>

using namespace std;

struct QNode {
    string data;
    QNode* next;
    
    QNode(const string& val, QNode* nxt = nullptr) : data(val), next(nxt) {}
};

struct Queue { 
    QNode* front = nullptr; 
    QNode* rear = nullptr; 
    size_t size = 0; 
    string filename; 
};

void QPUSH(Queue& queue, const string& value);
void QPOP(Queue& queue);
void QPRINT(const Queue& queue);
void QCLEAR(Queue& queue);

#endif
