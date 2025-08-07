#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 11

typedef struct node {
  struct node *next;
  int data;
} node;

typedef struct {
  struct node *myHashSet[11];
  int size;
} MyHashSet;

MyHashSet *myHashSetCreate() {
  MyHashSet *set = malloc(sizeof(MyHashSet));
  set->size = SIZE;
  for (int i = 0; i < SIZE; i++) {
    set->myHashSet[i] = NULL;
  }

  return set;
}

int hash(int key) { return key % SIZE; }

void _insert(node **head, int key) {
  node *temp = *head;
  while (temp != NULL) {
    if (temp->data == key)
      return;
    if (temp->data > key)
      break;
    temp = temp->next;
  }

  node *current = malloc(sizeof(node));
  current->data = key;
  current->next = NULL;
  if (*head == NULL || (*head)->data > key) {
    current->next = *head;
    *head = current;
    return;
  } else {
    node *ptr = *head;
    while (ptr->next != NULL && ptr->next->data < key) {
      ptr = ptr->next;
    }
    current->next = ptr->next;
    ptr->next = current;
  }
}

void myHashSetAdd(MyHashSet *obj, int key) {
  int index = hash(key);
  _insert(&obj->myHashSet[index], key);
}

void _transverse(node *head) {
  node *ptr = head;
  while (ptr != NULL) {
    printf("%d ", ptr->data);
    ptr = ptr->next;
  }
  printf("\n");
}

bool _search(node *head, int key) {
  node *ptr = head;
  while (ptr != NULL && ptr->data <= key) {
    if (ptr->data == key)
      return true;
    ptr = ptr->next;
  }
  return false;
}

bool myHashSetContains(MyHashSet *obj, int key) {
  int index = hash(key);
  return _search(obj->myHashSet[index], key);
}

void _delete(node **head, int key) {
  node *ptr = *head;
  node *prev = NULL;
  while (ptr != NULL) {
    if (ptr->data == key) {
      if (prev == NULL) {
        *head = ptr->next;
      } else {
        prev->next = ptr->next;
      }
      free(ptr);
      return;
    }
    prev = ptr;
    ptr = ptr->next;
  }
}

void myHashSetRemove(MyHashSet *obj, int key) {
  int index = hash(key);
  _delete(&obj->myHashSet[index], key);
}

void _free(node **head) {
  node *ptr = *head;

  while (*head != NULL) {
    ptr = *head;
    *head = (*head)->next;
    free(ptr);
  }
}
void myHashSetFree(MyHashSet *obj) {
  for (int i = 0; i < SIZE; i++) {
    _free(&obj->myHashSet[i]);
  }
  free(obj);
}

/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);

 * myHashSetRemove(obj, key);

 * bool param_3 = myHashSetContains(obj, key);

 * myHashSetFree(obj);
*/
