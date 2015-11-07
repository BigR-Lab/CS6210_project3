#include "LRU_min.h"
#include <stdio.h>

using namespace std;
using boost::unordered_map;

Lrum::Lrum(int s): Cache(s) {
	currSize = 0;
	size = s;
	ll_init(&node_list);
}
		
string Lrum::get(string key){
	string _return;
	page *getPage;

	// If we find the key
	if ( cache.count(key) > 0 ) {
		
		// Bubble to most recent
		ll_bubble(&node_list, cache[key]);
		
		// Get the page, so we can return it
		getPage = (page*)(cache[key])->item;
		_return = getPage->data;
		return _return;
	}
	else {
		// Return "0" to indicate not in cache
		return "0";
	}
}
		
void Lrum::set(string key, string value){
	page *storePage;
	ll_node_t *newNode;
	
	// Do not cache if page bigger than cache
	if (value.size() > size) return;
	
	// Remove pages until enough space
	while (currSize + value.size() > size){
		evict(value.size());
	}	
	
	// Add page to linked list and node to map
	storePage = new page;
	storePage->key = key;
	storePage->data = value;
	storePage->size = value.size();
	
	newNode = ll_add(&node_list, (void*) storePage);
	cache[key] = newNode;
	
	currSize += value.size();
	if(currSize > size){
		printf("ERROR: Cache overflowed!\n");
	}
}

void Lrum::evict(int s) {
	page *removedPage;
	ll_node_t *curNode;
	
	curNode = node_list.back;
	
	// Search for node with decreasing size
	while( ((page*)curNode->item)->size < s ) {
		if(curNode->prev != NULL) {
			curNode = curNode->prev;
		}
		else {
			s = s/2;
			curNode = node_list.back;
		}
		// If we get to size is 1, something went wrong
		if (s == 1) {
			printf("ERROR: LRU_min eviction failure; s == 1!\n");
			return;
		}
	}
	
	// Get node to be removed
	removedPage = (page*) curNode->item;
	
	// Decrease total cached size by size of page
	currSize -= removedPage->data.size();
	
	// Remove node from map, delete page, remove from linked list
	cache.erase(removedPage->key);
	delete removedPage;
	ll_remove(&node_list, curNode);
	
}