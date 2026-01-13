#include "Tree.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

void ClearTree(TNode* node) {
    if (!node) return;
    ClearTree(node->left);
    ClearTree(node->right);
    delete node;
}

void TADD(Tree& tree, const string& value, bool silent) {
    TNode* newNode = new TNode(value, nullptr, nullptr, nullptr);
    
    if (!tree.root) {
        tree.root = newNode;
    } else {
        queue<TNode*> q;
        q.push(tree.root);
        TNode* parent = nullptr;
        
        while (!q.empty()) {
            parent = q.front();
            q.pop();
            
            if (!parent->left) {
                parent->left = newNode;
                newNode->parent = parent;
                break;
            } else if (!parent->right) {
                parent->right = newNode;
                newNode->parent = parent;
                break;
            } else {
                q.push(parent->left);
                q.push(parent->right);
            }
        }
    }
    
    tree.size++;
    if (!silent) {
        cout << "Добавлен в дерево: " << value << endl;
    }
}

bool TFIND(const Tree& tree, const string& value) {
    if (!tree.root) {
        cout << "Дерево пусто!\n";
        return false;
    }
    
    queue<TNode*> q;
    q.push(tree.root);
    
    while (!q.empty()) {
        TNode* current = q.front();
        q.pop();
        
        if (current->data == value) {
            cout << "Элемент '" << value << "' найден в дереве" << endl;
            return true;
        }
        
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    
    cout << "Элемент '" << value << "' не найден в дереве" << endl;
    return false;
}

bool TISFULL(const Tree& tree) {
    if (!tree.root) return true;
    
    queue<TNode*> q;
    q.push(tree.root);
    bool foundNonFullNode = false;
    
    while (!q.empty()) {
        TNode* current = q.front();
        q.pop();
        
        bool hasZeroChildren = (!current->left && !current->right);
        bool hasTwoChildren = (current->left && current->right);
        
        if (!hasZeroChildren && !hasTwoChildren) {
            return false;
        }
        
        if (foundNonFullNode && !hasZeroChildren) {
            return false;
        }
        
        if (hasZeroChildren) {
            foundNonFullNode = true;
        }
        
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    
    return true;
}

void TLEVELORDER(const Tree& tree) {
    if (!tree.root) {
        cout << "Дерево пусто!\n";
        return;
    }
    
    cout << "Level-order: ";
    queue<TNode*> q;
    q.push(tree.root);
    
    while (!q.empty()) {
        TNode* current = q.front();
        q.pop();
        cout << current->data << " ";
        
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    cout << endl;
}

void TPRINT_STRUCTURE(const Tree& tree) {
    if (!tree.root) {
        cout << "Дерево пусто!\n";
        return;
    }
    
    cout << "Структура дерева:\n";
    queue<TNode*> q;
    q.push(tree.root);
    int level = 0;
    int nodesInLevel = 1;
    
    while (!q.empty()) {
        int nextLevelCount = 0;
        cout << "Уровень " << level << ": ";
        
        for (int i = 0; i < nodesInLevel; i++) {
            if (q.empty()) break;
            
            TNode* current = q.front();
            q.pop();
            
            if (current) {
                cout << current->data << " ";
                q.push(current->left);
                q.push(current->right);
                nextLevelCount += 2;
            } else {
                cout << "NULL ";
                q.push(nullptr);
                q.push(nullptr);
                nextLevelCount += 2;
            }
        }
        
        cout << endl;
        level++;
        nodesInLevel = nextLevelCount;
        
        bool hasNonNull = false;
        queue<TNode*> temp = q;
        while (!temp.empty()) {
            if (temp.front()) {
                hasNonNull = true;
                break;
            }
            temp.pop();
        }
        
        if (!hasNonNull) break;
    }
}

void TPREORDER(const Tree& tree) {
    if (!tree.root) {
        cout << "Дерево пусто!\n";
        return;
    }
    
    cout << "Pre-order: ";
    stack<TNode*> s;
    s.push(tree.root);
    
    while (!s.empty()) {
        TNode* current = s.top();
        s.pop();
        cout << current->data << " ";
        
        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
    }
    cout << endl;
}

void TINORDER(const Tree& tree) {
    if (!tree.root) {
        cout << "Дерево пусто!\n";
        return;
    }
    
    cout << "In-order: ";
    stack<TNode*> s;
    TNode* current = tree.root;
    
    while (current || !s.empty()) {
        while (current) {
            s.push(current);
            current = current->left;
        }
        
        current = s.top();
        s.pop();
        cout << current->data << " ";
        
        current = current->right;
    }
    cout << endl;
}

void TPOSTORDER(const Tree& tree) {
    if (!tree.root) {
        cout << "Дерево пусто!\n";
        return;
    }
    
    cout << "Post-order: ";
    stack<TNode*> s1, s2;
    s1.push(tree.root);
    
    while (!s1.empty()) {
        TNode* current = s1.top();
        s1.pop();
        s2.push(current);
        
        if (current->left) s1.push(current->left);
        if (current->right) s1.push(current->right);
    }
    
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
    cout << endl;
}

void TCLEAR(Tree& tree) {
    ClearTree(tree.root);
    tree.root = nullptr;
    tree.size = 0;
    cout << "Дерево очищено" << endl;
}
