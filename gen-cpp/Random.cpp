#include "Random.h"


using namespace std;
using boost::unordered_map;

Random::Random(int s): Cache(s) {
	currSize = 0;
}
		
string Random::get(string key){
	
	if ( cache.count(key) > 0 ) {
		// If we find the key
		return cache[key]; // return the actual string
	}
	else {
		return "0";
	}
	
}
		
void Random::set(string key, string value){
	if ( cache.count(key) > 0 || value.size() > size) {
		return;
	}
	else{
		//keep evicting until currSize is small enough
		while (currSize + value.size() > size){
			evict();
		}
		//using character count as size, because 1 char = 1 byte
		currSize += value.size();
		cache[key] = value;
	}
}

//randomly select item and delete from hash
void Random::evict(){
	int val = rand() % cache.size();

	boost::unordered_map<string,string>::iterator random_it;
	//it++ is the only way to advance the iterator in boost
	int i = 0;
	for(random_it = cache.begin(); i < val; ++random_it){
		i++;
	}
	
	currSize -= random_it->second.size();
	cache.erase(random_it);
}

