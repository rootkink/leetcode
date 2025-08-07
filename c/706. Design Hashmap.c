
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 1001

typedef struct node {
  struct node *next;
  int key;
  int value;
} node;

typedef struct {
  struct node *hashmap[SIZE];
} MyHashMap;

MyHashMap *myHashMapCreate() { return calloc(1, sizeof(MyHashMap)); }

void myHashMapPut(MyHashMap *obj, int key, int value) {
  int idx = key % SIZE;
  node *P = obj->hashmap[idx];
  while (P != NULL) {
    if (P->key == key) {
      P->value = value;
      return;
    }
    P = P->next;
  }

  node *n = malloc(sizeof(node));
  n->key = key;
  n->value = value;
  n->next = obj->hashmap[idx];
  obj->hashmap[idx] = n;
}

int myHashMapGet(MyHashMap *obj, int key) {
  int idx = key % SIZE;
  node *ptr = obj->hashmap[idx];
  while (ptr != NULL) {
    if (ptr->key == key)
      return ptr->value;
    ptr = ptr->next;
  }
  return -1;
}

void myHashMapRemove(MyHashMap *obj, int key) {
  int idx = key % SIZE;
  node *n = obj->hashmap[idx];
  node *prev = NULL;
  while (n != NULL) {
    if (n->key == key) {
      if (prev == NULL) {
        obj->hashmap[idx] = n->next;
      } else {
        prev->next = n->next;
      }
      free(n);
      return;
    }
    prev = n;
    n = n->next;
  }
}

void myHashMapFree(MyHashMap *obj) {
  for (int i = 0; i < SIZE; i++) {
    node *n = obj->hashmap[i];
    while (obj->hashmap[i] != NULL) {
      n = obj->hashmap[i];
      obj->hashmap[i] = obj->hashmap[i]->next;
      free(n);
    }
  }
  free(obj);
}

/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);

 * int param_2 = myHashMapGet(obj, key);

 * myHashMapRemove(obj, key);

 * myHashMapFree(obj);
*/
