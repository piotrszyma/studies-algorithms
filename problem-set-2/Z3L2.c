#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "utilities.h"

#define NUMBER_OF_TESTS 50
#define ARRAY_SIZE 100000
#define ORDER_TYPE 1

int comparisonCounter;

int swapCounter;

void dualPivotQuickSort(int *array);

void dualPivotQuickSortRecursion(int *array, int startIndex, int endIndex);

void insertionSortImproved(int *array, int startIndex, int endIndex);

void quickSort(int *array);

void quickSortDivider(int *array, int startIndex, int endIndex);

float countTime(void (*algorithm)(int *));

int main(void) {

    printf("\n---\n");
    printf("dualPivotQS:\t%0.5f [us]\n", countTime(dualPivotQuickSort));
    printf("standardQS:\t%0.5f [us]\n\n", countTime(quickSort));
    printf("---\n");


    return 0;
}



//DUAL PIVOT



void dualPivotQuickSort(int *array) {
    dualPivotQuickSortRecursion(array, 0, ARRAY_SIZE - 1);
}

void dualPivotQuickSortRecursion(int *array, int leftIndex, int rightIndex) {
//    if(leftIndex > rightIndex) return;
    if(rightIndex - leftIndex < 24) {
        insertionSortImproved(array, leftIndex, rightIndex);
        return;
    }

    int leftValue = array[leftIndex];
    int rightValue = array[rightIndex];
    int firstPointer = leftIndex + 1;
    int secondPointer = firstPointer;
    int thirdPointer = rightIndex - 1;

    while (secondPointer < thirdPointer) {
        if (array[secondPointer] < leftValue) {
            swap(array, firstPointer, secondPointer);
            firstPointer++;
        } else if (array[secondPointer] >= rightValue) {

            while (array[thirdPointer] > rightValue && secondPointer < thirdPointer) {
                thirdPointer--;
            }

            swap(array, secondPointer, thirdPointer);
            thirdPointer--;

            if (array[secondPointer] < leftValue) {
                swap(array, secondPointer, firstPointer);
                firstPointer++;
            }
        }

        secondPointer++;
    }

    firstPointer--;
    thirdPointer++;
    swap(array, leftIndex, firstPointer);
    swap(array, rightIndex, thirdPointer);
    dualPivotQuickSortRecursion(array, leftIndex, firstPointer - 1);
    dualPivotQuickSortRecursion(array, firstPointer + 1, thirdPointer - 1);
    dualPivotQuickSortRecursion(array, thirdPointer + 1, rightIndex);
    return;

}



//QSORT



void quickSort(int *array) {
    swapCounter = 0;
    comparisonCounter = 0;
    quickSortDivider(array, 0, ARRAY_SIZE - 1);
}

void quickSortDivider(int *array, int startIndex, int endIndex) {

    if (startIndex >= endIndex) return;
    int pivotValue = array[(startIndex + endIndex) / 2];
    int leftSearchIndex = startIndex;
    int rightSearchIndex = endIndex;

    while (leftSearchIndex <= rightSearchIndex) {

        while (array[leftSearchIndex] < pivotValue) {
            leftSearchIndex++;
        }

        while (array[rightSearchIndex] > pivotValue) {
            rightSearchIndex--;
        }

        comparisonCounter++;
        if (leftSearchIndex <= rightSearchIndex) {
            swap(array, leftSearchIndex, rightSearchIndex);
            leftSearchIndex++;
            rightSearchIndex--;
        }
    }
    if (rightSearchIndex > startIndex) quickSortDivider(array, startIndex, rightSearchIndex);
    if (leftSearchIndex < endIndex) quickSortDivider(array, leftSearchIndex, endIndex);

}

//INSERTION SORT

void insertionSortImproved(int *array, int startIndex, int endIndex) {
    for (int i = startIndex; i <= endIndex; i++) {
        for (int j = i - 1; j >= startIndex; j--) {
            if (array[j] > array[j + 1]) {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            } else break;
        }
    }
}


//UTILITIES



int *generateArray(int size, int orderType) {

    int *array = malloc(sizeof(int) * (size + 1));
    srand(time(NULL));
    if (orderType == 1) {
        int i = 0;
        while (i < (size + 1)) {
            array[i++] = rand() % 1000;
        }
        array[i] = '\n';
    } else {
        int i = 0;
        while (i < (size + 1)) {
            array[i++] = size - i;
        }
        array[i] = '\n';

    }

    return array;
}

float countTime(void (*algorithm)(int *)) {

    struct timeval start, end;

    float timeSum = 0;

    int *array = malloc(sizeof(int) * (ARRAY_SIZE + 1));
    srand(time(NULL));
    for (int i = 0; i < NUMBER_OF_TESTS; i++) {

        array = generateArray(ARRAY_SIZE, ORDER_TYPE);

        gettimeofday(&start, NULL);
        (*algorithm)(array);
        gettimeofday(&end, NULL);

        timeSum += ((float) ((end.tv_sec * 1000000 + end.tv_usec)
                             - (start.tv_sec * 1000000 + start.tv_usec)));
    }
    free(array);
    return timeSum / NUMBER_OF_TESTS;
}