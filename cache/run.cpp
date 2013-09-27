#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h> 
#include <time.h>
#include "Header.h"

static double test(int*, int, int);
static void test1();
static void test2();

void run(int file){
	std::stringstream filename("file");
	filename << file << "txt";
	std::ofstream fout(filename.str());
	const int size = 50;
	int times = 10000, arr[size];
	srand(time(NULL)+file);
	while(times--){
		//int limit = rand() % 5 + 5; // 5 to 9;
		for(int i = 0; i < size; i++) arr[i] = rand() % 9;
		try{
			double output = test(arr, size, 4);
			if(output > 4){

				fout << output << " size=" << 4 << "= {";
				for(int i = 0; i < size; i++){
					if(i) fout << ", ";
					fout << arr[i];
				}
				fout << "}\n";
			}
		}
		catch(int e){
			fout << "exception line " << e << " {";
			for(int i = 0; i < 20; i++){
				if(i) fout << ", ";
				fout << arr[i];
			}
			fout << "}\n";
		}
	}
	fout.close();
}

double test(int *arr, int length, int size){
	std::vector<int> vec(arr, arr + length);
	std::pair<int, int> pii = minCache(vec, size);
	arcCache arc(size);
	arc.solve(vec);
	//std::cout << "Min alg hits " << pii.first << " min alg misses " << pii.second << '\n';
	//std::cout << "Arc alg hits " << arc.gethits() << " arc alg misses " << arc.getmisses() << '\n';
	double misses = arc.getmisses() / ((double)pii.second);
	return misses;
}

void test1(){
	int arr [12] = {1,2,3,4,1,2,3,4,1,2,3,4};
	std::vector<int> vec(arr, arr+12);
	std::pair<int, int> pii = minCache(vec, 3);
	arcCache arc(3);
	arc.solve(vec);
	std::cout << "Min alg hits " << pii.first << " min alg misses " << pii.second << '\n';
	std::cout << "Arc alg hits " << arc.gethits() << " arc alg misses " << arc.getmisses() << '\n';

}
void test2(){
	int arr [12] = {1,2,3,4,5,4,3,2,1,2,3,4};
	std::vector<int> vec(arr, arr+12);
	std::pair<int, int> pii = minCache(vec, 3);
	arcCache arc(3);
	arc.solve(vec);
	std::cout << "Min alg hits " << pii.first << " min alg misses " << pii.second << '\n';
	std::cout << "Arc alg hits " << arc.gethits() << " arc alg misses " << arc.getmisses() << '\n';

}