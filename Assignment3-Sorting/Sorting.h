//  File: Sorting.h
//	Purpose: Header file for Sorting.cpp
//  Project: Assignment3-Sorting
//  Author: Ryan Amaral
//  Created On: February 22, 2016

#ifndef _SORTING_H
#define _SORTING_H

#include <string>

class Sorting
{
private:
	static void innerMergeSortInt(int* intArr, int* sortIntArr, unsigned int length); // merge sort for integers
	static bool innerStableExternalMergeSort(std::ifstream& mergeFileIn, std::ofstream& mergeFileOut,
		int* intArr, std::string* indexArr,
		int sectors, int sectorSize, int lastSectorSize, int entitiesAtOnce,
		bool swappy, long* sectorStartPositions); // the recursive part of the external merge sort

	static std::string tmpMergeFile1;
	static std::string tmpMergeFile2;
public:
	static bool compare(int int1, int int2, bool greater); // check how first compares to second
	static void bubbleSortInt(int* intArr, unsigned int length); // bubble sort for integers
	static void selectionSortInt(int* intArr, unsigned int length); // selection sort for integers
	static void insertionSortInt(int* intArr, unsigned int length); // insertion sort for integers
	static void shellSortInt(int* intArr, unsigned int length); // shell sort for integers
	static void mergeSortInt(int* intArr, unsigned int length); // merge sort for integers
	static void quickSortInt(int* intArr, unsigned int length); // quick sort for integers
	static void stableExternalMergeSort(std::string inFileName, std::string outFileName, int entities, int entitiesAtOnce); // uses external merge sort on contents of file
	static void quickSortIntIndexed(int* intArr, std::string* stringArr, unsigned int length); // quick sort for integers with string index
};

#endif