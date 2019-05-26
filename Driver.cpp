//Lili Chen
#include <iostream>
#include <string>
#include <vector>
#include <chrono> 
#include <time.h>
#include "BST.h"

using namespace std;
using namespace std::chrono;

void runExperiment(int n)
{
	srand(time(NULL));
	vector<int> testSet;
	for (int i = 0; i < n; i++)
		testSet.push_back(rand());

	// BST

	// start time
	auto start = high_resolution_clock::now();

	BST<int> bTree;
	for (int i = 0; i < testSet.size(); i++)
	{
		bTree.Insert(testSet[i]);
	}
	for (int i = 1; i < testSet.size(); i = i + 2)
	{
		bTree.Remove(testSet[i]);
	}

	// end time
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken for BST when N = " << n << ": "
		<< duration.count() << " microseconds" << endl;

	// AVL

	// start time
	start = high_resolution_clock::now();

	AVL<int> aTree;
	for (int i = 0; i < testSet.size(); i++)
	{
		aTree.Insert(testSet[i]);
	}
	for (int i = 1; i < testSet.size(); i = i + 2)
	{
		aTree.Remove(testSet[i]);
	}

	// end time
	stop = high_resolution_clock::now();

	duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken for AVL when N = " << n << ": "
		<< duration.count() << " microseconds" << endl;
}

int main()
{
	runExperiment(1000);
	runExperiment(100000);
	runExperiment(1000000);
	return 0;
}