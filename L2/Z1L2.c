#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include <math.h>
#include <string.h>

#define NUMBER_OF_TESTS 100

void swap(int *array, int firstElementIndex, int secondElementIndex);

void show(int *array);

void sortAlgorithmsTest(int orderType);

void generateData(int orderType);

void generateAverageData(int orderType);

int *generateArray(int size, int orderType);

void check(int *array);

void insertionSort(int *array);

void mergeSort(int *array);

void mergeSortDivider(int *array, int startIndex, int endIndex);

void merge(int *array, int firstArrayFirstElement, int firstArrayLastElement, int secondArrayLastElement);

void quickSort(int *array);

void quickSortDivider(int *array, int startIndex, int endIndex);

int *generateRandomDataArray(int arraySize);

float countTime(void (*algorithm)(int *));

unsigned int arraySize;

unsigned long long swapCounter;
unsigned long long comparisonCounter;
unsigned short logEnabled;
unsigned short insertionSortTimerEnabled;
int orderType;


int main(void) {

    insertionSortTimerEnabled = 0;
    int optionType;

    for (;;) {
        printf("What do you want to do?\n");
        printf("1. Count time with random data\n");
        printf("2. Count time with descending ordered data\n");
        printf("3. Generate data file with random data\n");
        printf("4. Generate data file with descending order data\n");
        printf("5. Show logs with random data\n");
        printf("6. Show logs with descending order data\n");
        printf("7. End\n");
        printf("Option [1-7]: ");
        scanf("%d", &optionType);
        if (optionType != 7) {
            printf("Enter the size of array to sort: ");
            scanf("%d", &arraySize);
        }

        switch (optionType) {
            case 1:
                logEnabled = 0;
                orderType = 1;
                printf("quickSort:\t\t%0.5f [us]\n", countTime(quickSort));
                printf("mergeSort:\t\t%0.5f [us]\n", countTime(mergeSort));
                printf("insertionSort:\t\t%0.5f [us]\n", countTime(insertionSort));
                break;
            case 2:
                logEnabled = 0;
                orderType = 2;
                printf("quickSort:\t\t%0.5f [us]\n", countTime(quickSort));
                printf("mergeSort:\t\t%0.5f [us]\n", countTime(mergeSort));
                printf("insertionSort:\t\t%0.5f [us]\n", countTime(insertionSort));
                break;
            case 3:
                logEnabled = 0;
                orderType = 1;
                generateAverageData(1);
//                generateData(1);
                break;
            case 4:
                logEnabled = 0;
                orderType = 0;
                generateAverageData(2);
//                generateData(2);
                break;
            case 5:
                logEnabled = 1;
                orderType = 1;
                sortAlgorithmsTest(1);
                break;
            case 6:
                logEnabled = 1;
                orderType = 0;
                sortAlgorithmsTest(1);
                break;
            case 7:
                return 0;
            default:
                printf("You've chosen wrong number!\n");
                break;
        }

    }
}


/*
 *
 *  Quick Sort
 *
 *
 */

void quickSort(int *array) {
    swapCounter = 0;
    comparisonCounter = 0;
    if (logEnabled) {
        printf("\n\nQS LOG: starting algorithm for array: ");
        show(array);
        printf("\n");
    }
    quickSortDivider(array, 0, arraySize - 1);
    if (logEnabled) {

        printf("QS SORT: sorted...");
        show(array);
        printf("\n\n\n");
    }
}

void quickSortDivider(int *array, int startIndex, int endIndex) {

    if (startIndex >= endIndex) return;
    if (logEnabled) printf("\nQS LOG: counting pivot for array: a[%d] - a[%d]\n", startIndex, endIndex);

    int pivotValue = array[(startIndex + endIndex) / 2];
    int leftSearchIndex = startIndex;
    int rightSearchIndex = endIndex;

    if (logEnabled) printf("QS LOG: looking for smaller or equal pivot on left; bigger than pivot on right\n");
    while (leftSearchIndex <= rightSearchIndex) {
        while (array[leftSearchIndex] < pivotValue) {
            comparisonCounter++;
            leftSearchIndex++;
        }
        comparisonCounter++;

        if (logEnabled)
            printf("QS LOG: found element smaller than pivot at %d index (value = %d)\n", leftSearchIndex,
                   array[leftSearchIndex]);

        while (array[rightSearchIndex] > pivotValue) {
            rightSearchIndex--;
            comparisonCounter++;
        }
        comparisonCounter++;
        if (logEnabled) {
            printf("QS LOG: found element bigger than pivot at %d index (value = %d)\n", rightSearchIndex,
                   array[rightSearchIndex]);
        }

        if (leftSearchIndex <= rightSearchIndex) {
            if (logEnabled) printf("QS LOG: swapping elements found above, continuing...\n");
            swap(array, leftSearchIndex, rightSearchIndex);
            swapCounter++;
            leftSearchIndex++;
            rightSearchIndex--;
        } else {
            if (logEnabled) printf("QG LOG: searching indexes missed\n");
        }
    }

    if (logEnabled) printf("QG LOG: searching indexes missed\n");

    comparisonCounter++;
    if (rightSearchIndex > startIndex) quickSortDivider(array, startIndex, rightSearchIndex);

    comparisonCounter++;
    if (leftSearchIndex < endIndex) quickSortDivider(array, leftSearchIndex, endIndex);

}

/*
 *
 *  Merge Sort
 *
 *
 */

void mergeSort(int *array) {
    swapCounter = 0;
    comparisonCounter = 0;
    if (logEnabled) {
        printf("\n\nMG SORT: Starting algorithm for array: ");
        show(array);
        printf("\n");
    }
    mergeSortDivider(array, 0, arraySize - 1);
    if (logEnabled) {
        printf("MG SORT: sorted...");
        show(array);
        printf("\n\n\n");

    }

}

void mergeSortDivider(int *array, int startIndex, int endIndex) {
    if (startIndex == endIndex) {
        return;
    }
    if (logEnabled) printf("MG SORT: counting pivot for array: a[%d] - a[%d]\n", startIndex, endIndex);

    int centerIndex = (startIndex + endIndex) / 2;
    if (logEnabled)
        printf("MG SORT: dividing array a[%d] - a[%d] on two parts on %d index\n", startIndex, endIndex, centerIndex);

    mergeSortDivider(array, startIndex, centerIndex);
    mergeSortDivider(array, centerIndex + 1, endIndex);

    merge(array, startIndex, centerIndex, endIndex);
}

void merge(int *array, int firstArrayFirstElement, int firstArrayLastElement, int secondArrayLastElement) {

    int secondArrayFirstElement = firstArrayLastElement + 1;
    int tempArray[arraySize];
    int firstArrayIndex = firstArrayFirstElement;
    int secondArrayIndex = secondArrayFirstElement;
    int tempArrayIndex = 0;
    if (logEnabled)
        printf("MG SORT: merging subtables: a[%d] - a[%d] and a[%d] - a[%d]\n", firstArrayFirstElement,
               firstArrayLastElement, secondArrayFirstElement, secondArrayLastElement);

    while (firstArrayIndex <= firstArrayLastElement && secondArrayIndex <= secondArrayLastElement) {

        comparisonCounter++;

        if (array[firstArrayIndex] > array[secondArrayIndex]) {
            tempArray[tempArrayIndex] = array[secondArrayIndex];
            secondArrayIndex++;
        } else {
            tempArray[tempArrayIndex] = array[firstArrayIndex];
            firstArrayIndex++;
        }
        tempArrayIndex++;
        swapCounter++;


    }

    while (firstArrayIndex <= firstArrayLastElement) {
        tempArray[tempArrayIndex] = array[firstArrayIndex];
        firstArrayIndex++;
        tempArrayIndex++;
        swapCounter++;
    }

    while (secondArrayIndex <= secondArrayLastElement) {
        tempArray[tempArrayIndex] = array[secondArrayIndex];
        secondArrayIndex++;
        tempArrayIndex++;
        swapCounter++;
    }

    int tempArrayLastElement = tempArrayIndex - 1;
    tempArrayIndex = 0;
    int arrayIndex = firstArrayFirstElement;

    if (logEnabled)
        printf("MG SORT: saving sorted array on positions from a[%d] to a[%d]\n", firstArrayFirstElement,
               secondArrayLastElement);
    while (tempArrayIndex <= tempArrayLastElement) {
        array[arrayIndex] = tempArray[tempArrayIndex];
        tempArrayIndex++;
        arrayIndex++;
    }

}

/*
 *
 *  Insertion Sort
 *
 *
 */

void insertionSort(int *array) {
    swapCounter = 0;
    comparisonCounter = 0;
    FILE *f;
    FILE *g;
    if (insertionSortTimerEnabled) {
        f = fopen("insertion_sort_swaps.txt", "w");
        g = fopen("insertion_sort_comps.txt", "w");
    }

    if (logEnabled) printf("\n\nIN SORT: starting algorithm...\n");
    for (int i = 1; i < arraySize; i++) {
        for (int j = i - 1; j >= 0; j--) {

            if (logEnabled) printf("IN SORT: checking if a[%d] is bigger than a[%d]...\n", j, j + 1);

            comparisonCounter++;
            if (array[j] > array[j + 1]) {
                if (logEnabled) printf("IN SORT: it is, so swaping...\n");

                swap(array, j, j + 1);
                swapCounter++;


            } else break;
        }
        if (insertionSortTimerEnabled) {
            fprintf(f, "%d %llu\n", i, swapCounter);
            fprintf(g, "%d %llu\n", i, comparisonCounter);
        }
    }

    if (insertionSortTimerEnabled) {
        fclose(f);
        fclose(g);
    }
    if (logEnabled) {
        printf("IN SORT: sorted...");
        show(array);
        printf("\n\n\n");
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


/*
 *
 * Testing
 *
 *
 */

void sortAlgorithmsTest(int orderType) {


    int *insertionSortArray = malloc(sizeof(int) * arraySize);
    int *mergeSortArray = malloc(sizeof(int) * arraySize);
    int *quickSortArray = malloc(sizeof(int) * arraySize);

    switch (orderType) {
        case 1:
            for (int i = 0; i < arraySize; i++) {
                insertionSortArray[i] = rand() % 100;
                mergeSortArray[i] = insertionSortArray[i];
                quickSortArray[i] = insertionSortArray[i];
            }
            break;
        case 2:
            for (int i = 0; i < arraySize; i++) {
                insertionSortArray[i] = arraySize - i;
                mergeSortArray[i] = insertionSortArray[i];
                quickSortArray[i] = insertionSortArray[i];
            }
            break;
        default:
            printf("Wrong orderType");
            break;

    }

    struct timeval start, end;

    srand(time(NULL));

    gettimeofday(&start, NULL);
    insertionSort(insertionSortArray);
    gettimeofday(&end, NULL);

    if (!logEnabled) {
        printf("\n--- \t\tInsertion sort \t\t ---\n\n");
        printf("Time: %0.2f [microseconds]\n",
               ((float) ((end.tv_sec * 1000000 + end.tv_usec)
                         - (start.tv_sec * 1000000 + start.tv_usec))));

        printf("Number of swaps: %llu\n", swapCounter);
        printf("Number of comparisons: %llu\n", comparisonCounter);
    }


    gettimeofday(&start, NULL);
    mergeSort(mergeSortArray);
    gettimeofday(&end, NULL);

    if (!logEnabled) {
        printf("\n--- \t\tMerge sort \t\t ---\n\n");

        printf("Time: %0.2f [microseconds]\n",
               ((float) ((end.tv_sec * 1000000 + end.tv_usec)
                         - (start.tv_sec * 1000000 + start.tv_usec))));

        printf("Number of swaps: %llu\n", swapCounter);
        printf("Number of comparisons: %llu\n", comparisonCounter);

    }

    gettimeofday(&start, NULL);
    quickSort(quickSortArray);
    gettimeofday(&end, NULL);


    free(insertionSortArray);
    free(mergeSortArray);
    free(quickSortArray);

}

void generateData(int orderType) {
    int *array;
    int maxArraySize = arraySize;
    unsigned long long timeSum;
    unsigned long long swapsSum;
    unsigned long long comparisonsSums;

    FILE *f = fopen("merge_sort_swaps.txt", "w");
    FILE *g = fopen("merge_sort_comps.txt", "w");
    printf("Generating... (mergeSort)\n");

    for (int i = 100; i <= maxArraySize; i += 100) {
        array = generateArray(i, orderType);
        arraySize = i;
        mergeSort(array);
        free(array);
        fprintf(f, "%d %llu\n", i, swapCounter);
        fprintf(g, "%d %llu\n", i, comparisonCounter);
    }
    fclose(f);
    fclose(g);

    printf("Merge sort stats generated\n");

    f = fopen("quick_sort_swaps.txt", "w");
    g = fopen("quick_sort_comps.txt", "w");
    printf("Generating... (quickSort)\n");

    for (int i = 100; i <= maxArraySize; i += 100) {
        array = generateArray(i, orderType);
        arraySize = i;
        quickSort(array);
        free(array);
        fprintf(f, "%d %llu\n", i, swapCounter);
        fprintf(g, "%d %llu\n", i, comparisonCounter);
    }
    fclose(f);
    fclose(g);

    printf("Quick sort stats generated\n");


    printf("Generating... (insertionSort)\n");

    insertionSortTimerEnabled = 1;
    array = generateArray(maxArraySize, orderType);
    insertionSort(array);
    free(array);
    insertionSortTimerEnabled = 0;

    printf("Insertion sort stats for generated\n");
    printf("All stats files for %d elements array generated!\n", maxArraySize);
    printf("Returning to the beginning...\n\n");
}

//orderType
//1 - random
//2 - descending

int *generateArray(int size, int orderType) {

    int *array = malloc(sizeof(int) * size);
    srand(time(NULL));
    if (orderType == 1) {
        for (int i = 0; i < size; i++) {
            array[i] = rand() % 1000;
        }
    } else {
        for (int i = 0; i < size; i++) {
            array[i] = size - i;
        }
    }

    return array;
}

void generateAverageData(int orderType) {
    int *array;
    int maxArraySize = arraySize;
    unsigned long long swapsSum;
    unsigned long long comparisonsSums;

    FILE *f = fopen("merge_sort_swaps.txt", "w");
    FILE *g = fopen("merge_sort_comps.txt", "w");
    printf("Generating... (mergeSort)\n");

    swapsSum = 0;
    comparisonsSums = 0;

    for (int i = 100; i <= maxArraySize; i += 100) {

        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            array = generateArray(i, orderType);
            arraySize = i;
            mergeSort(array);
            free(array);
            swapsSum += swapCounter;
            comparisonsSums += comparisonCounter;

        }
        printf("%d/%d\n", i, maxArraySize);

        fprintf(f, "%d %llu\n", i, swapsSum / NUMBER_OF_TESTS);
        fprintf(g, "%d %llu\n", i, comparisonsSums / NUMBER_OF_TESTS);
    }

    fclose(f);
    fclose(g);

    printf("Merge sort stats generated\n");

    f = fopen("quick_sort_swaps.txt", "w");
    g = fopen("quick_sort_comps.txt", "w");
    printf("Generating... (quickSort)\n");

    swapsSum = 0;
    comparisonsSums = 0;

    for (int i = 100; i <= maxArraySize; i += 100) {

        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            array = generateArray(i, orderType);
            arraySize = i;
            quickSort(array);
            free(array);
            swapsSum += swapCounter;
            comparisonsSums += comparisonCounter;

        }
        printf("%d/%d\n", i, maxArraySize);
        fprintf(f, "%d %llu\n", i, swapsSum / NUMBER_OF_TESTS);
        fprintf(g, "%d %llu\n", i, comparisonsSums / NUMBER_OF_TESTS);
    }

    swapsSum = 0;
    comparisonsSums = 0;

    fclose(f);
    fclose(g);

    printf("Quick sort stats generated\n");

    printf("Generating... (insertionSort)\n");

    insertionSortTimerEnabled = 1;
    array = generateArray(maxArraySize, orderType);
    insertionSort(array);
    free(array);
    insertionSortTimerEnabled = 0;

    printf("Insertion sort stats for generated\n");
    printf("All stats files for %d elements array generated!\n", maxArraySize);
    printf("Returning to the beginning...\n\n");
}

float countTime(void (*algorithm)(int *)) {

    struct timeval start, end;

    float timeSum = 0;

    int *array = malloc(sizeof(int) * arraySize);
    srand(time(NULL));
    for (int i = 0; i < NUMBER_OF_TESTS; i++) {

        array = generateArray(arraySize, orderType);

        gettimeofday(&start, NULL);
        (*algorithm)(array);
        gettimeofday(&end, NULL);

        timeSum += ((float) ((end.tv_sec * 1000000 + end.tv_usec)
                             - (start.tv_sec * 1000000 + start.tv_usec)));
    }
    free(array);
    return timeSum / NUMBER_OF_TESTS;
}