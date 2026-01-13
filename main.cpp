#include "Array.h"
#include "SinglyList.h"
#include "Commands.h"
#include "DoublyList.h"
#include "Stack.h"
#include "Queue.h"
#include "Tree.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

// ----- Структура для хранения всех структур данных -----
struct Database {
    map<string, Array> arrays;
    map<string, SingleList> singlyLists;
    map<string, DoublyList> doublyLists;
    map<string, Stack> stacks;
    map<string, Queue> queues;
    map<string, Tree> trees;
};

// ----- Вспомогательные функции для загрузки и сохранения -----
void loadDatabaseFromFile(const string& filename, Database& db) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        return; // Файл не существует, база пустая
    }

    string line;
    string currentStructure;
    string currentType;

    while (getline(fin, line)) {
        if (line.empty()) continue;

        // Проверяем, является ли строка заголовком структуры
        if (line[0] == '[' && line[line.length()-1] == ']') {
            string header = line.substr(1, line.length()-2);
            size_t pos = header.find(':');
            if (pos != string::npos) {
                currentStructure = header.substr(0, pos);
                currentType = header.substr(pos + 1);
            }
            continue;
        }

        // Загружаем данные в соответствующую структуру
        if (currentType == "ARRAY") {
            MPUSH(db.arrays[currentStructure], line);
        }
        else if (currentType == "SINGLY_LIST") {
            FADD_TAIL(db.singlyLists[currentStructure], line);
        }
        else if (currentType == "DOUBLY_LIST") {
            LADD_TAIL(db.doublyLists[currentStructure], line);
        }
        else if (currentType == "STACK") {
            SPUSH(db.stacks[currentStructure], line);
        }
        else if (currentType == "QUEUE") {
            QPUSH(db.queues[currentStructure], line);
        }
        else if (currentType == "TREE") {
            TADD(db.trees[currentStructure], line, true);
        }
    }
    fin.close();
}

void saveDatabaseToFile(const string& filename, Database& db) {
    ofstream fout(filename);
    if (!fout.is_open()) return;

    // Сохраняем массивы
    for (auto& pair : db.arrays) {
        fout << "[" << pair.first << ":ARRAY]" << endl;
        Array& arr = pair.second;
        for (uint64_t i = 0; i < arr.size; i++) {
            fout << arr.data[i] << endl;
        }
        fout << endl;
    }

    // Сохраняем односвязные списки
    for (auto& pair : db.singlyLists) {
        fout << "[" << pair.first << ":SINGLY_LIST]" << endl;
        SingleList& list = pair.second;
        FNode* curr = list.head;
        while (curr) {
            fout << curr->data << endl;
            curr = curr->next;
        }
        fout << endl;
    }

    // Сохраняем двусвязные списки
    for (auto& pair : db.doublyLists) {
        fout << "[" << pair.first << ":DOUBLY_LIST]" << endl;
        DoublyList& list = pair.second;
        LNode* curr = list.head;
        while (curr) {
            fout << curr->data << endl;
            curr = curr->next;
        }
        fout << endl;
    }

    // Сохраняем стеки (в обратном порядке)
    for (auto& pair : db.stacks) {
        fout << "[" << pair.first << ":STACK]" << endl;
        Stack& stack = pair.second;
        vector<string> temp;
        SNode* curr = stack.top;
        while (curr) {
            temp.push_back(curr->data);
            curr = curr->next;
        }
        for (int i = temp.size() - 1; i >= 0; i--) {
            fout << temp[i] << endl;
        }
        fout << endl;
    }

    // Сохраняем очереди
    for (auto& pair : db.queues) {
        fout << "[" << pair.first << ":QUEUE]" << endl;
        Queue& queue = pair.second;
        QNode* curr = queue.front;
        while (curr) {
            fout << curr->data << endl;
            curr = curr->next;
        }
        fout << endl;
    }

    // Сохраняем деревья (level-order)
    for (auto& pair : db.trees) {
        fout << "[" << pair.first << ":TREE]" << endl;
        Tree& tree = pair.second;
        if (tree.root) {
            queue<TNode*> q;
            q.push(tree.root);
            while (!q.empty()) {
                TNode* current = q.front();
                q.pop();
                fout << current->data << endl;
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
        }
        fout << endl;
    }

    fout.close();
}

// ----- Универсальная функция PRINT -----
void PRINT(const Database& db, const string& structureName, const string& structureType = "") {
    string type = structureType;
    transform(type.begin(), type.end(), type.begin(), ::toupper);

    if (type == "ARRAY" || type == "M") {
        auto it = db.arrays.find(structureName);
        if (it != db.arrays.end()) {
            cout << "ARRAY '" << structureName << "': ";
            MPRINT(it->second);
        } else {
            cout << "Массив '" << structureName << "' не найден!" << endl;
        }
    }
    else if (type == "SINGLY_LIST" || type == "SINGLY" || type == "F") {
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            cout << "SINGLY LIST '" << structureName << "': ";
            FPRINT(it->second);
        } else {
            cout << "Односвязный список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (type == "DOUBLY_LIST" || type == "DOUBLY" || type == "L") {
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            cout << "DOUBLY LIST '" << structureName << "': ";
            LPRINT(it->second);
        } else {
            cout << "Двусвязный список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (type == "STACK" || type == "S") {
        auto it = db.stacks.find(structureName);
        if (it != db.stacks.end()) {
            cout << "STACK '" << structureName << "': ";
            SPRINT(it->second);
        } else {
            cout << "Стек '" << structureName << "' не найден!" << endl;
        }
    }
    else if (type == "QUEUE" || type == "Q") {
        auto it = db.queues.find(structureName);
        if (it != db.queues.end()) {
            cout << "QUEUE '" << structureName << "': ";
            QPRINT(it->second);
        } else {
            cout << "Очередь '" << structureName << "' не найден!" << endl;
        }
    }
    else if (type == "TREE" || type == "T") {
        auto it = db.trees.find(structureName);
        if (it != db.trees.end()) {
            cout << "TREE '" << structureName << "': ";
            TLEVELORDER(it->second);
        } else {
            cout << "Дерево '" << structureName << "' не найден!" << endl;
        }
    }
    else {
        cout << "Неизвестный тип структуры: " << structureType << endl;
        cout << "Доступные: ARRAY(M), SINGLY_LIST(F), DOUBLY_LIST(L), STACK(S), QUEUE(Q), TREE(T)" << endl;
    }
}

// ----- Обработка команд -----
void Commands::execute(const string& query, string& filename) {
    istringstream iss(query);
    vector<string> tokens;
    string token;
    
    // Разбиваем запрос на токены
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    if (tokens.empty()) {
        cerr << "Пустая команда!" << endl;
        return;
    }
    
    string command = tokens[0];
    
    // Обработка команды PRINT
    if (command == "PRINT") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для PRINT. Формат: PRINT <имя> <тип>" << endl;
            return;
        }
        Database db;
        loadDatabaseFromFile(filename, db);
        PRINT(db, tokens[1], tokens[2]);
        return;
    }
    
    // Для остальных команд нужны хотя бы 2 токена (команда + имя структуры)
    if (tokens.size() < 2) {
        cerr << "Недостаточно параметров. Формат: <команда> <имя_структуры> [параметры...]" << endl;
        return;
    }
    
    string structureName = tokens[1];
    Database db;
    loadDatabaseFromFile(filename, db);
    
    // ---- TREE ----
    if (command == "TADD") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для TADD. Формат: TADD <имя> <значение>" << endl;
            return;
        }
        TADD(db.trees[structureName], tokens[2]);
        saveDatabaseToFile(filename, db);
        cout << "-> вставлен " << tokens[2] << " в дерево '" << structureName << "'" << endl;
    }
    else if (command == "TFIND") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для TFIND. Формат: TFIND <имя> <значение>" << endl;
            return;
        }
        auto it = db.trees.find(structureName);
        if (it != db.trees.end()) {
            TFIND(it->second, tokens[2]);
        } else {
            cout << "Дерево '" << structureName << "' не найдено!" << endl;
        }
    }
    else if (command == "TISFULL") {
        auto it = db.trees.find(structureName);
        if (it != db.trees.end()) {
            bool ok = TISFULL(it->second);
            cout << "-> " << (ok ? "FULL" : "NOT FULL") << endl;
        } else {
            cout << "Дерево '" << structureName << "' не найдено!" << endl;
        }
    }
    else if (command == "TLEVELORDER") {
        auto it = db.trees.find(structureName);
        if (it != db.trees.end()) {
            TLEVELORDER(it->second);
        } else {
            cout << "Дерево '" << structureName << "' не найдено!" << endl;
        }
    }
    else if (command == "TPRINT") {
        auto it = db.trees.find(structureName);
        if (it != db.trees.end()) {
            TPRINT_STRUCTURE(it->second);
        } else {
            cout << "Дерево '" << structureName << "' не найдено!" << endl;
        }
    }
    else if (command == "TPREORDER") {
        auto it = db.trees.find(structureName);
        if (it != db.trees.end()) {
            TPREORDER(it->second);
        } else {
            cout << "Дерево '" << structureName << "' не найдено!" << endl;
        }
    }
    else if (command == "TINORDER") {
        auto it = db.trees.find(structureName);
        if (it != db.trees.end()) {
            TINORDER(it->second);
        } else {
            cout << "Дерево '" << structureName << "' не найдено!" << endl;
        }
    }
    else if (command == "TPOSTORDER") {
        auto it = db.trees.find(structureName);
        if (it != db.trees.end()) {
            TPOSTORDER(it->second);
        } else {
            cout << "Дерево '" << structureName << "' не найдено!" << endl;
        }
    }
    else if (command == "TCLEAR") {
        auto it = db.trees.find(structureName);
        if (it != db.trees.end()) {
            TCLEAR(it->second);
            db.trees.erase(it);
            saveDatabaseToFile(filename, db);
            cout << "-> дерево '" << structureName << "' очищено" << endl;
        } else {
            cout << "Дерево '" << structureName << "' не найдено!" << endl;
        }
    }

    // ---- ARRAY ----
    else if (command == "MPUSH") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для MPUSH. Формат: MPUSH <имя> <значение>" << endl;
            return;
        }
        MPUSH(db.arrays[structureName], tokens[2]);
        saveDatabaseToFile(filename, db);
        cout << "-> добавлен " << tokens[2] << " в массив '" << structureName << "'" << endl;
    }
    else if (command == "MADD_INDEX") {
        if (tokens.size() < 4) {
            cerr << "Недостаточно параметров для MADD_INDEX. Формат: MADD_INDEX <имя> <значение> <индекс>" << endl;
            return;
        }
        auto it = db.arrays.find(structureName);
        if (it != db.arrays.end()) {
            try {
                uint64_t index = stoull(tokens[3]);
                MADD_INDEX(it->second, tokens[2], index);
                saveDatabaseToFile(filename, db);
                cout << "-> вставлен " << tokens[2] << " по индексу " << index << " в массив '" << structureName << "'" << endl;
            } catch (const exception& e) {
                cerr << "Ошибка преобразования индекса: " << e.what() << endl;
            }
        } else {
            cout << "Массив '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "MREMOVE") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для MREMOVE. Формат: MREMOVE <имя> <индекс>" << endl;
            return;
        }
        auto it = db.arrays.find(structureName);
        if (it != db.arrays.end()) {
            try {
                uint64_t index = stoull(tokens[2]);
                if (index < it->second.size) {
                    MREMOVE(it->second, index);
                    saveDatabaseToFile(filename, db);
                    cout << "-> удалён элемент по индексу " << index << " из массива '" << structureName << "'" << endl;
                } else {
                    cout << "Ошибка: индекс " << index << " вне диапазона" << endl;
                }
            } catch (const exception& e) {
                cerr << "Ошибка преобразования индекса: " << e.what() << endl;
            }
        } else {
            cout << "Массив '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "MREPLACE") {
        if (tokens.size() < 4) {
            cerr << "Недостаточно параметров для MREPLACE. Формат: MREPLACE <имя> <индекс> <значение>" << endl;
            return;
        }
        auto it = db.arrays.find(structureName);
        if (it != db.arrays.end()) {
            try {
                uint64_t index = stoull(tokens[2]);
                MREPLACE(it->second, index, tokens[3]);
                saveDatabaseToFile(filename, db);
                cout << "-> заменён элемент по индексу " << index << " на " << tokens[3] << " в массиве '" << structureName << "'" << endl;
            } catch (const exception& e) {
                cerr << "Ошибка преобразования индекса: " << e.what() << endl;
            }
        } else {
            cout << "Массив '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "MGET") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для MGET. Формат: MGET <имя> <индекс>" << endl;
            return;
        }
        auto it = db.arrays.find(structureName);
        if (it != db.arrays.end()) {
            try {
                uint64_t index = stoull(tokens[2]);
                string result = MGET(it->second, index);
                cout << "-> " << result << endl;
            } catch (const out_of_range& e) {
                cout << "Ошибка: " << e.what() << endl;
            } catch (const exception& e) {
                cerr << "Ошибка преобразования индекса: " << e.what() << endl;
            }
        } else {
            cout << "Массив '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "MLENGTH") {
        auto it = db.arrays.find(structureName);
        if (it != db.arrays.end()) {
            uint64_t length = MLENGTH(it->second);
            cout << "-> " << length << endl;
        } else {
            cout << "Массив '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "MPRINT") {
        auto it = db.arrays.find(structureName);
        if (it != db.arrays.end()) {
            cout << "-> ";
            MPRINT(it->second);
        } else {
            cout << "Массив '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "MCLEAR") {
        auto it = db.arrays.find(structureName);
        if (it != db.arrays.end()) {
            MCLEAR(it->second);
            db.arrays.erase(it);
            saveDatabaseToFile(filename, db);
            cout << "-> массив '" << structureName << "' очищен" << endl;
        } else {
            cout << "Массив '" << structureName << "' не найден!" << endl;
        }
    }

    // ---- SINGLY LINKED LIST ----
    else if (command == "FADD_HEAD") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для FADD_HEAD. Формат: FADD_HEAD <имя> <значение>" << endl;
            return;
        }
        FADD_HEAD(db.singlyLists[structureName], tokens[2]);
        saveDatabaseToFile(filename, db);
        cout << "-> добавлен " << tokens[2] << " в голову списка '" << structureName << "'" << endl;
    }
    else if (command == "FADD_TAIL") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для FADD_TAIL. Формат: FADD_TAIL <имя> <значение>" << endl;
            return;
        }
        FADD_TAIL(db.singlyLists[structureName], tokens[2]);
        saveDatabaseToFile(filename, db);
        cout << "-> добавлен " << tokens[2] << " в список '" << structureName << "'" << endl;
    }
    else if (command == "FADD_BEFORE") {
        if (tokens.size() < 4) {
            cerr << "Недостаточно параметров для FADD_BEFORE. Формат: FADD_BEFORE <имя> <значение> <цель>" << endl;
            return;
        }
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            FADD_BEFORE(it->second, tokens[2], tokens[3]);
            saveDatabaseToFile(filename, db);
            cout << "-> вставлен " << tokens[2] << " перед " << tokens[3] << " в список '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "FADD_AFTER") {
        if (tokens.size() < 4) {
            cerr << "Недостаточно параметров для FADD_AFTER. Формат: FADD_AFTER <имя> <значение> <цель>" << endl;
            return;
        }
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            FADD_AFTER(it->second, tokens[2], tokens[3]);
            saveDatabaseToFile(filename, db);
            cout << "-> вставлен " << tokens[2] << " после " << tokens[3] << " в список '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "FREMOVE_HEAD") {
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            FREMOVE_HEAD(it->second);
            saveDatabaseToFile(filename, db);
            cout << "-> удалён первый элемент из списка '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "FREMOVE_TAIL") {
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            FREMOVE_TAIL(it->second);
            saveDatabaseToFile(filename, db);
            cout << "-> удалён последний элемент из списка '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "FREMOVE_BEFORE") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для FREMOVE_BEFORE. Формат: FREMOVE_BEFORE <имя> <цель>" << endl;
            return;
        }
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            FREMOVE_BEFORE(it->second, tokens[2]);
            saveDatabaseToFile(filename, db);
            cout << "-> удалён элемент перед " << tokens[2] << " из списка '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "FREMOVE_AFTER") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для FREMOVE_AFTER. Формат: FREMOVE_AFTER <имя> <цель>" << endl;
            return;
        }
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            FREMOVE_AFTER(it->second, tokens[2]);
            saveDatabaseToFile(filename, db);
            cout << "-> удалён элемент после " << tokens[2] << " из списка '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "FREMOVE_BY_VALUE") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для FREMOVE_BY_VALUE. Формат: FREMOVE_BY_VALUE <имя> <значение>" << endl;
            return;
        }
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            bool ok = FREMOVE_BY_VALUE(it->second, tokens[2]);
            saveDatabaseToFile(filename, db);
            if (ok)
                cout << "-> удалён " << tokens[2] << " из списка '" << structureName << "'" << endl;
            else
                cout << "-> элемент " << tokens[2] << " не найден в списке '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "FFIND") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для FFIND. Формат: FFIND <имя> <значение>" << endl;
            return;
        }
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            FFIND(it->second, tokens[2]);
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "FPRINT") {
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            cout << "-> ";
            FPRINT(it->second);
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "FPRINT_FORWARD") {
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            cout << "-> ";
            FPRINT_FORWARD(it->second);
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "FPRINT_BACKWARD") {
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            cout << "-> ";
            FPRINT_BACKWARD(it->second);
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "FCLEAR") {
        auto it = db.singlyLists.find(structureName);
        if (it != db.singlyLists.end()) {
            FCLEAR(it->second);
            db.singlyLists.erase(it);
            saveDatabaseToFile(filename, db);
            cout << "-> список '" << structureName << "' очищен" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }

    // ---- DOUBLY LINKED LIST ----
    else if (command == "LADD_HEAD") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для LADD_HEAD. Формат: LADD_HEAD <имя> <значение>" << endl;
            return;
        }
        LADD_HEAD(db.doublyLists[structureName], tokens[2]);
        saveDatabaseToFile(filename, db);
        cout << "-> добавлен " << tokens[2] << " в голову списка '" << structureName << "'" << endl;
    }
    else if (command == "LADD_TAIL") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для LADD_TAIL. Формат: LADD_TAIL <имя> <значение>" << endl;
            return;
        }
        LADD_TAIL(db.doublyLists[structureName], tokens[2]);
        saveDatabaseToFile(filename, db);
        cout << "-> добавлен " << tokens[2] << " в список '" << structureName << "'" << endl;
    }
    else if (command == "LADD_BEFORE") {
        if (tokens.size() < 4) {
            cerr << "Недостаточно параметров для LADD_BEFORE. Формат: LADD_BEFORE <имя> <значение> <цель>" << endl;
            return;
        }
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            LADD_BEFORE(it->second, tokens[2], tokens[3]);
            saveDatabaseToFile(filename, db);
            cout << "-> вставлен " << tokens[2] << " перед " << tokens[3] << " в список '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "LADD_AFTER") {
        if (tokens.size() < 4) {
            cerr << "Недостаточно параметров для LADD_AFTER. Формат: LADD_AFTER <имя> <значение> <цель>" << endl;
            return;
        }
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            LADD_AFTER(it->second, tokens[2], tokens[3]);
            saveDatabaseToFile(filename, db);
            cout << "-> вставлен " << tokens[2] << " после " << tokens[3] << " в список '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "LREMOVE_HEAD") {
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            LREMOVE_HEAD(it->second);
            saveDatabaseToFile(filename, db);
            cout << "-> удалён первый элемент из списка '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "LREMOVE_TAIL") {
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            LREMOVE_TAIL(it->second);
            saveDatabaseToFile(filename, db);
            cout << "-> удалён последний элемент из списка '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "LREMOVE_BEFORE") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для LREMOVE_BEFORE. Формат: LREMOVE_BEFORE <имя> <цель>" << endl;
            return;
        }
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            LREMOVE_BEFORE(it->second, tokens[2]);
            saveDatabaseToFile(filename, db);
            cout << "-> удалён элемент перед " << tokens[2] << " из списка '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "LREMOVE_AFTER") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для LREMOVE_AFTER. Формат: LREMOVE_AFTER <имя> <цель>" << endl;
            return;
        }
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            LREMOVE_AFTER(it->second, tokens[2]);
            saveDatabaseToFile(filename, db);
            cout << "-> удалён элемент после " << tokens[2] << " из списка '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "LREMOVE_BY_VALUE") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для LREMOVE_BY_VALUE. Формат: LREMOVE_BY_VALUE <имя> <значение>" << endl;
            return;
        }
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            bool ok = LREMOVE_BY_VALUE(it->second, tokens[2]);
            saveDatabaseToFile(filename, db);
            if (ok)
                cout << "-> удалён " << tokens[2] << " из списка '" << structureName << "'" << endl;
            else
                cout << "-> элемент " << tokens[2] << " не найден в списке '" << structureName << "'" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "LFIND") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для LFIND. Формат: LFIND <имя> <значение>" << endl;
            return;
        }
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            LFIND(it->second, tokens[2]);
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "LPRINT") {
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            cout << "-> ";
            LPRINT(it->second);
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "LPRINT_FORWARD") {
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            cout << "-> ";
            LPRINT_FORWARD(it->second);
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "LPRINT_BACKWARD") {
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            cout << "-> ";
            LPRINT_BACKWARD(it->second);
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "LCLEAR") {
        auto it = db.doublyLists.find(structureName);
        if (it != db.doublyLists.end()) {
            LCLEAR(it->second);
            db.doublyLists.erase(it);
            saveDatabaseToFile(filename, db);
            cout << "-> список '" << structureName << "' очищен" << endl;
        } else {
            cout << "Список '" << structureName << "' не найден!" << endl;
        }
    }

    // ---- STACK ----
    else if (command == "SPUSH") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для SPUSH. Формат: SPUSH <имя> <значение>" << endl;
            return;
        }
        SPUSH(db.stacks[structureName], tokens[2]);
        saveDatabaseToFile(filename, db);
        cout << "-> добавлен " << tokens[2] << " в стек '" << structureName << "'" << endl;
    }
    else if (command == "SPOP") {
        auto it = db.stacks.find(structureName);
        if (it != db.stacks.end()) {
            if (it->second.top) {
                SPOP(it->second);
                saveDatabaseToFile(filename, db);
                cout << "-> удалён верхний элемент из стека '" << structureName << "'" << endl;
            } else {
                cout << "Ошибка: стек '" << structureName << "' пуст" << endl;
            }
        } else {
            cout << "Стек '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "SPRINT") {
        auto it = db.stacks.find(structureName);
        if (it != db.stacks.end()) {
            cout << "-> ";
            SPRINT(it->second);
        } else {
            cout << "Стек '" << structureName << "' не найден!" << endl;
        }
    }
    else if (command == "SCLEAR") {
        auto it = db.stacks.find(structureName);
        if (it != db.stacks.end()) {
            SCLEAR(it->second);
            db.stacks.erase(it);
            saveDatabaseToFile(filename, db);
            cout << "-> стек '" << structureName << "' очищен" << endl;
        } else {
            cout << "Стек '" << structureName << "' не найден!" << endl;
        }
    }

    // ---- QUEUE ----
    else if (command == "QPUSH") {
        if (tokens.size() < 3) {
            cerr << "Недостаточно параметров для QPUSH. Формат: QPUSH <имя> <значение>" << endl;
            return;
        }
        QPUSH(db.queues[structureName], tokens[2]);
        saveDatabaseToFile(filename, db);
        cout << "-> добавлен " << tokens[2] << " в очередь '" << structureName << "'" << endl;
    }
    else if (command == "QPOP") {
        auto it = db.queues.find(structureName);
        if (it != db.queues.end()) {
            if (it->second.front) {
                QPOP(it->second);
                saveDatabaseToFile(filename, db);
                cout << "-> удалён первый элемент из очереди '" << structureName << "'" << endl;
            } else {
                cout << "Ошибка: очередь '" << structureName << "' пуста" << endl;
            }
        } else {
            cout << "Очередь '" << structureName << "' не найдена!" << endl;
        }
    }
    else if (command == "QPRINT") {
        auto it = db.queues.find(structureName);
        if (it != db.queues.end()) {
            cout << "-> ";
            QPRINT(it->second);
        } else {
            cout << "Очередь '" << structureName << "' не найдена!" << endl;
        }
    }
    else if (command == "QCLEAR") {
        auto it = db.queues.find(structureName);
        if (it != db.queues.end()) {
            QCLEAR(it->second);
            db.queues.erase(it);
            saveDatabaseToFile(filename, db);
            cout << "-> очередь '" << structureName << "' очищена" << endl;
        } else {
            cout << "Очередь '" << structureName << "' не найдена!" << endl;
        }
    }

    else {
        cerr << "Неизвестная команда: " << command << endl;
    }
}

// Функция для разбора аргументов командной строки
void parseCommandLine(int argc, char* argv[], string& filename, string& query) {
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }
}

int main(int argc, char* argv[]) {
    Commands cmd;
    string filename;
    string query;

    // Если переданы аргументы командной строки
    if (argc > 1) {
        parseCommandLine(argc, argv, filename, query);
        
        if (filename.empty() || query.empty()) {
            cerr << "Использование: " << argv[0] << " --file <filename> --query <command>" << endl;
            cerr << "Пример: " << argv[0] << " --file file.data --query 'SPUSH mystack item'" << endl;
            return 1;
        }
        
        // Выполняем команду
        cmd.execute(query, filename);
    } else {
        // Интерактивный режим
        cout << "Введите имя файла для работы: ";
        cin >> filename;
        cout << "Введите команды:" << endl;
        cin.ignore();

        while (true) {
            cout << "> ";
            getline(cin, query);
            
            if (query == "exit" || query == "quit") {
                break;
            }
            
            if (!query.empty()) {
                cmd.execute(query, filename);
            }
        }
    }

    return 0;
}
