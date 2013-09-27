#pragma once

#include<deque>
#include<unordered_set>
#include<utility>
#include<vector>

/**
running the code
*/
void run(int);

/**
min algorithm
*/
std::pair<int, int> minCache(std::vector<int> &, int);

/**
arc algorithm
*/
class arcCache{
	std::unordered_set<int> cache, fakecache;
	std::deque<int> T1, T2, B1, B2;
	int limit, hits, misses, p;
	void init();
	void replace(bool);
public:
	arcCache(int);
	int gethits();
	int getmisses();
	void setlimit(int);
	void solve(std::vector<int> &);
};