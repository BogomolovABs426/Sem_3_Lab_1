#include "Array.h"
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

void MPUSH(Array& arr, const string& value) {
    if (arr.size >= arr.capacity) {
        uint64_t newCap = arr.capacity ? arr.capacity * 2 : 4;
        string* newData = new string[newCap];
        for (uint64_t i = 0; i < arr.size; i++) newData[i] = arr.data[i];
        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCap;
    }
    
    arr.data[arr.size] = value;
    arr.size++;
}

void MADD_INDEX(Array& arr, const string& value, uint64_t index) {
    if (index > arr.size) {
        cout << "Неверный индекс! Максимальный допустимый индекс: " << arr.size << endl;
        return;
    }
    
    if (arr.size >= arr.capacity) {
        uint64_t newCap = arr.capacity ? arr.capacity * 2 : 4;
        string* newData = new string[newCap];
        for (uint64_t i = 0; i < arr.size; i++) newData[i] = arr.data[i];
        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCap;
    }
    
    for (uint64_t i = arr.size; i > index; i--) {
        arr.data[i] = arr.data[i-1];
    }
    arr.data[index] = value;
    arr.size++;
}

void MREMOVE(Array& arr, uint64_t index) {
    if (index >= arr.size) { 
        cout << "Неверный индекс!\n"; 
        return; 
    }
    for (uint64_t i = index; i < arr.size-1; i++) arr.data[i] = arr.data[i+1];
    arr.size--;
}

void MREPLACE(Array& arr, uint64_t index, const string& value) {
    if (index >= arr.size || index < 0) { 
        cout << "Неверный индекс!\n"; 
        return; 
    }
    arr.data[index] = value;
}

string MGET(const Array& arr, uint64_t index) {
    if (index >= arr.size || index < 0) throw out_of_range("Неверный индекс");
    return arr.data[index];
}

uint64_t MLENGTH(const Array& arr) {
    return arr.size;
}

void MPRINT(const Array& arr) {
    if (!arr.size) { 
        cout << "Массив пуст!\n"; 
        return; 
    }
    cout << "Массив [" << arr.size << "]: ";
    for (uint64_t i = 0; i < arr.size; i++) 
        cout << arr.data[i] << (i < arr.size-1 ? ", " : "");
    cout << endl;
}

void MCLEAR(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = arr.capacity = 0;
    cout << "Массив очищен" << endl;
}
