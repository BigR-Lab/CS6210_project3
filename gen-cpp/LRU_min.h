#ifndef LRUM_H
#define LRUM_H

#include "Cache.h"
#include "ll.h"
#include <boost/unordered_map.hpp>

using namespace std;
using boost::unordered_map;

typedef struct {
	string key;
	string data;
	int size;
} page;

class Lrum: public Cache {
	public:
		Lrum(int s);
		
		string get(string key);
		void set(string key, string value);
		void evict();
	
	private:
		int currSize;
		ll_t node_list;
		unordered_map<string,ll_node_t*> cache;

		
};

#endif
