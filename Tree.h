#ifndef TREE_H
#define TREE_H

#include <string>

using namespace std;

struct TNode {
    string data;
    TNode* left;
    TNode* right;
    TNode* parent;
    
    TNode(const string& val, TNode* lft = nullptr, TNode* rght = nullptr, TNode* prnt = nullptr) : data(val), left(lft), right(rght), parent(prnt) {}
};

struct Tree { 
    TNode* root = nullptr; 
    size_t size = 0; 
    string filename; 
};

void TADD(Tree& tree, const string& value, bool silent = false);
bool TFIND(const Tree& tree, const string& value);
bool TISFULL(const Tree& tree);
void TLEVELORDER(const Tree& tree);
void TPRINT_STRUCTURE(const Tree& tree);
void TPREORDER(const Tree& tree);
void TINORDER(const Tree& tree);
void TPOSTORDER(const Tree& tree);
void TCLEAR(Tree& tree);

#endif
