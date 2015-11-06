#include <stdlib.h>
#include <stdio.h>
#include "ll.h"

void ll_init(ll_t *list){
  list->front = NULL;
  list->back = NULL;
  list->N = 0;
}

ll_node_t* ll_add(ll_t* list, ll_item item){
  ll_node_t* node;

  node = (ll_node_t*) malloc(sizeof(ll_node_t));
  node->item = item;
  node->next = NULL;
  node->prev = NULL;
  
  if(list->front == NULL)
    list->back = node;
  else {
    list->front->prev = node;
	node->next = list->front;
  }

  list->front = node;
  list->N++;
  
  return node;
}

void ll_remove(ll_t* list, ll_node_t* node){

	if (node == NULL) return;

	if(node->prev != NULL) {
		node->prev->next = node->next;
		if(node == list->back) list->back = node->prev;
	}
	if(node->next != NULL) {
		node->next->prev = node->prev;
		if(node == list->front) list->front = node->next;
	}

	free(node);
	list->N--;
	
	if (list->N == 0) {
		list->front = NULL;
		list->back = NULL;
	}
}

void ll_bubble(ll_t* list, ll_node_t* node){
	
	// Check if already front
	if(list->front == node) return;
	
	if(list->back == node){
		node->prev->next = NULL;
		list->back = node->prev;
	}
	else{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	
	list->front->prev = node;
	node->next = list->front;
	node->prev = NULL;
	list->front = node;
}

int ll_size(ll_t* list){
  return list->N;
}

int ll_isempty(ll_t *list){
  return list->N == 0;
}

ll_item ll_front(ll_t* list){
  if(list->front == NULL){
    fprintf(stderr, "Error: underflow in ll_front.\n");
    exit(1);
  }
  
  return list->front->item;
}

void ll_destroy(ll_t* list){

	while(!ll_isempty(list))
		ll_remove(list, list->front);
}
