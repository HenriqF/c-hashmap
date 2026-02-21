#ifndef HASH
#define HASH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum{
    INT,
    FLOAT,
    CHAR,
    CHARA,
    NONE,
}ValueType;

typedef struct HashItem{
    char* key;

    void* value;
    ValueType value_type;

    struct HashItem* next;
} HashItem;

typedef struct HashMap{
    size_t buckets;
    size_t pairs;
    HashItem* HashItems;
} HashMap;

void initHashmap(HashMap* HashMap);

size_t getBucket(char* string, size_t buckets);
void setKey(HashMap* HashMap, char* key, void* value, ValueType value_type);
void removeKey(HashMap* HashMap, char* key);

void getValue(HashMap HashMap, char* key, void** value, ValueType* value_type);

#endif