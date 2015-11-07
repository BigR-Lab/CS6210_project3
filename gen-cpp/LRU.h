#ifndef LRU_H
#define LRU_H

#include "Cache.h"
#include "ll.h"
#include <boost/unordered_map.hpp>

using namespace std;
using boost::unordered_map;


class Lru: public Cache {
	public:
		Lru(int s);
		
		string get(string key);
		void set(string key, string value);
		void evict();
	
	private:
		int currSize;
		ll_t node_list;
		unordered_map<string,ll_node_t*> cache;

		
};

#endif
