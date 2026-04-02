#include "hash.h"


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
        HashMap->pairs++;
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
            HashMap->pairs--;
            if (item == last_item){
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
            return;
        }
        item = item->next;
    }
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