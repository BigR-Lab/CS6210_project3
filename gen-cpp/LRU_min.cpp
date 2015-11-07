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
		evict();
	}	
	
	// Add page to linked list and node to map
	storePage = new page;
	storePage->key = key;
	storePage->data = value;
	
	newNode = ll_add(&node_list, (void*) storePage);
	cache[key] = newNode;
	
	currSize += value.size();
}

void Lrum::evict() {
	page *removedPage;
	
	// Get node to be removed
	removedPage = (page*) node_list.back->item;
	
	// Decrease total cached size by size of page
	currSize -= removedPage->data.size();
	
	// Remove node from map, delete page, remove from linked list
	cache.erase(removedPage->key);
	delete removedPage;
	ll_remove(&node_list, node_list.back);
	
}