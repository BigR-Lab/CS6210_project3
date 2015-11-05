#ifndef LRU_H
#define LRU_H

#include "Cache.h"

using namespace std;

class Lru: public Cache {
	public:
		Lru(int s);
		
		string get(string key);
		
		void set(string key, string value);
	
	private:
		int currSize;
};

#endif
