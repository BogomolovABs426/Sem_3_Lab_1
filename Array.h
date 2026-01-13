#ifndef ARRAY_H
#define ARRAY_H

#include <string>
#include <cstdint>

using namespace std;

struct Array { 
    string* data = nullptr;
    size_t size = 0; 
    uint64_t capacity = 0; 
    string filename; 
};

void MPUSH(Array& arr, const string& value);
void MADD_INDEX(Array& arr, const string& value, uint64_t index);
void MREMOVE(Array& arr, uint64_t index);
void MREPLACE(Array& arr, uint64_t index, const string& value);
string MGET(const Array& arr, uint64_t index);
uint64_t MLENGTH(const Array& arr);
void MPRINT(const Array& arr);
void MCLEAR(Array& arr);

#endif
