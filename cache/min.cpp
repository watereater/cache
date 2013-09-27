#include<iostream>
#include<queue>
#include<unordered_set>
#include<unordered_map>
#include<utility>
#include<vector>
/**
my min cache implementation
don't think it's that great. lots of problems
o well, better than brute force
*/
std::pair<int, int> minCache(std::vector<int> &vec, int limit){
	int hits = 0, misses = 0, size = vec.size(), inf = 1<<30;
	std::unordered_set<int> cache;
	std::unordered_map<int, std::vector<int> > m;
	std::vector<int> L1;

	for(int i = 0; i < size; i++)
		m[vec[i]].push_back(i);
	
	for(int i = 0; i < size; i++){
		int next = vec[i];
		if(cache.count(next)){
			hits++;
		}// cache hits are simple
		else{
			misses++;
			if(L1.size() == limit){
				int rem = -1, dist = -1;
				for(int j = 0; j < limit && dist < inf; j++){
					int cur = L1[j];
					std::vector<int>::iterator it = std
						::upper_bound(m[cur].begin(), m[cur].end(), i);
					if(it == m[cur].end()){
						rem = j;
						dist = inf;
					}
					else if(*it > dist){
						rem = j;
						dist = *it;
					}
				} // loop through L1 cache
				cache.erase(L1[rem]);
				L1.erase(L1.begin() + rem);
			}
			L1.push_back(next);
			cache.insert(next);
		}// cache miss
	}
	return std::make_pair(hits, misses);
}