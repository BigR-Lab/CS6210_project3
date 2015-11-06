#ifndef RANDOM_H
#define RANDOM_H

#include "Cache.h"
#include <boost/unordered_map.hpp>

using namespace std;
using boost::unordered_map;

class Random: public Cache {
	public:
		Random(int s);
		
		string get(string key);
		
		void set(string key, string value);
	
	private:
		void evict();
	
		int currSize;
		
		unordered_map<string,string> cache;
};

#endif
