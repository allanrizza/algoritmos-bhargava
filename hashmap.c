#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//para casos de COLISÃO
typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

#define TABLE_SIZE 10
typedef struct HashMap {
    Node *table[TABLE_SIZE];
} HashMap;

unsigned int hash(char *key) {
    unsigned int hashValue = 0;
    while(*key) {
        hashValue = (hashValue << 5) + *key++;
    }
    return hashValue % TABLE_SIZE;
}

Node *createNode(char *key, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = strdup(key); //strdup para copiar a string
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void initHashMap(HashMap *map) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;
    }
}

void insert(HashMap *map, char *key, int value) {
    unsigned int index = hash(key);
    Node *newNode = createNode(key, value);

    if(map->table[index] == NULL) {
        map->table[index] = newNode;
    } else {
        //adiciona no início da lista encadeada (chaining)
        newNode->next = map->table[index];
        map->table[index] = newNode;
    }
}

int search(HashMap *map, char *key) {
    unsigned int index = hash(key);
    Node *current = map->table[index];

    while (current != NULL) {
        if(strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return -1;
}

void removeKey(HashMap *map, char *key) {
    unsigned int index = hash(key);
    Node *current = map->table[index];
    Node *prev = NULL;

    while(current != NULL) {
        if(strcmp(current->key, key) == 0) {
            if(prev == NULL) {
                map->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void freeHashMap(HashMap *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = map->table[i];
        while(current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
}

int main() {
    HashMap map;
    initHashMap(&map);

    insert (&map, "apple", 5);
    insert(&map, "banana", 3);
    insert(&map, "orange", 8);

    printf("Valor de apple: %d\n", search(&map, "apple"));
    printf("Valor de banana: %d\n", search(&map, "banana"));
    printf("Valor de orange: %d\n", search(&map, "orange"));

    removeKey(&map, "banana");
    printf("Valor de banana após remoção: %d\n", search(&map, "banana"));

    freeHashMap(&map);

    return 0;
}