#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include <math.h>
#include <string.h>

#define NUMBER_OF_TESTS 100

void swap(int *array, int firstElementIndex, int secondElementIndex);

void show(int *array);


void check(int *array);

void quickSort(int *array);

void quickSortDivider(int *array, int startIndex, int endIndex);

unsigned int arraySize;

int main(void) {

    arraySize = 9;
    int *array = malloc(sizeof(int) * arraySize);
    array[0] = 1;
    array[1] = 7;
    array[2] = 3;
    array[3] = 5;
    array[4] = 8;
    array[5] = 2;
    array[6] = 3;
    array[7] = 1;
    array[8] = 7;
    quickSort(array);
    show(array);
}


/*
 *
 *  Quick Sort
 *
 *
 */

void quickSort(int *array) {

    quickSortDivider(array, 0, arraySize - 1);

}

void quickSortDivider(int *array, int startIndex, int endIndex) {

    if (startIndex >= endIndex) return;
    int pivotIndex = rand() % (endIndex + 1 - startIndex) + startIndex;
    int pivotValue = array[pivotIndex];
    int leftSearchIndex = startIndex;
    int rightSearchIndex = endIndex;

    while (leftSearchIndex <= rightSearchIndex) {
        while (array[leftSearchIndex] < pivotValue) {
            leftSearchIndex++;
        }


        while (array[rightSearchIndex] > pivotValue) {
            rightSearchIndex--;
        }


        if (leftSearchIndex <= rightSearchIndex) {
            swap(array, leftSearchIndex, rightSearchIndex);
            if (leftSearchIndex == pivotIndex) {
                pivotIndex = rightSearchIndex;
            } else if (rightSearchIndex == pivotIndex) {
                pivotIndex = leftSearchIndex;
            }
            leftSearchIndex++;
            rightSearchIndex--;
        }
    }

    if (rightSearchIndex > startIndex) quickSortDivider(array, startIndex, rightSearchIndex);
    if (leftSearchIndex < endIndex) quickSortDivider(array, leftSearchIndex, endIndex);

}

/*
 *
 *  Utilities
 *
 *
 */

void swap(int *array, int firstElementIndex, int secondElementIndex) {
    int tmp = array[secondElementIndex];
    array[secondElementIndex] = array[firstElementIndex];
    array[firstElementIndex] = tmp;
}

void show(int *array) {
    for (int i = 0; i < arraySize; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
}

void check(int *array) {
    for (int i = 0; i < arraySize - 1; i++) {
        if (array[i] > array[i + 1]) {
            printf("Check FAILED!\n");
            return;
        }
    }
    printf("Check PASSED!\n");
}
