#pragma once
#include <string>
#include "Tree.h"
#include "Array.h"
#include "SinglyList.h"
#include "DoublyList.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

class Commands {
public:
    void execute(const string& query, string& filename);
};
