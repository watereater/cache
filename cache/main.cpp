#include<cstdio>
#include<iostream>
#include<string>
#include<thread>
#include<time.h>
#include "Header.h"

void task1(std::string msg)
{
	int arr [12] = {1,2,3,4,1,2,3,4,1,2,3,4};
	std::vector<int> v(arr, arr+12);
	std::pair<int,int> pii = minCache(v, 3);
	std::cout << "hits " << pii.first << ' ' << " misses " << pii.second << '\n';
}

int main(){
	
	time_t start,end;
	unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
	std::cout << concurentThreadsSupported << '\n';
	
	time (&start);
	/*
	arcCache arc(3);
	int arr [] = {3, 3, 4, 5, 5, 5, 5, 6, 6, 2, 4, 6, 0, 1, 6, 2, 6, 6, 3, 4};
	std::vector<int> vec(arr, arr+sizeof(arr)/4);
	arc.solve(vec);
	std::cout << arc.gethits() << " " << arc.getmisses() << '\n';
	*/
	
	std::thread ts[16];
	for(int i = 0; i < concurentThreadsSupported; i++){
		ts[i] = std::thread(run, i);
	}
	for(int i = 0; i < concurentThreadsSupported; i++){
		ts[i].join();
	}
	time (&end);
	double dif = difftime (end,start);
	printf ("Elasped time is %.2lf seconds.", dif );
	return 0;
}