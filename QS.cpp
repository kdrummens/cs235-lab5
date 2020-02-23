/*
* QS.cpp
*
*  Created on: May 1, 2014
*  Last Updated on: March 30, 2015
*/

#include "QS.h"
#include <vector>
using namespace std;

/*
* sortAll()
*
* Sorts elements of the array.  After this function is called, every
* element in the array is less than or equal its successor.
*
* Does nothing if the array is empty.
*/
void QS::sortAll() {
    if(arrayCounter == 0) {
        return;
    }
    else {
        quicksort(0, arrayCounter - 1);
    }
};

/*
* medianOfThree()
*
* The median of three pivot selection has two parts:
*
* 1) Calculates the middle index by averaging the given left and right indices:
*
* middle = (left + right)/2
*
* 2) Then bubble-sorts the values at the left, middle, and right indices.
*
* After this method is called, data[left] <= data[middle] <= data[right].
* The middle index will be returned.
*
* Returns -1 if the array is empty, if either of the given integers
* is out of bounds, or if the left index is not less than the right
* index.
*
* @param left
*         the left boundary for the subarray from which to find a pivot
* @param right
*         the right boundary for the subarray from which to find a pivot
* @return
*        the index of the pivot (middle index); -1 if provided with invalid input
*/
int QS::medianOfThree(int left, int right) {
    cout << "LEFT: " << left << " RIGHT: " << right << endl;
    if(arrayCounter == 0 || left < 0 || right > arrayCounter - 1 || right < left || right == 0) {
        return -1;
    }
    
    int middle = (left + right) / 2;
    
    int indices[] = { table[left], table[middle], table[right] };
    
    
    bool isSwap;
    do {
      isSwap = false;
      for(int i = 0; i < 2; i++) {
        if(indices[i] > indices[i+1]) {
          int tmp = indices[i];
          indices[i] = indices[i+1];
          indices[i+1] = tmp;
          isSwap = true;
        }
      }
    } while(isSwap);
    
    
    table[left] = indices[0];
    table[middle] = indices[1];
    table[right] = indices[2];
    
    return middle;
};




/*
* Partitions a subarray around a pivot value selected according to
* median-of-three pivot selection.  Because there are multiple ways to partition a list,
* we will follow the algorithm on page 611 of the course text when testing this function.
*
* The values which are smaller than the pivot should be placed to the left
* of the pivot; the values which are larger than the pivot should be placed
* to the right of the pivot.
*
* Returns -1 if the array is null, if either of the given integers is out of
* bounds, or if the first integer is not less than the second integer, or if the
* pivot is not within the sub-array designated by left and right.
*
* @param left
*         the left boundary for the subarray to partition
* @param right
*         the right boundary for the subarray to partition
* @param pivotIndex
*         the index of the pivot in the subarray
* @return
*        the pivot's ending index after the partition completes; -1 if
*         provided with bad input
*/
int QS::partition(int left, int right, int pivotIndex) {
    if(arrayCounter == 0 || left < 0 || right > arrayCounter - 1 || right < left || pivotIndex < left || pivotIndex > right) {
           return -1;
    }
    
    
    
    /*
    int pivot = table[pivotIndex];    // pivot
    int i = (left - 1);  // Index of smaller element
    
    for(int j = left; j < right; j++) {
          // If current element is smaller than or
          // equal to pivot
          if (table[j] <= pivot)
          {
              i++;    // increment index of smaller element
              swap(table[i], table[j]);
          }
      }
      swap(table[i + 1], table[right]);
      return (i + 1);
     */
    
    
    
    
    
    
    /*
    
    vector<int> leftArray;
    vector<int> rightArray;
    
    int i;
    int j;
    
    for(i = 0; i < (right - left); i++) {
        int val = table[left + i];
        if(val >= table[pivotIndex]) {
            rightArray.push_back(val);
        }
        else {
            leftArray.push_back(val);
        }
    }
    
    i = 0;
    for(j = 0; j < leftArray.size(); j++) {
        table[left + i] = leftArray.at(j);
        i++;
    }
    table[left + i] = table[pivotIndex];
    i++;
    for(j = 0; j < rightArray.size(); j++) {
        table[left + i] = rightArray.at(j);
        i++;
    }
    
    
    return left + ((int)leftArray.size());
    */
    
    
    
    swap(table[pivotIndex], table[left]);
    
    int up = left + 1;
    int down = right - 1;
    
    do {
        while((up != right - 1) && !(left < up)) {
            ++up;
        }
        while(left < down) {
            --down;
        }
        
        if(up < down) {
            swap(table[up], table[down]);
        }
    } while(up < down);
    
    swap(table[left], table[down]);
    
    return down;
     
     
};

/*
* Produces a comma delimited string representation of the array. For example: if my array
* looked like {5,7,2,9,0}, then the string to be returned would look like "5,7,2,9,0"
* with no trailing comma.  The number of cells included equals the number of values added.
* Do not include the entire array if the array has yet to be filled.
*
* Returns an empty string, if the array is NULL or empty.
*
* @return
*        the string representation of the current array
*/
string QS::getArray() const {
    string arr = "";
    
    if(table != 0) {
        for(int i = 0; i < arrayCounter; i++) {
            int *currentInt = &table[i];
            arr += to_string(*currentInt);
            if(i < arrayCounter - 1) {
                arr += ",";
            }
        }
    }
    return arr;
};

/*
* Returns the number of elements which have been added to the array.
*/
int QS::getSize() const {
    return arrayCounter;
};

/*
* Adds the given value to the end of the array starting at index 0.
* For example, the first time addToArray is called,
* the give value should be found at index 0.
* 2nd time, value should be found at index 1.
* 3rd, index 2, etc up to its max capacity.
*
* If the array is filled, do nothing.
* returns true if a value was added, false otherwise.
*/
bool QS::addToArray(int value) {
    if(arrayCounter >= tableSize) {
        return false;
    }
    else {
        table[arrayCounter] = value;
        arrayCounter++;
        return true;
    }
};

/*
* Dynamically allocates an array with the given capacity.
* If a previous array had been allocated, delete the previous array.
* Returns false if the given capacity is non-positive, true otherwise.
*
* @param
*        size of array
* @return
*        true if the array was created, false otherwise
*/
bool QS::createArray(int capacity) {
    if(capacity < 0) {
        return false;
    }
    else {
        if(table != 0 && table != NULL) {
            delete [] table;
            table = 0;
        }
        table = new int[capacity];
        tableSize = capacity;
        arrayCounter = 0;
        return true;
    }
};


void QS::quicksort(int first, int last) {
    if((last - first) < 1) {
        return;
    }
    int pivot = medianOfThree(first, last);
    pivot = partition(first, last, pivot);
    quicksort(first, pivot - 1);
    quicksort(pivot + 1, last);
}

/*
* Resets the array to an empty or NULL state.
*/
void QS::clear() {
    delete [] table;
    table = 0;
    arrayCounter = 0;
};
    

