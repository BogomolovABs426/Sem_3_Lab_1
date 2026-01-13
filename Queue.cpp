#include "Queue.h"
#include <iostream>
#include <fstream>

using namespace std;

void QPUSH(Queue& queue, const string& value) {
    QNode* newNode = new QNode(value, nullptr);
    if (!queue.rear) {
        queue.front = queue.rear = newNode;
    } else {
        queue.rear->next = newNode;
        queue.rear = newNode;
    }
    queue.size++;    
}

void QPOP(Queue& queue) {
    if (!queue.front) { 
        cout << "Очередь пуста!\n"; 
        return; 
    }
    QNode* temp = queue.front;
    queue.front = queue.front->next;
    if (!queue.front) queue.rear = nullptr;
    delete temp;
    queue.size--;
}

void QPRINT(const Queue& queue) {
    if (!queue.front) { 
        cout << "Очередь пуста!\n"; 
        return; 
    }
    cout << "Очередь (" << queue.size << "): ";
    QNode* curr = queue.front;
    while (curr) {
        cout << curr->data;
        if (curr->next) cout << " -> ";
        curr = curr->next;
    }
    cout << endl;
}

void QCLEAR(Queue& queue) {
    while (queue.front) {
        QNode* temp = queue.front;
        queue.front = queue.front->next;
        delete temp;
    }
    queue.rear = nullptr;
    queue.size = 0;
    cout << "Очередь очищена" << endl;
}
