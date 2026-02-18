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
    while ((c = *string++)) hash = ((hash << 5) + hash) + c;

    unsigned long bucket = hash % buckets;
    return (size_t)bucket;
}

void setKey(HashMap* HashMap, char* key, void* value, ValueType value_type){
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

void removeKey(HashMap* HashMap, char* key){
    size_t key_bucket = getBucket(key, HashMap->buckets);
    HashItem* item = &(HashMap->HashItems[key_bucket]);
    HashItem* last_item = item;

    while (item->next != NULL){
        if (strcmp(item->key, key) == 0){
            if (item == last_item){
                HashItem* cabeca = item;
                HashMap->HashItems[key_bucket] = *item->next;
                return;
            }
            last_item->next = item->next;
            free(item);
            return;
        }
        last_item = item;
        item = item->next;
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
        printf("nao encontrado\n");
    }

    else if (rvt == INT){
        printf("encontrado: %d\n", *(int*)result);
    }
    else if (rvt == FLOAT){
        printf("encontrado: %f\n", *(float*)result);
    }
    else if (rvt == CHAR){
        printf("encontrado: %c\n", *(char*)result);
    }
    else if (rvt == CHARA){
        printf("encontrado: %s\n", *(char**)result);
    }
}



int main(){
    HashMap hm = {100, NULL};
    initHashmap(&hm);

    int value = 20;
    char* string = "sigmdfdsafsadf";
    
    setKey(&hm, "wow", &value, INT);
    search(hm, "wow");
    setKey(&hm, "wow", &string, CHARA);
    search(hm, "wow");
    removeKey(&hm, "wow");
    search(hm, "wow");
    setKey(&hm, "wow", &value, INT);
    search(hm, "wow");

    return 0;
}