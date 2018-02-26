#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#define NUMBER_OF_TESTS 10

int maxNumberOfDigits;
int logEnabled;
int randOrder;
int arraySize;
int graphGenerating;

int operationsCounter;

void calculateConstants();

void show(int *);

void sshow(int *array, int size);

void check(int *);

void swap(int *array, int firstElementIndex, int secondElementIndex);

void quickSort(int *array);

void quickSortDivider(int *array, int startIndex, int endIndex);

void quickSortMM(int *array);

void quickSortDividerMM(int *array, int startIndex, int endIndex);

void selectPivot(int *array, int startIndex, int endIndex);

int medianDistanceFromBeginning(int number);

void shuffle(int *array, size_t n);

int *generateArray(int thisArraySize);

void generateDataFile();

void insertionSort(int *array, int startIndex, int endIndex);

int main(int argc, char *argv[]) {
//
//    int* array = generateArray(20);
//    quickSortMM(array);
//    check(array);
   generateDataFile();

    return 0;


}

void calculateConstants() {
    int numberOfDigits = 0;
    for (int number = arraySize; number > 0; number /= 10, numberOfDigits++);
    maxNumberOfDigits = numberOfDigits;
    operationsCounter = 0;
}

void show(int *array) {
    for (int i = 0; i < arraySize; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void sshow(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void check(int *array) {
    for (int i = 1; i < arraySize; i++) {
        if (array[i - 1] > array[i]) {
            printf("\n%d %d %d %d\n", array[i - 1], array[i], i - 1, i);
            printf("\nTEST FAILED!");
            return;
        }
    }
    printf("\nTEST PASSED!");
}
/*
 *
 * QuickSort with Median of Medians
 *
 */

void quickSortMM(int *array) {
    quickSortDividerMM(array, 0, arraySize - 1);
}

void quickSortDividerMM(int *array, int startIndex, int endIndex) {

    if (startIndex >= endIndex) return;

    selectPivot(array, startIndex, endIndex);

    int pivotValue = array[startIndex];

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
            operationsCounter++;
            leftSearchIndex++;
            rightSearchIndex--;
        }
    }

    if (rightSearchIndex > startIndex) quickSortDividerMM(array, startIndex, rightSearchIndex);
    if (leftSearchIndex < endIndex) quickSortDividerMM(array, leftSearchIndex, endIndex);

}

void selectPivot(int *array, int startIndex, int endIndex) {
    int arraySize = endIndex - startIndex + 1;
    int numberOfGroups;
    numberOfGroups = ((arraySize % 5) ? arraySize / 5 + 1 : arraySize / 5);


    while (arraySize > 5) {

        int sizeOfLastGroup = (arraySize % 5) ? arraySize % 5 : 5;

        for (int i = 0; i < numberOfGroups - 1; i++) {
            insertionSort(array, (i * 5) + startIndex, ((i + 1) * 5 - 1) + startIndex);
        }

        //Last group:
        insertionSort(array, ((numberOfGroups - 1) * 5) + startIndex,
                      ((numberOfGroups) * 5 - 1 - (5 - sizeOfLastGroup)) + startIndex);

        for (int i = 0; i < numberOfGroups - 1; i++) {
            swap(array, i + startIndex, (5 * i + 2) + startIndex);
        }

        //Last group:
        swap(array, (numberOfGroups - 1) + startIndex,
             (5 * (numberOfGroups - 1) + medianDistanceFromBeginning(sizeOfLastGroup)) + startIndex);

        arraySize = numberOfGroups;

        numberOfGroups = ((arraySize % 5) ? arraySize / 5 + 1 : arraySize / 5);

    }

    insertionSort(array, 0 + startIndex, (arraySize - 1) + startIndex);

    swap(array, 0 + startIndex, (medianDistanceFromBeginning(arraySize)) + startIndex);
}

int medianDistanceFromBeginning(int number) {
    if (number == 1 || number == 2) return 0;
    else if (number == 3 || number == 4) return 1;
    else return 2;
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

//    int pivotIndex = rand() % (endIndex + 1 - startIndex) + startIndex;

    int pivotIndex = startIndex;

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
            operationsCounter++;
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

void generateDataFile() {

    unsigned long long operationsSum = 0;
    int operationsMax = 0;
    int operationsMin = INT_MAX;


    int *array;
    int maxArraySize;

    printf("Generating stats for quickSort (random pivot).\n");

    FILE* f = fopen("qs_rand_100_100000.txt", "w");
    FILE* min = fopen("qs_rand_100_100000_min.txt", "w");
    FILE* max = fopen("qs_rand_100_100000_max.txt", "w");

    maxArraySize = 100000;
    for (int i = 100; i < maxArraySize; i += 100) {
        arraySize = i;
        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            array = generateArray(i);

            operationsCounter = 0;
            quickSort(array);
            free(array);

            operationsSum += operationsCounter;
            if(operationsCounter > operationsMax) operationsMax = operationsCounter;
            if(operationsCounter < operationsMin) operationsMin = operationsCounter;
        }

        printf("%d / %d\n", i, maxArraySize);
        fprintf(f, "%d %llu\n", i, operationsSum / NUMBER_OF_TESTS);
        fprintf(min, "%d %llu\n", i, operationsMin);
        fprintf(max, "%d %llu\n", i, operationsMax);
        operationsMax = 0;
        operationsMin = INT_MAX;
        operationsSum = 0;
        operationsCounter = 0;
    }

    fclose(f);
    fclose(min);
    fclose(max);

    printf("Generating stats for quickSort (median of medians).\n");

    f = fopen("qs_mm_100_100000.txt", "w");
    min = fopen("qs_mm_100_100000_min.txt", "w");
    max = fopen("qs_mm_100_100000_max.txt", "w");

    maxArraySize = 100000;
    for (int i = 100; i < maxArraySize; i += 100) {
        arraySize = i;
        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            array = generateArray(i);

            operationsCounter = 0;
            quickSortMM(array);
            free(array);

            operationsSum += operationsCounter;
            if(operationsCounter > operationsMax) operationsMax = operationsCounter;
            if(operationsCounter < operationsMin) operationsMin = operationsCounter;
        }

        printf("%d / %d\n", i, maxArraySize);
        fprintf(f, "%d %llu\n", i, operationsSum / NUMBER_OF_TESTS);
        fprintf(min, "%d %llu\n", i, operationsMin);
        fprintf(max, "%d %llu\n", i, operationsMax);
        operationsMax = 0;
        operationsMin = INT_MAX;
        operationsSum = 0;
        operationsCounter = 0;
    }

    fclose(f);
    fclose(min);
    fclose(max);



}

int *generateArray(int thisArraySize) {

    int *array = malloc(sizeof(int) * thisArraySize);

    if (randOrder) {
        for (int i = 0; i < thisArraySize; i++) {
            array[i] = rand() % thisArraySize;
        }
    } else {
        for (int i = 0; i < thisArraySize; i++) {
            array[i] = i + 1;

        }
        shuffle(array, thisArraySize);
    }

    return array;
}

void shuffle(int *array, size_t n) {
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void insertionSort(int *array, int startIndex, int endIndex) {
    for (int i = startIndex + 1; i < endIndex + 1; i++) {
        for (int j = i - 1; j >= startIndex; j--) {
            if (array[j] > array[j + 1]) {
                swap(array, j, j + 1);
            } else break;
        }
    }
}
