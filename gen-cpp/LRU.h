#ifndef LRU_H
#define LRU_H

#include "Cache.h"
#include <boost/unordered_map.hpp>

using namespace std;
using boost::unordered_map;

class Lru: public Cache {
	public:
		Lru(int s);
		
		string get(string key);
		
		void set(string key, string value);
	
	private:
		int currSize;
		unordered_map<string,int*> cache;

		
};

#endif
