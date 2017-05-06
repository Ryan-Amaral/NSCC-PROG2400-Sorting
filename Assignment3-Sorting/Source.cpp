//  File: Source.cpp
//	Purpose: The main driver file of the app.
//  Project: Assignment3-Sorting
//  Author: Ryan Amaral
//  Created On: February 22, 2016

#include "Sorting.h"
#include <conio.h>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;


/// Copy elements in arrFrom to arrTo.
void copyArray(int* arrTo, int* arrFrom, unsigned int length)
{
	for (unsigned int i = 0; i < length; i++)
	{
		arrTo[i] = arrFrom[i];
	}
}

/// Prints the int array to a file.
void PrintIntArrToFile(int* intArr, unsigned int length, string fileName)
{
	try
	{
		ofstream outFile; // the file to print to
		outFile.open(fileName, ios_base::trunc);

		// put each int in
		for (int i = 0; i < length; i++)
		{
			outFile << intArr[i] << endl;
		}
		outFile.close();
	}
	catch (...){}
}

int main()
{
	const unsigned int LENGTH = 100000; // amount of elements in array
	cout << "Sorting " << LENGTH << " integers with different algorithms." << endl << endl;

	const string eMergeFileName = "EMerge.txt";

	ofstream eMergeFile; // the file to use external merge sort on

	int* intArr = new int[LENGTH];// the int array
	int* tempArr = new int [LENGTH]; // copy array to keep original value
	try
	{
		eMergeFile.open(eMergeFileName, ios_base::trunc);
		// randomizing the int array, 0 to 32767
		for (unsigned int i = 0; i < LENGTH; i++)
		{
			intArr[i] = rand() % 32768;
			eMergeFile << intArr[i] << " Line:" << i << endl;
		}
	}
	catch (...)
	{
		cout << "An error has occured. Exiting.";
	}

	// variables for timing
	float start;
	float duration;
	
	// set temp array to value of original
	copyArray(tempArr, intArr, LENGTH);
	cout << "Bubble Sort: ";
	// start timer
	start = clock(); 
	Sorting::bubbleSortInt(tempArr, LENGTH); // do bubble sort
	duration = (clock() - start) / CLOCKS_PER_SEC; // finish timer
	cout << duration << " seconds" << endl;// print time
	// print temp arr to file
	PrintIntArrToFile(tempArr, LENGTH, "BubbleSort.txt");
	

	
	// set temp array to value of original
	copyArray(tempArr, intArr, LENGTH);
	cout << "Selection Sort: ";
	// start timer
	start = clock();
	Sorting::selectionSortInt(tempArr, LENGTH); // do selection sort
	duration = (clock() - start) / CLOCKS_PER_SEC; // finish timer
	cout << duration << " seconds" << endl;// print time
	// print temp arr to file
	PrintIntArrToFile(tempArr, LENGTH, "SelectionSort.txt");
	

	
	// set temp array to value of original
	copyArray(tempArr, intArr, LENGTH);
	cout << "Insertion Sort: ";
	// start timer
	start = clock();
	Sorting::insertionSortInt(tempArr, LENGTH); // do insertion sort
	duration = (clock() - start) / CLOCKS_PER_SEC; // finish timer
	cout << duration << " seconds" << endl;// print time
	// print temp arr to file
	PrintIntArrToFile(tempArr, LENGTH, "InsertionSort.txt");
	

	
	// set temp array to value of original
	copyArray(tempArr, intArr, LENGTH);
	cout << "Shell Sort: ";
	// start timer
	start = clock();
	Sorting::shellSortInt(tempArr, LENGTH); // do shell sort
	duration = (clock() - start) / CLOCKS_PER_SEC; // finish timer
	cout << duration << " seconds" << endl;// print time
	// print temp arr to file
	PrintIntArrToFile(tempArr, LENGTH, "ShellSort.txt");
	

	// set temp array to value of original
	copyArray(tempArr, intArr, LENGTH);
	cout << "Merge Sort: ";
	// start timer
	start = clock();
	Sorting::mergeSortInt(tempArr, LENGTH); // do merge sort
	duration = (clock() - start) / CLOCKS_PER_SEC; // finish timer
	cout << duration << " seconds" << endl;// print time
	// print temp arr to file
	PrintIntArrToFile(tempArr, LENGTH, "MergeSort.txt");

	
	// set temp array to value of original
	copyArray(tempArr, intArr, LENGTH);
	cout << "Quick Sort: ";
	// start timer
	start = clock();
	Sorting::quickSortInt(tempArr, LENGTH); // do quick sort
	duration = (clock() - start) / CLOCKS_PER_SEC; // finish timer
	cout << duration << " seconds" << endl;// print time
	// print temp arr to file
	PrintIntArrToFile(tempArr, LENGTH, "QuickSort.txt");

	cout << "External Merge Sort: ";
	// start timer
	start = clock();
	Sorting::stableExternalMergeSort(eMergeFileName, "sorted"+eMergeFileName, LENGTH, 1000); // do external merge sort
	duration = (clock() - start) / CLOCKS_PER_SEC; // finish timer
	cout << duration << " seconds" << endl;// print time
	

	delete[] intArr;

	cout << "Press any key to quit.";
	_getch();
}