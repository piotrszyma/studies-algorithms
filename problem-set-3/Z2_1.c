#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#define NUMBER_OF_TESTS 500

int maxNumberOfDigits;
int logEnabled;
int randOrder;
int arraySize;
int graphGenerating;

int operationsCounter;

int randomizedSelect(int *array, int searchedIndex);

int randomizedSelectRecursion(int *array, int startIndex, int endIndex, int searchedIndex);

int randomizedSelectPartition(int *array, int startIndex, int endIndex);

void calculateConstants();

void show(int *);

void sshow(int *array, int size);

void check(int *);

void swap(int *array, int firstElementIndex, int secondElementIndex);

void quickSort(int *array);

void quickSortDivider(int *array, int startIndex, int endIndex);

int select(int *array, int searchedIndex);

int selectRecursion(int *array, int startIndex, int endIndex, int searchedIndex);

int selectPartition(int *array, int startIndex, int endIndex);

void selectPivot(int *array, int startIndex, int endIndex);

int medianDistanceFromBeginning(int number);

void shuffle(int *array, size_t n);

int *generateArray(int thisArraySize);

void generateDataFile();

void insertionSort(int *array, int startIndex, int endIndex);

int betterSelect(int* array, int searchedIndex);

int selectB(int *array, int index, int startIndex, int endIndex);

int selectMMB(int *array, int startIndex, int endIndex);

int selectPartitionB(int *array, int pivot, int startIndex, int endIndex);

int main(int argc, char *argv[]) {


    if (argc != 6) return 0;

    int searchedIndex;

    arraySize = atoi(argv[1]);
    randOrder = atoi(argv[2]);
    searchedIndex = atoi(argv[3]);
    logEnabled = atoi(argv[4]);
    graphGenerating = atoi(argv[5]);

    //Generate array
    int *array = generateArray(arraySize);

    //Select
    if (logEnabled) {
        int randomizedSelectResult = randomizedSelect(array, searchedIndex);
        int selectResult = select(array, searchedIndex);
        printf("Looked for value at index %d. \nrandomizedSelect() found value = %d\n", searchedIndex,
               randomizedSelectResult);
        printf("select() with median of medians found value = %d\n", selectResult);

        printf("Press Any Key to Continue\n");
        getchar();

        quickSort(array);
        printf("After quickSorting array, the value at position %d is: %d\n", searchedIndex, array[searchedIndex]);
        logEnabled = 0;
    }

    //Generate Graph
    if (graphGenerating) {
        generateDataFile();

        printf("Graph data generated\n");
    }


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
 *  Randomized Select
 *
 *
 */

int randomizedSelect(int *array, int searchedIndex) {

    if (logEnabled) {
        printf("RAND-SEL: Starting algorithm\n");
    }
    if (searchedIndex < 0 || searchedIndex > arraySize - 1) return -1;

    int *arrayCopy = malloc(arraySize * sizeof(int));

    memcpy(arrayCopy, array, arraySize * sizeof(int));

    int searchedIndexResult = randomizedSelectRecursion(arrayCopy, 0, arraySize - 1, searchedIndex);
    free(arrayCopy);
    return searchedIndexResult;

}

int randomizedSelectRecursion(int *array, int startIndex, int endIndex, int searchedIndex) {

    if (logEnabled) {
        printf("RAND-SEL: Starting recursion for array [%d - %d]\n", startIndex, endIndex);
    }
    int pivotIndex = randomizedSelectPartition(array, startIndex, endIndex);

    if (logEnabled) {
        printf("RAND-SEL:Choosing pivot index: %d, value: %d\n", pivotIndex, array[pivotIndex]);
    }
    if (pivotIndex == searchedIndex) {
        if (logEnabled) {
            printf("RAND-SEL: Pivot index equal to searched element, returning.\n");
        }
        return array[searchedIndex];
    } else if (pivotIndex < searchedIndex) {
        if (logEnabled) {
            printf("RAND-SEL: Pivot is smaller than searched element, looking in right side of the table.\n");
        }
        return randomizedSelectRecursion(array, pivotIndex + 1, endIndex, searchedIndex);
    } else {
        if (logEnabled) {
            printf("RAND-SEL: Pivot is bigger than searched element, looking in left side of the table.\n");
        }
        return randomizedSelectRecursion(array, startIndex, pivotIndex - 1, searchedIndex);
    }

}

int randomizedSelectPartition(int *array, int startIndex, int endIndex) {

    if (logEnabled) {
        printf("RAND-SEL:Partitioning array [%d - %d]\n", startIndex, endIndex);
    }

    if (startIndex == endIndex) return startIndex;

    int pivotIndex = startIndex + rand() % (endIndex - startIndex + 1);
    int pivotValue = array[pivotIndex];
    swap(array, pivotIndex, endIndex);
    operationsCounter++;

    int lastLessIndex = startIndex;
    for (int checkedIndex = startIndex; checkedIndex < endIndex; checkedIndex++) {
        if (array[checkedIndex] <= pivotValue) {
            swap(array, lastLessIndex, checkedIndex);
            operationsCounter++;
            lastLessIndex++;
        }
    }

    swap(array, lastLessIndex, endIndex);
    operationsCounter++;

    return lastLessIndex;
}


/*
 *
 *  Select
 *
 *
 */

int select(int *array, int searchedIndex) {

    if (logEnabled) {
        printf("SELECT: Starting algorithm\n");
    }
    if (searchedIndex < 0 || searchedIndex > arraySize - 1) return -1;

    int *arrayCopy = malloc(arraySize * sizeof(int));

    memcpy(arrayCopy, array, arraySize * sizeof(int));

    int searchedIndexResult = selectRecursion(arrayCopy, 0, arraySize - 1, searchedIndex);

    free(arrayCopy);

    return searchedIndexResult;

}

int selectRecursion(int *array, int startIndex, int endIndex, int searchedIndex) {

    if (logEnabled) {
        printf("SELECT: Starting recursion for array [%d - %d]\n", startIndex, endIndex);
    }
    int pivotIndex = selectPartition(array, startIndex, endIndex);

    if (logEnabled) {
        printf("SELECT:Choosing pivot index: %d, value: %d\n", pivotIndex, array[pivotIndex]);
    }

    if (pivotIndex == searchedIndex) {
        if (logEnabled) {
            printf("SELECT: Pivot index equal to searched element, returning.\n");
        }
        return array[searchedIndex];
    } else if (pivotIndex < searchedIndex) {
        if (logEnabled) {
            printf("SELECT: Pivot is smaller than searched element, looking in right side of the table.\n");
        }
        return selectRecursion(array, pivotIndex + 1, endIndex, searchedIndex);
    } else {
        if (logEnabled) {
            printf("SELECT: Pivot is bigger than searched element, looking in right side of the table.\n");
        }
        return selectRecursion(array, startIndex, pivotIndex - 1, searchedIndex);
    }

}

int selectPartition(int *array, int startIndex, int endIndex) {


    if (startIndex == endIndex) return startIndex;


    selectPivot(array, startIndex, endIndex);

    int pivotIndex = startIndex + rand() % (endIndex - startIndex + 1);

    int pivotValue = array[pivotIndex];
    swap(array, pivotIndex, endIndex);
    operationsCounter++;

    int lastLessIndex = startIndex;
    for (int checkedIndex = startIndex; checkedIndex < endIndex; checkedIndex++) {
        if (array[checkedIndex] <= pivotValue) {
            swap(array, lastLessIndex, checkedIndex);
            operationsCounter++;
            lastLessIndex++;
        }
    }

    swap(array, lastLessIndex, endIndex);
    operationsCounter++;

    return lastLessIndex;
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
 * Better Select
 *
 *
 */

int betterSelect(int* array, int searchedIndex) {
    return selectB(array, searchedIndex, 0, arraySize);
}

int selectB(int *array, int index, int startIndex, int endIndex) {
    if (endIndex - startIndex <= 5) {
        insertionSort(array, startIndex, endIndex);
        return array[index];
    }

    int swapIndex = selectMMB(array, startIndex, endIndex);

    int newN = startIndex + ((swapIndex - startIndex) / 2);
    int median = selectB(array, newN, startIndex, swapIndex);

    int location = selectPartitionB(array, median, startIndex, endIndex);
    if (location == index) {
        return array[index];
    } else if (index > location) {
        return selectB(array, index, newN + 1, endIndex);
    } else {
        return selectB(array, index, startIndex, newN);
    }

}

int selectMMB(int *array, int startIndex, int endIndex) {
    int arraySize = endIndex - startIndex + 1;
    int numberOfGroups;
    numberOfGroups = ((arraySize % 5) ? arraySize / 5 + 1 : arraySize / 5);


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

    return startIndex + arraySize - 1;


}

int selectPartitionB(int *array, int pivot, int startIndex, int endIndex) {


    if (startIndex == endIndex) return startIndex;


    int pivotIndex = pivot;
    int pivotValue = array[pivot];

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

void generateDataFile() {

    unsigned long long operationsSum = 0;
    int operationsMax = 0;
    int operationsMin = INT_MAX;


    int *array;
    int maxArraySize;

    printf("Generating stats for SELECT-RAND small range (5 - 100) ...\n");
    FILE *f = fopen("select_rand_5_100.txt", "w");
    FILE *min = fopen("select_rand_5_100_min.txt", "w");
    FILE *max = fopen("select_rand_5_100_max.txt", "w");

    maxArraySize = 100;

    srand(time(NULL));

    for (int i = 5; i < maxArraySize; i += 5) {

        arraySize = i;

        for (int j = 0; j < NUMBER_OF_TESTS * 1000; j++) {

            array = generateArray(i);
            operationsCounter = 0;
            randomizedSelect(array, rand() % arraySize);
            free(array);
            operationsSum += operationsCounter;
            if (operationsCounter > operationsMax) operationsMax = operationsCounter;
            if (operationsCounter < operationsMin) operationsMin = operationsCounter;


        }

        printf("%d / %d\n", i, maxArraySize);
        fprintf(f, "%d %llu\n", i, operationsSum / NUMBER_OF_TESTS);
        fprintf(min, "%d %d\n", i, operationsMin);
        fprintf(max, "%d %d\n", i, operationsMax);
        operationsMax = 0;
        operationsMin = INT_MAX;
        operationsSum = 0;
        operationsCounter = 0;
    }
    fclose(f);
    fclose(min);
    fclose(max);
    printf("Stats for SELECT-RAND small range (5 - 100) generated...\n");


    printf("Generating stats for SELECT small range (5 - 100) ...\n");
    f = fopen("select_5_100.txt", "w");
    min = fopen("select_5_100_min.txt", "w");
    max = fopen("select_5_100_max.txt", "w");

    maxArraySize = 100;
    for (int i = 5; i < maxArraySize; i += 5) {
        arraySize = i;
        for (int j = 0; j < (NUMBER_OF_TESTS * 100); j++) {
            array = generateArray(i);

            operationsCounter = 0;
            select(array, rand() % arraySize);
            free(array);

            operationsSum += operationsCounter;
            if (operationsCounter > operationsMax) operationsMax = operationsCounter;
            if (operationsCounter < operationsMin) operationsMin = operationsCounter;
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
    printf("Stats for SELECT small range (5 - 100) generated...\n");


    printf("Generating stats for SELECT-RAND range (100 - 100000) ...\n");
    f = fopen("select_rand_100_100000.txt", "w");
    min = fopen("select_rand_100_100000_min.txt", "w");
    max = fopen("select_rand_100_100000_max.txt", "w");

    maxArraySize = 100000;
    for (int i = 100; i < maxArraySize; i += 100) {
        arraySize = i;
        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            array = generateArray(i);

            operationsCounter = 0;
            randomizedSelect(array, rand() % arraySize);
            free(array);

            operationsSum += operationsCounter;
            if (operationsCounter > operationsMax) operationsMax = operationsCounter;
            if (operationsCounter < operationsMin) operationsMin = operationsCounter;
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
    printf("Stats for SELECT-RAND range (100 - 100000) generated...\n");

    printf("Generating stats for SELECT range (100 - 100000) ...\n");
    f = fopen("select_100_100000.txt", "w");
    min = fopen("select_100_100000_min.txt", "w");
    max = fopen("select_100_100000_max.txt", "w");

    maxArraySize = 100000;
    for (int i = 100; i < maxArraySize; i += 100) {
        arraySize = i;
        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            array = generateArray(i);

            operationsCounter = 0;
            select(array, rand() % arraySize);
            free(array);

            operationsSum += operationsCounter;
            if (operationsCounter > operationsMax) operationsMax = operationsCounter;
            if (operationsCounter < operationsMin) operationsMin = operationsCounter;
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
    printf("Stats for SELECT small range (100 - 100000) generated...\n");


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
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
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
