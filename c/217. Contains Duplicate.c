#include <stdbool.h>
#include <stdlib.h>

#define SIZE 1009
typedef struct entry {
  struct entry *next;
  int val;
} entry;

typedef struct {
  entry *table[SIZE];
} Hashset;

Hashset *create() { return calloc(1, sizeof(Hashset)); }
void insert(Hashset *obj, int key) {
  int idx = (key % SIZE + SIZE) % SIZE;
  entry *n = malloc(sizeof(entry));
  n->val = key;
  n->next = obj->table[idx];
  obj->table[idx] = n;
}
bool has(Hashset *obj, int key) {

  int idx = (key % SIZE + SIZE) % SIZE;
  entry *p = obj->table[idx];
  while (p != NULL) {
    if (p->val == key)
      return true;
    p = p->next;
  }
  return false;
}

bool containsDuplicate(int *nums, int numsSize) {
  if (nums == NULL || numsSize <= 0)
    return false;
  Hashset *set = create();
  for (int i = 0; i < numsSize; i++) {
    if (has(set, nums[i]))
      return true;
    else
      insert(set, nums[i]);
  }
  return false;
}
