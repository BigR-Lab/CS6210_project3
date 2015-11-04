#ifndef RANDOM_H
#define RANDOM_H

#include "Cache.h"

using namespace std;

class Random: public Cache {
	public:
		Random(int s);
		
		string get(string key);
		
		void set(string key, string value);
	
	private:
		int currSize;
};

#endif
