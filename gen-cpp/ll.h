#ifndef LL_H
#define LL_H

typedef void* ll_item;

typedef struct ll_node_t{
  ll_item item;
  struct ll_node_t* next;
  struct ll_node_t* prev;
} ll_node_t;

typedef struct{
  ll_node_t* front;
  ll_node_t* back;
  int N;
}ll_t;


/* Initializes the data structure */
void ll_init(ll_t* list);

/* Return 1 if empty, 0 otherwise */
int ll_isempty(ll_t* list);

/* Returns the number of elements in the ll */
int ll_size(ll_t* list);

/* Adds an element to the "back" of the ll */
ll_node_t* ll_add(ll_t* list, ll_item item);

void ll_remove(ll_t* list, ll_node_t* node);

void ll_bubble(ll_t* list, ll_node_t* node);

/* Returns the element at the "front" of the ll without removing it*/
ll_item ll_front(ll_t* list);

/* Empties the ll and performs any necessary memory cleanup */
void ll_destroy(ll_t* list);

#endif
