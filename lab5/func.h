#ifndef UNTITLED3_FUNC_H
#define UNTITLED3_FUNC_H

typedef struct Node {
    char *key;
    char *value;
    struct Node *prev, *next;
} Node;

typedef struct {
    int capacity;
    int count;
    Node *head, *tail;
    Node **map;
} LRUCache;

Node* createNode(char *key, char *value);
LRUCache* createCache(int capacity);
int hashFunction(const char* key);
void addToHead(LRUCache* cache, Node* node);
void removeNode(LRUCache* cache, Node* node);
void put(LRUCache* cache, char *key, char *value);
char* get(LRUCache* cache, char *key);
char* getKey(LRUCache* cache, char *key);
void freeCache(LRUCache* cache);
bool validateIp(const char *ip);
void putInFile(FILE* fp,int mode);
int searchInFile(LRUCache* cache,FILE* fp,char* key, int mode);
void searchAndPrint(LRUCache* cache,FILE* fp, char* key,int mode);
void printCache(LRUCache* cache);


#endif //UNTITLED3_FUNC_H
