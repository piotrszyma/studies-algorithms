#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUMBER_OF_TESTS 10

int maxNumberOfDigits;
int logEnabled;
int descOrder;
int arraySize;
int graphGenerating;

int counterSwaps;
int counterComparisons;

void calculateConstants();

void show(int *);

void sshow(int *array, int size);

void check(int *);

void swap(int *array, int firstElementIndex, int secondElementIndex);

void quickSort(int *array);

void quickSortDivider(int *array, int startIndex, int endIndex);

void insertionSort(int *array, int startIndex, int endIndex);

int select(int *array, int searchedIndex);

int selectRecursion(int *array, int startIndex, int endIndex, int searchedIndex);

int selectPartition(int *array, int startIndex, int endIndex);

void selectPivot(int *array, int, int);

int medianDistanceFromBeginning(int number);

void ishow(int* array, int startIndex, int endIndex);

int *watchedArray;

void checkArray(int *array);

int main(int argc, char *argv[]) {

    arraySize = 14;
    int *array = malloc(sizeof(int) * arraySize);
    array[0] = 9;
    array[1] = 9;
    array[2] = 4;
    array[3] = 3;
    array[4] = 2;
    array[5] = 1;
    array[6] = 6;
    array[7] = 5;
    array[8] = 5;
    array[9] = 3;
    array[10] = 8;
    array[11] = 3;
    array[12] = 4;
    array[13] = 10;


    srand(time(NULL));

    int lookedPosition = rand() % 14;

    printf("Value at searched position: %d\n", select(array, lookedPosition));
    quickSort(array);
    printf("Value at this position after quickSort: %d\n", array[lookedPosition]);


}

void calculateConstants() {
    int numberOfDigits = 0;
    for (int number = arraySize; number > 0; number /= 10, numberOfDigits++);
    maxNumberOfDigits = numberOfDigits;
    counterComparisons = 0;
    counterSwaps = 0;
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
 *  Select
 *
 *
 */

int select(int *array, int searchedIndex) {

    if (searchedIndex < 0 || searchedIndex > arraySize - 1) return -1;

    int *arrayCopy = malloc(arraySize * sizeof(int));

    memcpy(arrayCopy, array, arraySize * sizeof(int));

    int searchedIndexResult = selectRecursion(arrayCopy, 0, arraySize - 1, searchedIndex);

    free(arrayCopy);

    return searchedIndexResult;

}

int selectRecursion(int *array, int startIndex, int endIndex, int searchedIndex) {

    int pivotIndex = selectPartition(array, startIndex, endIndex);

    if (pivotIndex == searchedIndex) {
        return array[searchedIndex];
    } else if (pivotIndex < searchedIndex) {
        return selectRecursion(array, pivotIndex + 1, endIndex, searchedIndex);
    } else {
        return selectRecursion(array, startIndex, pivotIndex - 1, searchedIndex);
    }

}

int selectPartition(int *array, int startIndex, int endIndex) {


    if (startIndex == endIndex) return startIndex;



    selectPivot(array, startIndex, endIndex);

    int pivotIndex = startIndex + rand() % (endIndex - startIndex + 1);

    int pivotValue = array[pivotIndex];
    swap(array, pivotIndex, endIndex);

    int lastLessIndex = startIndex;
    for (int checkedIndex = startIndex; checkedIndex < endIndex; checkedIndex++) {
        if (array[checkedIndex] <= pivotValue) {
            swap(array, lastLessIndex, checkedIndex);
            lastLessIndex++;
        }
    }

    swap(array, lastLessIndex, endIndex);
    return lastLessIndex;
}

void selectPivot(int *array, int startIndex, int endIndex) {

    watchedArray = array;
    int arraySize = endIndex - startIndex + 1;
    int numberOfGroups;
    numberOfGroups = ((arraySize % 5) ? arraySize / 5 + 1 : arraySize / 5);


    while (arraySize > 5) {

        int sizeOfLastGroup = (arraySize % 5) ? arraySize % 5 : 5;

        for (int i = 0; i < numberOfGroups - 1; i++) {
            insertionSort(array, (i * 5) + startIndex, ((i + 1) * 5 - 1) + startIndex);
        }

        //Last group:
        insertionSort(array, ((numberOfGroups - 1) * 5) + startIndex, ((numberOfGroups) * 5 - 1 - (5 - sizeOfLastGroup)) + startIndex);

        for (int i = 0; i < numberOfGroups - 1; i++) {
            swap(array, i  + startIndex, (5 * i + 2) + startIndex);
        }

        //Last group:
        swap(array, (numberOfGroups - 1) + startIndex, (5 * (numberOfGroups - 1) + medianDistanceFromBeginning(sizeOfLastGroup)) + startIndex);

        arraySize = numberOfGroups;

        numberOfGroups = ((arraySize % 5) ? arraySize / 5 + 1 : arraySize / 5);

    }

    insertionSort(array, 0  + startIndex, (arraySize - 1) + startIndex);

    swap(array, 0  + startIndex, (medianDistanceFromBeginning(arraySize)) + startIndex);



    // number of arrays - if arrsize | 5 -> arrsize / 5, else arrsize / 5 + 1
//    int numberOfSubArrays = arraySize % 5 ? arraySize / 5 + 1 : arraySize / 5;
//    //insertion sort for all except last
//    for (int i = 0; i < numberOfSubArrays - 1; i++) {
//        insertionSort(array, 5 * i, 5 * (i + 1) - 1);
//    }
//    //if last not length 5 , sort only size of it
//    if (arraySize % 5) {
//        insertionSort(array, 5 * (numberOfSubArrays - 1), 5 * (numberOfSubArrays - 1) + (arraySize % 5 - 1));
//        //if last is length 5, insertion sort on all
//    } else {
//        insertionSort(array, 5 * (numberOfSubArrays - 1), 5 * ((numberOfSubArrays - 1) + 1) - 1);
//    }
//
//    show(array);
//    //generate array of medians
//    int *arrayOfMedians = malloc(sizeof(int) * numberOfSubArrays);
//
//    //fill array of medians (without last not full)
//    for (int i = 0; i < numberOfSubArrays - 1; i++) {
//        arrayOfMedians[i] = array[i * 5 + 2];
//    }
//    //if not full (5 elements long), fill not all
//    if (arraySize % 5) {
//        switch (arraySize % 5) {
//            case 1:
//            case 2:
//                arrayOfMedians[numberOfSubArrays - 1] = array[(numberOfSubArrays - 1) * 5];
//                break;
//            case 3:
//            case 4:
//                arrayOfMedians[numberOfSubArrays - 1] = array[(numberOfSubArrays - 1) * 5 + 1];
//                break;
//            default:
//                break;
//        }
//        //else fill
//    } else {
//        arrayOfMedians[numberOfSubArrays - 1] = array[(numberOfSubArrays - 1) * 5 + 2];
//    }
//
//    sshow(arrayOfMedians, numberOfSubArrays);
//            printf("%d", numberOfSubArrays % 5);
//    if (numberOfSubArrays > 5) {
//        return selectPivot(arrayOfMedians, numberOfSubArrays);
//    } else {
//        switch(numberOfSubArrays % 5) {
//            case 0:
//                return arrayOfMedians[2];
//            case 4:
//            case 3:
//                return arrayOfMedians[1];
//            case 2:
//            case 1:
//                return arrayOfMedians[2];
//            default:
//                break;
//        }
//    }
//
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
 * Insertion sort
 *
 *
 */

void insertionSort(int *array, int startIndex, int endIndex) {
    for (int i = startIndex + 1; i < endIndex + 1; i++) {
        for (int j = i - 1; j >= startIndex; j--) {
            if (array[j] > array[j + 1]) {
                swap(array, j, j + 1);
            } else break;
        }
    }
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

void checkArray(int *array) {
    for (int i = 0; i < arraySize; i++) {
        quickSort(array);
        if (select(array, i) != array[i]) {
            printf("BUG");
        }

    }
}

void ishow(int* array, int startIndex, int endIndex) {
    for(int i = startIndex; i <=endIndex; i++) {
        printf(" %d", array[i]);
    }

    printf("\n");
}