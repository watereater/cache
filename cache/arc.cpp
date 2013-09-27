/**
Arc Algorithm written by Leo Shao

you can find the paper
Outperforming Lru with an Adaptive Replacement Algorithm
http://theory.stanford.edu/~megiddo/pdf/IEEE_COMPUTER_0404.pdf
*/

#include <assert.h>
#include <algorithm>
#include <unordered_set>
#include <deque>
#include <stdexcept>
#include <vector>

#include "Header.h"
/**
The algorithm currently uses linearly scans
But input size is going to be quite small for now
*/

	
void arcCache::init(){
	hits = misses = p = 0;
	T1.clear(); T2.clear(); B1.clear(); B2.clear();
	cache.clear(); fakecache.clear();
}

/**
replace method in paper
*/
void arcCache::replace(bool inB2){
	if((T1.size() >= 1) &&((inB2 && T1.size() == p) || T1.size() > p)){
		int rem = T1.front(); T1.pop_front();
		B1.push_back(rem);
		cache.erase(rem);
		fakecache.insert(rem);
	}
	else{
		if(T2.empty()) throw 40;
		int rem = T2.front(); T2.pop_front();
		B2.push_back(rem);
		cache.erase(rem);
		fakecache.insert(rem);
	}
}
	
arcCache::arcCache(int limit){
	this->limit = limit;
}

int arcCache::gethits() {return hits;}
int arcCache::getmisses() {return misses;}

void arcCache::setlimit(int limit){
	this->limit = limit;
}

void arcCache::solve(std::vector<int> &vec){
	init();
	for(int i = 0; i < vec.size(); i++){
		int cur = vec[i];
		/**
		Case 1 it is in cache
		Erase the value from either T1 or T2
		and add the mru of T2
		*/
		if(cache.count(cur)){

			hits++;
			int er = -1;
			for(int i = 0; i < T1.size() && er == -1; i++)
				if(T1[i] == cur) er = i;
			if(er!=-1) T1.erase(T1.begin() + er);
			else{
				for(int i = 0; i < T2.size() && er == -1; i++)
					if(T2[i] == cur) er = i;
				if(er == -1) throw 78; // it is in cache so should be in T1 or T2
				T2.erase(T2.begin() + er);
			}
			T2.push_back(cur);
		}
		/**
		Cases 2 & 3 it is in fakecache aka DBL
		Ill improve speed later worry about correctness
		*/
		else if(fakecache.count(cur)){
			misses++;
			int er = -1;
			for(int i = 0; i < B1.size() && er == -1; i++){
				if(B1[i] == cur) er = i;
			}
			/**
			Case 2 it is in B1
			*/
			if(er != -1){
				p = std::min(limit, p + std::max((int)(B2.size()/B1.size()), 1));
				replace(false);
				B1.erase(B1.begin()+er);
				T2.push_back(cur);
				fakecache.erase(cur);
				cache.insert(cur);
			}
			else{
				for(int i = 0; i < B2.size() && er == -1; i++){
					if(B2[i] == cur) er = i;
				}
				p = std::max(0, p - std::max((int)(B1.size()/B2.size()), 1));
				replace(true);
				if(er==-1) throw 116; // has to be in B1 or B2
				B2.erase(B2.begin() + er);
				T2.push_back(cur);
				fakecache.erase(cur);
				cache.insert(cur);
			}
				
		}// cases 2 & 3
		/**
		Case 4 it is in neither cache nor fakecache(DBL)
		*/
		else{
			misses++;
			/**
			Case 1 in paper
			*/
			if(T1.size() + B1.size() == limit){
				if(T1.size() < limit){
					if(!B1.empty()) {
						fakecache.erase(B1.front());
						B1.pop_front();
					}
					replace(false);
				}
				else{
					if(T1.empty()) throw 135; // paper said do it so assert first
					cache.erase(T1.front());
					T1.pop_front();
				}
			}
			/**
			Case 2 in paper
			*/
			else if(T1.size() + B1.size() < limit && cache.size() + fakecache.size() >= limit){
				if(cache.size() + fakecache.size() == 2 * limit){
					if(B2.empty()) throw 145; // paper assumes true meh
					fakecache.erase(B2.front());
					B2.pop_front();
				}	
				replace(false);
			}
			T1.push_back(cur);
			cache.insert(cur);
		}

	}// loop through all request
}// solve
