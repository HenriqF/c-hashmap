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
    HashItem* HashItems;
} HashMap;


void initHashmap(HashMap* HashMap){
    (HashMap->HashItems) = malloc((HashMap->buckets)*sizeof(HashItem));
    for (size_t i = 0; i < HashMap->buckets; i++){
        HashMap->HashItems[i].key = NULL;
        HashMap->HashItems[i].value = NULL;
        HashMap->HashItems[i].value_type = NONE;
        HashMap->HashItems[i].next = NULL;
    }

}

size_t getBucket(char* string, size_t buckets){
    unsigned long hash = 5381;

    int c;
    while ((c = *string++)){
        hash = ((hash << 5) + hash) + c;
    }

    unsigned long bucket = hash % buckets;
    return (size_t)bucket;
}


void putHash(HashMap* HashMap, char* key, void* value, ValueType value_type){
    size_t key_bucket = getBucket(key, HashMap->buckets);
    HashItem* item = &(HashMap->HashItems[key_bucket]);

    while (item->next != NULL){
        if (strcmp(item->key, key) == 0){
            item->value = value;
            item->value_type = value_type;

            //printf("update\n");
            return;
        }
        item = item->next;
    }
    if(item->key == NULL){
        item->key = key;
        item->value = value;
        item->value_type = value_type;
        HashItem* new_item = malloc(sizeof(HashItem));
        *new_item = (HashItem){NULL, NULL, NONE, NULL};
        item->next = new_item;

        //printf("criacao\n");
        return;
    }
}

void getValue(HashMap HashMap, char* key, void** value, ValueType* value_type){
    size_t key_bucket = getBucket(key, HashMap.buckets);
    HashItem* item = &(HashMap.HashItems[key_bucket]);

    while (item->next != NULL){
        if (strcmp(item->key, key) == 0){
            (*value) = item->value; 
            (*value_type) = item->value_type;

            //printf("encontrado\n");
            return;
        }
        item = item->next;
    }
    //printf("sem resultados.");
}


void search(HashMap HashMap, char* key){
    
    void* result = NULL;
    ValueType rvt = NONE;
    getValue(HashMap, key, &result, &rvt);
    if (result == NULL){
        printf("nao encontrado");
    }

    else if (rvt == INT){
        printf("encontrado: %d", *(int*)result);
    }
    else if (rvt == FLOAT){
        printf("encontrado: %f", *(float*)result);
    }
    else if (rvt == CHAR){
        printf("encontrado: %c", *(char*)result);
    }
    else if (rvt == CHARA){
        printf("encontrado: %s", *(char**)result);
    }
}

int main(){

    HashMap hm = {100, NULL};
    initHashmap(&hm);

    int value = 20;
    
    putHash(&hm, "wow", &value, INT);
    search(hm, "wow");
    //putHash(&hm, "porra", &value, INT);
    



    return 0;
}