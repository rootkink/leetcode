#include <stdbool.h>
#include <stdlib.h>

#define SIZE 1013

typedef struct LRUNode {
  struct LRUNode *next;
  struct LRUNode *prev;
  int key;
  int val;
} LRUNode;

typedef struct hashNode {
  int key;
  LRUNode *node;
  struct hashNode *next;
} hashNode;

typedef struct {
  LRUNode *head;
  LRUNode *tail;
  int capacity;
  int size;
  hashNode *Map[SIZE];
} LRUCache;
void HashMapSet(LRUCache *obj, int key, LRUNode *n) {
  int idx = key % SIZE;
  hashNode *t = malloc(sizeof(hashNode));
  t->key = key;
  t->node = n;
  t->next = obj->Map[idx];
  obj->Map[idx] = t;
}

bool HashMapHas(LRUCache *obj, int key) {
  int idx = key % SIZE;
  hashNode *n = obj->Map[idx];
  while (n) {
    if (n->key == key)
      return true;
    n = n->next;
  }
  return false;
}

LRUNode *HashMapGet(LRUCache *obj, int key) {
  int idx = key % SIZE;
  hashNode *n = obj->Map[idx];
  while (n) {
    if (n->key == key) {
      return n->node;
    }
    n = n->next;
  }
  return NULL;
}

void HashMapDelete(LRUCache *obj, int key) {
  int idx = key % SIZE;
  hashNode *n = obj->Map[idx];
  hashNode *prev = NULL;
  while (n) {
    if (n->key == key) {
      if (prev)
        prev->next = n->next;
      else
        obj->Map[idx] = n->next;
      free(n);
      return;
    }
    prev = n;
    n = n->next;
  }
}
void addNode(LRUCache *obj, LRUNode *n) {
  n->next = obj->head;
  n->prev = NULL;
  if (obj->head)
    obj->head->prev = n;
  obj->head = n;
  if (!obj->tail)
    obj->tail = n;
  obj->size++;
}

int removeNode(LRUCache *obj, LRUNode *n, bool shouldFree) {
  if (n->prev)
    n->prev->next = n->next;
  if (n->next)
    n->next->prev = n->prev;
  if (n == obj->head)
    obj->head = n->next;
  if (n == obj->tail)
    obj->tail = n->prev;
  n->prev = NULL;
  n->next = NULL;
  int key = n->key;
  obj->size--;
  if (shouldFree)
    free(n);
  return key;
}

LRUCache *lRUCacheCreate(int capacity) {
  LRUCache *obj = (LRUCache *)calloc(1, sizeof(LRUCache));
  obj->capacity = capacity;
  obj->size = 0;
  obj->head = NULL;
  obj->tail = NULL;
  return obj;
}

int lRUCacheGet(LRUCache *obj, int key) {
  if (HashMapHas(obj, key)) {
    LRUNode *node = HashMapGet(obj, key);
    removeNode(obj, node, false);
    addNode(obj, node);
    return node->val;
  }
  return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value) {
  if (HashMapHas(obj, key)) {
    LRUNode *node = HashMapGet(obj, key);
    node->val = value;
    removeNode(obj, node, false);
    addNode(obj, node);
    return;
  }
  if (obj->size == obj->capacity) {
    int key = removeNode(obj, obj->tail, true);
    HashMapDelete(obj, key);
  }
  LRUNode *n = malloc(sizeof(LRUNode));
  n->key = key;
  n->val = value;
  addNode(obj, n);
  HashMapSet(obj, key, n);
}

void lRUCacheFree(LRUCache *obj) {
  LRUNode *n = obj->head;
  while (n) {
    LRUNode *p = n->next;
    free(n);
    n = p;
  }
  for (int i = 0; i < SIZE; i++) {
    hashNode *n = obj->Map[i];
    while (n) {
      hashNode *p = n->next;
      free(n);
      n = p;
    }
  }
  free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);

 * lRUCachePut(obj, key, value);

 * lRUCacheFree(obj);
*/
