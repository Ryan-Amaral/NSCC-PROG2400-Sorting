//  File: Sorting.cpp
//	Purpose: Contains various sorting algorithms.
//  Project: Assignment3-Sorting
//  Author: Ryan Amaral
//  Created On: February 22, 2016

#include "Sorting.h"
#include <math.h>
#include <fstream>
#include <sstream>

/// Put comparisons into single function to make switch from ascending to descending easier.
bool Sorting::compare(int int1, int int2, bool isGreater)
{
	if (isGreater)
	{
		return int1 > int2;
	}
	else
	{
		return int1 < int2;
	}
}

/// Bubble sort on an int array.
void Sorting::bubbleSortInt(int* intArr, unsigned int length)
{
	int temp; // temp swapping space
	// amount of iterations through array
	for (unsigned int i = 0; i < length - 1; i++)
	{
		// element to swap at
		for (unsigned int j = 0; j < length - 1 - i; j++)
		{
			// if true swap
			if (intArr[j] > intArr[j + 1])
			{
				temp = intArr[j];
				intArr[j] = intArr[j + 1];
				intArr[j + 1] = temp;
			}
		}
	}
}

/// Selection sort on an int array.
void Sorting::selectionSortInt(int* intArr, unsigned int length)
{
	int curMin; // the cur minimum (treated as max if !isAcending)
	unsigned int curMinIndex; // the index of the cur min
	// look at each element except last
	for (unsigned int i = 0; i < length - 1; i++)
	{
		// go through all elements after i to see which is lowest
		for (unsigned int j = i; j < length; j++)
		{
			// first is auto min
			if (j == i)
			{
				curMin = intArr[j];
				curMinIndex = j;
			}
			else
			{
				if (intArr[j] < curMin)
				{
					curMin = intArr[j];
					curMinIndex = j;
				}
			}
		}

		// swap i with curMinIndex
		intArr[curMinIndex] = intArr[i];
		intArr[i] = curMin;
	}
}

/// Insertion sort on an int array.
void Sorting::insertionSortInt(int* intArr, unsigned int length)
{
	int temp; // temp swapping space
	unsigned int insertIndex; // index to put next number in
	// look at each element after first
	// skip first because we can count that as start of sorted portion
	for (unsigned int i = 1; i < length; i++)
	{
		temp = intArr[i];
		insertIndex = i; // change nothing if insert index stays i
		// check where temp gets inserted
		for (unsigned int j = 0; j < i; j++)
		{
			if (temp < intArr[j])
			{
				insertIndex = j;
				break;
			}
		}

		// move elements after insert index forward, starting from last
		for (unsigned int j = i; j > insertIndex; j--)
		{
			intArr[j] = intArr[j - 1];
		}

		// set the insert index to temp
		intArr[insertIndex] = temp;
	}
}

/// Shell sort on an int array.
void Sorting::shellSortInt(int* intArr, unsigned int length)
{
	int temp; // temp swapping space
	// do shell sort for each interval starting from half rounded down to one
	for (unsigned int i = length / 2; i > 0; i /= 2)
	{
		for (unsigned int j = 0; j < length - i; j++)
		{
			for (int k = j; k >= 0; k -= i)
			{
				if (intArr[k] > intArr[k + i])
				{
					temp = intArr[k];
					intArr[k] = intArr[k + i];
					intArr[k + i] = temp;
				}
				else
				{
					break;
				}
			}
		}
	}

	// insertion sort the rest
	//insertionSortInt(intArr, length);
}

/// Merge sort on an int array, don't create new array.
void Sorting::innerMergeSortInt(int* intArr, int* sortIntArr, unsigned int length)
{
	int regSize = length / 2; // get the standard size of each half
	int rExtra = length % 2; // extra length on right side
	if (length > 1)
	{
		innerMergeSortInt(intArr, sortIntArr, regSize); // merge sort left side
		innerMergeSortInt(&intArr[regSize], &sortIntArr[regSize], regSize + rExtra); // merge sort right side
	}

	// how far we are in to each half
	int lIndex = 0;
	int rIndex = regSize;

	// join left and right together in order
	// from intArr to sortIntArr
	for (int i = 0; i < length; i++)
	{
		// still left and right left
		if (lIndex < regSize && rIndex < ((2 * regSize) + rExtra))
		{
			if (intArr[lIndex] < intArr[rIndex])
			{
				sortIntArr[i] = intArr[lIndex];
				lIndex++;
			}
			else
			{
				sortIntArr[i] = intArr[rIndex];
				rIndex++;
			}
		}
		// right is gone
		else if (lIndex < regSize)
		{
			sortIntArr[i] = intArr[lIndex];
			lIndex++;
		}
		// left is gone
		else
		{
			sortIntArr[i] = intArr[rIndex];
			rIndex++;
		}
	}

	// write sortIntArr back to intArr
	for (int i = 0; i < length; i++)
	{
		intArr[i] = sortIntArr[i];
	}
}

/// Merge sort on an int array.
void Sorting::mergeSortInt(int* intArr, unsigned int length)
{
	int* sortIntArr = new int[length]; // need this for extra space to do sort
	innerMergeSortInt(intArr, sortIntArr, length); // start the merger chain
	delete[] sortIntArr; // delete the extra
}

/// Quick sort on an int array.
void Sorting::quickSortInt(int* intArr, unsigned int length)
{
	int pivot = intArr[0]; // pivot is always last element
	unsigned int pivotIndex = 0;
	// giter all split by partition
	for (unsigned int i = 1; i < length; i++)
	{
		// if element is less than pivot, insert in far left
		if (intArr[i] < pivot)
		{
			intArr[pivotIndex] = intArr[i];
			intArr[i] = intArr[pivotIndex + 1];
			intArr[pivotIndex + 1] = pivot;
			pivotIndex++;
		}
	}

	// quick sort left side
	if (pivotIndex > 0)
	{
		quickSortInt(&intArr[0], pivotIndex);
	}
	// quick sort right side
	if (pivotIndex < length - 1)
	{
		quickSortInt(&intArr[pivotIndex + 1], length - pivotIndex - 1);
	}
}

std::string Sorting::tmpMergeFile1 = "tmpMergeFile1";
std::string Sorting::tmpMergeFile2 = "tmpMergeFile2";

/// Takes a file that has number and index by it and stable sort it.
void Sorting::stableExternalMergeSort(std::string inFileName, std::string outFileName, int entities, int entitiesAtOnce)
{
	std::ifstream* mergeFileIn = new std::ifstream; // will originally be used to take in original values
	std::ofstream* mergeFileOut = new std::ofstream;

	bool isSecondFiles = true; // bool for what pair to write from in the end

	if (entitiesAtOnce > entities)
	{
		entitiesAtOnce = entities;
	}

	// arrays to store data from file
	int* intArr = new int[entitiesAtOnce];
	std::string* stringArr = new std::string[entitiesAtOnce];

	// each entitiesAtOnce entities gets sorted and put in out files
	int sectors = std::ceil((float)entities / (float)entitiesAtOnce);
	long* sectorStartPositions = new long[sectors / 2]; // the starting position in the file of every second sector
	int lastSectorLength = entities % entitiesAtOnce; // last sector could be different
	if (lastSectorLength == 0)
	{
		lastSectorLength = entitiesAtOnce;
	}

	try
	{
		mergeFileIn->open(inFileName, std::fstream::in); // intFileIn originally used to get all values
		// temp names for other files
		mergeFileOut->open(tmpMergeFile2, std::fstream::trunc);

		int curLength;
		std::stringstream curLineStream;
		std::string curLine;

		// sort each sector and put it into out files
		for (int i = 0; i < sectors; i++)
		{
			// set proper length of last sector
			if (i == sectors - 1)
			{
				curLength = lastSectorLength;
			}
			else
			{
				curLength = entitiesAtOnce;
			}

			for (int j = 0; j < curLength; j++)
			{
				std::getline(*mergeFileIn, curLine);
				curLineStream << curLine;
				curLineStream >> intArr[j] >> stringArr[j];
				curLineStream.clear();
			}

			// sort the data
			// not stable switch to merge
			quickSortIntIndexed(intArr, stringArr, curLength);

			if ((i + 1) % 2 == 0)
			{
				sectorStartPositions[i / 2] = mergeFileOut->tellp();
			}

			// write data to file
			for (int j = 0; j < curLength; j++)
			{
				*mergeFileOut << intArr[j] << " " << stringArr[j] << std::endl;
			}
		}

		mergeFileIn->close();
		mergeFileOut->close();

		// now call the recursive part
		if (sectors > 1)
		{
			isSecondFiles = !innerStableExternalMergeSort(*mergeFileIn, *mergeFileOut,
				intArr, stringArr, sectors, entitiesAtOnce, lastSectorLength, entitiesAtOnce, true, sectorStartPositions);
		}

		int j = 0; // to index through int and string arrs
		int kMax = entitiesAtOnce;

		// write to output file from proper input file
		if (isSecondFiles)
		{
			// use intFile1 output, intFile2 as input
			mergeFileIn->open(tmpMergeFile2, std::ifstream::in);

			// open outFileName to put final sorted output
			mergeFileOut->open(outFileName, std::ofstream::trunc);

			// read from files 2
			for (int i = 0; i < entities; i++)
			{
				std::getline(*mergeFileIn, curLine);
				curLineStream << curLine;
				curLineStream >> intArr[j] >> stringArr[j];
				curLineStream.clear();

				j++;
				if (i > 0 && j > 0)
				{
					if (j % entitiesAtOnce == 0 || i == entities - 1)
					{
						if (i == entities - 1)
						{
							if (j % entitiesAtOnce != 0)
							{
								kMax = entities % entitiesAtOnce;
							}
						}

						j = 0;

						// write existing data from arrs to file
						for (int k = 0; k < kMax; k++)
						{
							*mergeFileOut << intArr[k] << " " << stringArr[k] << std::endl;
						}
					}
				}
			}
		}
		else
		{
			// use intFile2 output, intFile1 as input
			mergeFileIn->open(tmpMergeFile1, std::ifstream::in);

			// open outFileName to put final sorted output
			mergeFileOut->open(outFileName, std::ofstream::trunc);

			// read from files 1
			for (int i = 0; i < entities; i++)
			{
				std::getline(*mergeFileIn, curLine);
				curLineStream << curLine;
				curLineStream >> intArr[j] >> stringArr[j];
				curLineStream.clear();

				j++;
				if (i > 0 && j > 0)
				{
					if (j % entitiesAtOnce == 0 || i == entities - 1)
					{
						if (i == entities - 1)
						{
							if (j % entitiesAtOnce != 0)
							{
								kMax = entities % entitiesAtOnce;
							}
						}

						j = 0;

						// write existing data from arrs to file
						for (int k = 0; k < kMax; k++)
						{
							*mergeFileOut << intArr[k] << " " << stringArr[k] << std::endl;
						}
					}
				}
			}
		}

		// close all fstreams
		mergeFileIn->close();
		mergeFileOut->close();

		delete mergeFileIn;
		delete mergeFileOut;
		delete[] intArr;
		delete[] stringArr;
	}
	catch (std::ios_base::failure e)
	{
		return; // something wrong with file
	}
	catch (std::exception e)
	{
		return; // something wrong with file
	}
}

bool Sorting::innerStableExternalMergeSort(std::ifstream& mergeFileIn, std::ofstream& mergeFileOut,
	int* intArr, std::string* indexArr,
	int sectors, int sectorSize, int lastSectorSize, int entitiesAtOnce,
	bool swappy, long* sectorStartPositions)
{
	if (swappy)
	{
		mergeFileIn.open(tmpMergeFile2, std::ifstream::in);
		mergeFileOut.open(tmpMergeFile1, std::ofstream::trunc);
	}
	else
	{
		mergeFileIn.open(tmpMergeFile1, std::ifstream::in);
		mergeFileOut.open(tmpMergeFile2, std::ofstream::trunc);
	}

	int tempInt;
	std::string tempIndex;

	// when reaches mergeHalfSize - 1, or entitiesAtOnce, reset
	int curElementAtRam[2]; // the element for each side of merge

	int curElementAtFile[2]; // the element in the current file (sector)
	long intFilePos[2]; // the current position in each side of merge in the file

	int totalUsedInSector[2]; // the amount of elements used in each sector

	int mergeHalfSize = entitiesAtOnce / 2;

	bool leftRamDone; // tells if left side of merge is done
	bool rightRamDone; // tells if right side of merge is done
	bool leftSectorDone; // tells if left side of merge is done
	bool rightSectorDone; // tells if right side of merge is done

	std::string lineContent;
	std::stringstream curLineStream;

	int curNum;
	std::string curIndex;

	bool rightSideShorter = (lastSectorSize != sectorSize);
	int rightSideEntitiesAtOnce = mergeHalfSize;
	int rightSideMax = sectorSize;

	int mergeTotalSize;

	// merge each two pairs
	for (int i = 1; i < sectors; i += 2)
	{
		// i-1 and i

		// fill in first part of first side of merge
		for (int j = 0; j < mergeHalfSize; j++)
		{
			// get int
			std::getline(mergeFileIn, lineContent);
			curLineStream << lineContent;
			curLineStream >> intArr[j] >> indexArr[j];
			curLineStream.clear();
		}
		curElementAtFile[0] = mergeHalfSize;
		intFilePos[0] = mergeFileIn.tellg();

		if (i == sectors - 1)
		{
			if (lastSectorSize < mergeHalfSize)
			{
				rightSideEntitiesAtOnce = lastSectorSize;
			}
			rightSideMax = lastSectorSize;
		}

		// read past rest of untill at other sector
		/*for (int j = 0; j < sectorSize - mergeHalfSize; j++)
		{
			std::getline(mergeFileIn, lineContent);
		}*/
		// more efficient
		int h = mergeFileIn.tellg();
		mergeFileIn.seekg(sectorStartPositions[i / 2]);
		h = mergeFileIn.tellg();

		// fill in first part of second side
		for (int j = mergeHalfSize; j < mergeHalfSize + rightSideEntitiesAtOnce; j++)
		{
			// get int
			std::getline(mergeFileIn, lineContent);
			curLineStream << lineContent;
			curLineStream >> intArr[j] >> indexArr[j];
			curLineStream.clear();
		}
		curElementAtFile[1] = mergeHalfSize;
		intFilePos[1] = mergeFileIn.tellg();

		curElementAtRam[0] = 0;
		curElementAtRam[1] = mergeHalfSize;

		totalUsedInSector[0] = 0;
		totalUsedInSector[1] = 0;

		leftRamDone = false;
		rightRamDone = false;
		leftSectorDone = false;
		rightSectorDone = false;
		// merge the two sides
		for (int j = 0; j < sectorSize + rightSideMax; j++)
		{
			// compare sides
			// can't do left, so do right
			if (leftRamDone)
			{
				curNum = intArr[curElementAtRam[1]];
				curIndex = indexArr[curElementAtRam[1]];
				curElementAtRam[1]++;
				totalUsedInSector[1]++;
				if (totalUsedInSector[1] == rightSideMax)
				{
					rightRamDone = true;
				}
			}
			// can't do right, so do left
			else if (rightRamDone)
			{
				curNum = intArr[curElementAtRam[0]];
				curIndex = indexArr[curElementAtRam[0]];
				curElementAtRam[0]++;
				totalUsedInSector[0]++;
				if (totalUsedInSector[0] == sectorSize)
				{
					leftRamDone = true;
				}
			}
			// take left
			else if (intArr[curElementAtRam[0]] <= intArr[curElementAtRam[1]])
			{
				curNum = intArr[curElementAtRam[0]];
				curIndex = indexArr[curElementAtRam[0]];
				curElementAtRam[0]++;
				totalUsedInSector[0]++;
				if (totalUsedInSector[0] == sectorSize)
				{
					leftRamDone = true;
				}
			}
			// take right
			else if (intArr[curElementAtRam[0]] > intArr[curElementAtRam[1]])
			{
				curNum = intArr[curElementAtRam[1]];
				curIndex = indexArr[curElementAtRam[1]];
				curElementAtRam[1]++;
				totalUsedInSector[1]++;
				if (totalUsedInSector[1] == rightSideMax)
				{
					rightRamDone = true;
				}
			}

			// put num and index into out files
			mergeFileOut << curNum << " " << curIndex << std::endl;

			// refill left side if needed and can
			if (curElementAtRam[0] == mergeHalfSize && !leftSectorDone)
			{
				curElementAtRam[0] = 0; // set back to beggining

				// set files to right positions
				mergeFileIn.seekg(intFilePos[0]);
				
				// get new datas
				for (int k = 0; k < mergeHalfSize; k++)
				{
					// get int
					std::getline(mergeFileIn, lineContent);
					curLineStream << lineContent;
					curLineStream >> intArr[k] >> indexArr[k];
					curLineStream.clear();

					curElementAtFile[0]++;

					// break prematurely if at end of sector
					if (curElementAtFile[0] == sectorSize)
					{
						leftSectorDone = true;
						break;
					}
				}
				intFilePos[0] = mergeFileIn.tellg();
			}

			// refill right side if needed and can
			if (curElementAtRam[1] == mergeHalfSize + rightSideEntitiesAtOnce && !rightSectorDone)
			{
				curElementAtRam[1] = mergeHalfSize; // set back to beggining

				// set files to right positions
				mergeFileIn.seekg(intFilePos[1]);

				// get new datas
				for (int k = mergeHalfSize; k < mergeHalfSize + rightSideEntitiesAtOnce; k++)
				{
					// get int
					std::getline(mergeFileIn, lineContent);
					curLineStream << lineContent;
					curLineStream >> intArr[k] >> indexArr[k];
					curLineStream.clear();

					curElementAtFile[1]++;

					// break prematurely if at end of sector
					if (curElementAtFile[1] == rightSideMax)
					{
						rightSectorDone = true;
						break;
					}
				}
				intFilePos[1] = mergeFileIn.tellg();
			}
		}
		// seek files to end of right
		mergeFileIn.seekg(intFilePos[1]);

		// set start of new sector at end of out file
		if ((i + 1) % 4 != 0)
		{
			sectorStartPositions[i / 4] = mergeFileOut.tellp();
		}
	}

	// determine if last sector size needs to change
	if (sectors % 2 == 0)
	{
		lastSectorSize = sectorSize + lastSectorSize;
	}
	// write the last sector to file
	else
	{
		// seek to right part
		mergeFileIn.seekg(intFilePos[1]);

		for (int i = 0; i < lastSectorSize; i++)
		{
			// get int
			std::getline(mergeFileIn, lineContent);
			curLineStream << lineContent;
			curLineStream >> tempInt >> tempIndex;
			curLineStream.clear();

			// write to the files
			mergeFileOut << tempInt << " " << tempIndex << std::endl;
		}
	}

	// close all streams
	mergeFileIn.close();
	mergeFileOut.close();

	// determine weather to do this again
	sectors = std::ceil((float)sectors / (float)2);
	if (sectors > 1)
	{
		return !innerStableExternalMergeSort(mergeFileIn, mergeFileOut,
			intArr, indexArr, sectors, sectorSize * 2, lastSectorSize, entitiesAtOnce, !swappy, sectorStartPositions);
	}
	else
	{
		return true;
	}
}

/// Quick sort to be used in external merge sort.
void Sorting::quickSortIntIndexed(int* intArr, std::string* stringArr, unsigned int length)
{
	int pivot = intArr[0]; // pivot is always last element
	std::string pivotLineIndex = stringArr[0];
	unsigned int pivotIndex = 0;
	// giter all split by partition
	for (unsigned int i = 1; i < length; i++)
	{
		// if element is less than pivot, insert in far left
		if (intArr[i] < pivot)
		{
			intArr[pivotIndex] = intArr[i];
			stringArr[pivotIndex] = stringArr[i];

			intArr[i] = intArr[pivotIndex + 1];
			stringArr[i] = stringArr[pivotIndex + 1];

			intArr[pivotIndex + 1] = pivot;
			stringArr[pivotIndex + 1] = pivotLineIndex;

			pivotIndex++;
		}
	}

	// quick sort left side
	if (pivotIndex > 0)
	{
		quickSortIntIndexed(&intArr[0], &stringArr[0], pivotIndex);
	}
	// quick sort right side
	if (pivotIndex < length - 1)
	{
		quickSortIntIndexed(&intArr[pivotIndex + 1], &stringArr[pivotIndex + 1], length - pivotIndex - 1);
	}
}