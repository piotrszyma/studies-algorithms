#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define NUMBER_OF_TESTS 100

//quickSort
void quickSort(int *array);

void quickSortDivider(int *array, int startIndex, int endIndex);

//quickSort wih insertionSort
void quickSortImproved(int *);

void quickSortImprovedDivider(int *, int, int);

//insertionSort
void insertionSortImproved(int *array, int startIndex, int endIndex);

//void insertionSortSec(int *array, int startIndex, int endIndex);

//mergeSort
void mergeSort(int *array);

void mergeSortDivider(int *array, int startIndex, int endIndex);

void merge(int *array, int firstArrayFirstElement, int firstArrayLastElement, int secondArrayLastElement);

//mergeSort with insertionSort

void mergeSortImproved(int *array);

void mergeSortImprovedDivider(int *array, int startIndex, int endIndex);

//Utilities
void swap(int *array, int firstElementIndex, int secondElementIndex);

void show(int *array);

void check(int *array);

int *generateArray(int size, int orderType);

//Generating data
void generateData(int orderType);

void generateAverageData(int orderType);

float countTime(void (*algorithm)(int *));

void showLog();

unsigned int arraySize;
unsigned long long swapCounter;
unsigned long long comparisonCounter;
unsigned short logEnabled;
int orderType;

int main(void) {

    arraySize = 20000;
    orderType = 1;
    logEnabled = 0;
    int optionType;

    for (;;) {
        printf("What do you want to do?\n");
        printf("1. Count time with random data\n");
        printf("2. Count time with descending ordered data\n");
        printf("3. Generate data file with random data\n");
        printf("4. Generate data file with descending order data\n");
        printf("5. Show log for data with random order data\n");
        printf("6. Show log for data with descending order data\n");
        printf("7. End\n");
        printf("Option [1-7]: ");
        scanf("%d", &optionType);
        if (optionType != 7) {
            printf("Enter the size of array to sort: ");
            scanf("%d", &arraySize);
        }

        switch (optionType) {
            case 1:
                orderType = 1;
                printf("mergeSort:\t\t%0.5f [us]\n", countTime(mergeSort));
                printf("mergeInsertSort:\t%0.5f [us]\n", countTime(mergeSortImproved));
                printf("quickSort:\t\t%0.5f [us]\n", countTime(quickSort));
                printf("quickInsertSort:\t%0.5f [us]\n", countTime(quickSortImproved));
                break;
            case 2:
                orderType = 2;
                printf("mergeSort:\t\t%0.5f [us]\n", countTime(mergeSort));
                printf("mergeInsertSort:\t%0.5f [us]\n", countTime(mergeSortImproved));
                printf("quickSort:\t\t%0.5f [us]\n", countTime(quickSort));
                printf("quickInsertSort:\t%0.5f [us]\n", countTime(quickSortImproved));
                break;
            case 3:
                orderType = 1;
                generateAverageData(1);
                break;
            case 4:
                orderType = 2;
                generateAverageData(1);
                break;
            case 5:
                logEnabled = 1;
                showLog();
                logEnabled = 0;
                break;
            case 6:
                logEnabled = 1;
                showLog();
                logEnabled = 0;
                break;
            case 7:
                return 0;
            default:
                printf("You've chosen wrong number!\n");
                break;
        }

    }
    printf("mergeSort:\t\t%0.5f [us]\n", countTime(mergeSort));
    printf("mergeInsertSort:\t%0.5f [us]\n", countTime(mergeSortImproved));
    printf("quickSort:\t\t%0.5f [us]\n", countTime(quickSort));
    printf("quickInsertSort:\t%0.5f [us]\n", countTime(quickSortImproved));
    generateData(orderType);
    return 0;

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
    quickSortDivider(array, 0, arraySize - 1);
}

void quickSortDivider(int *array, int startIndex, int endIndex) {

    comparisonCounter++;
    if (startIndex >= endIndex) return;
    int pivotValue = array[(startIndex + endIndex) / 2];
    int leftSearchIndex = startIndex;
    int rightSearchIndex = endIndex;

    while (leftSearchIndex <= rightSearchIndex) {

        while (array[leftSearchIndex] < pivotValue) {
            leftSearchIndex++;
            comparisonCounter++;
        }

        while (array[rightSearchIndex] > pivotValue) {
            rightSearchIndex--;
            comparisonCounter++;
        }

        comparisonCounter++;
        if (leftSearchIndex <= rightSearchIndex) {
            swap(array, leftSearchIndex, rightSearchIndex);
            swapCounter++;
            leftSearchIndex++;
            rightSearchIndex--;
        }
    }

    comparisonCounter++;
    if (rightSearchIndex > startIndex) quickSortDivider(array, startIndex, rightSearchIndex);

    comparisonCounter++;
    if (leftSearchIndex < endIndex) quickSortDivider(array, leftSearchIndex, endIndex);

}

/*
 *
 * Quicksort with insertion sort for under 16 elements arrays
 *
 *
 */

void quickSortImproved(int *array) {
    swapCounter = 0;
    comparisonCounter = 0;
    if (logEnabled) {
        printf("\n\nQSIMP LOG: starting algorithm for array: ");
        show(array);
        printf("\n");
    }
    quickSortImprovedDivider(array, 0, arraySize - 1);
}

void quickSortImprovedDivider(int *array, int startIndex, int endIndex) {

    comparisonCounter++;

    if (endIndex - startIndex < 17) {
        if (logEnabled) printf("QSIMP LOG: array size under 17, switching to standard insertionSort...\n");
        insertionSortImproved(array, startIndex, endIndex);
    } else {
        if (logEnabled) printf("\nQSIMP LOG: counting pivot for array: a[%d] - a[%d]\n", startIndex, endIndex);

        int pivotValue = array[(startIndex + endIndex) / 2];
        int leftSearchIndex = startIndex;
        int rightSearchIndex = endIndex;

        if (logEnabled) printf("QSIMP LOG: looking for smaller or equal pivot on left; bigger than pivot on right\n");

        while (leftSearchIndex <= rightSearchIndex) {

            while (array[leftSearchIndex] < pivotValue) {
                leftSearchIndex++;
                comparisonCounter++;
            }
            comparisonCounter++;

            if (logEnabled)
                printf("QSIMP LOG: found element smaller than pivot at %d index (value = %d)\n", leftSearchIndex,
                       array[leftSearchIndex]);

            while (array[rightSearchIndex] > pivotValue) {
                rightSearchIndex--;
                comparisonCounter++;
            }

            comparisonCounter++;

            if (logEnabled) {
                printf("QSIMP LOG: found element bigger than pivot at %d index (value = %d)\n", rightSearchIndex,
                       array[rightSearchIndex]);
            }

            if (leftSearchIndex <= rightSearchIndex) {
                if (logEnabled) printf("QSIMP LOG: swapping elements found above, continuing...\n");

                swap(array, leftSearchIndex, rightSearchIndex);
                swapCounter++;
                leftSearchIndex++;
                rightSearchIndex--;
            } else {
                if (logEnabled) printf("QG LOG: searching indexes missed\n");
            }
        }

        if (logEnabled) printf("QGIMP LOG: searching indexes missed\n");


        comparisonCounter++;
        if (rightSearchIndex > startIndex) quickSortImprovedDivider(array, startIndex, rightSearchIndex);

        comparisonCounter++;
        if (leftSearchIndex < endIndex) quickSortImprovedDivider(array, leftSearchIndex, endIndex);
    }


}

void insertionSortImproved(int *array, int startIndex, int endIndex) {
    for (int i = startIndex; i <= endIndex; i++) {
        for (int j = i - 1; j >= startIndex; j--) {
            comparisonCounter++;
            if (array[j] > array[j + 1]) {
                int tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
//                swap(array, j, j + 1);
                swapCounter++;
            } else break;
        }
    }
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
    mergeSortDivider(array, 0, arraySize - 1);
}

void mergeSortDivider(int *array, int startIndex, int endIndex) {
    if (startIndex == endIndex) {
        return;
    }
    int centerIndex = (startIndex + endIndex) / 2;

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

    while (firstArrayIndex <= firstArrayLastElement && secondArrayIndex <= secondArrayLastElement) {

        //mergeSort COMPARISON
        comparisonCounter += 3;

        if (array[firstArrayIndex] > array[secondArrayIndex]) {
            tempArray[tempArrayIndex] = array[secondArrayIndex];
            secondArrayIndex++;
        } else {
            tempArray[tempArrayIndex] = array[firstArrayIndex];
            firstArrayIndex++;
        }
        tempArrayIndex++;

        //mergeSort SWAP
        ++swapCounter;
    }

    while (firstArrayIndex <= firstArrayLastElement) {
        tempArray[tempArrayIndex] = array[firstArrayIndex];
        firstArrayIndex++;
        tempArrayIndex++;
    }

    while (secondArrayIndex <= secondArrayLastElement) {
        tempArray[tempArrayIndex] = array[secondArrayIndex];
        secondArrayIndex++;
        tempArrayIndex++;
    }

    int tempArrayLastElement = tempArrayIndex - 1;
    tempArrayIndex = 0;
    int arrayIndex = firstArrayFirstElement;

    while (tempArrayIndex <= tempArrayLastElement) {
        array[arrayIndex] = tempArray[tempArrayIndex];
        tempArrayIndex++;
        arrayIndex++;
    }

}


/*
 *
 *  Merge Sort improved
 *
 *
 */

void mergeSortImproved(int *array) {
    swapCounter = 0;
    comparisonCounter = 0;
    mergeSortImprovedDivider(array, 0, arraySize - 1);
}

void mergeSortImprovedDivider(int *array, int startIndex, int endIndex) {
    if (startIndex == endIndex) {
        return;
    }
    if (endIndex - startIndex < 6) {
        insertionSortImproved(array, startIndex, endIndex);
    } else {
        int centerIndex = (startIndex + endIndex) / 2;

        mergeSortImprovedDivider(array, startIndex, centerIndex);
        mergeSortImprovedDivider(array, centerIndex + 1, endIndex);

        merge(array, startIndex, centerIndex, endIndex);
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
 * Generating data
 *
 */

void generateData(int orderType) {
    int *array;
    int maxArraySize = arraySize;


    struct timeval start, end;
//
//    gettimeofday(&start, NULL);
//    quickSort(quickSortArray);
//    gettimeofday(&end, NULL);

    FILE *f = fopen("quick_sort_swaps.txt", "w");
    FILE *g = fopen("quick_sort_comps.txt", "w");


    for (int i = 100; i <= maxArraySize; i += 100) {
        unsigned long long swapCounterSum = 0;
        unsigned long long comparisonCounterSum = 0;
        float timeSum = 0.0;
        for (int j = 0; j < 10; j++) {
            array = generateArray(i, orderType);
            arraySize = i;
            gettimeofday(&start, NULL);
            quickSort(array);
            gettimeofday(&end, NULL);
            swapCounterSum += swapCounter;
            comparisonCounterSum += comparisonCounter;
            timeSum += ((float) ((end.tv_sec * 1000000 + end.tv_usec)
                                 - (start.tv_sec * 1000000 + start.tv_usec)));
        }


        free(array);
        printf("Generating... (quickSort) %d/%d\n", i, maxArraySize);
        fprintf(f, "%d %llu\n", i, swapCounter);
        fprintf(g, "%d %llu\n", i, comparisonCounter);
    }
    fclose(f);
    fclose(g);


    printf("Merge sort stats generated\n");

    f = fopen("quick_sort_improved_swaps.txt", "w");
    g = fopen("quick_sort_improved_comps.txt", "w");

    for (int i = 100; i <= maxArraySize; i += 100) {
        array = generateArray(i, orderType);
        arraySize = i;
        gettimeofday(&start, NULL);
        quickSortImproved(array);
        gettimeofday(&end, NULL);

        free(array);
        printf("Generating... (quickSort improved) %d/%d\n", i, maxArraySize);
        fprintf(f, "%d %llu\n", i, swapCounter);
        fprintf(g, "%d %llu\n", i, comparisonCounter);
    }
    fclose(f);
    fclose(g);


    printf("Quick sort stats generated\n");


    f = fopen("merge_sort_swaps.txt", "w");
    g = fopen("merge_sort_comps.txt", "w");


    for (int i = 100; i <= maxArraySize; i += 100) {
        array = generateArray(i, orderType);
        arraySize = i;
        gettimeofday(&start, NULL);
        mergeSort(array);
        gettimeofday(&end, NULL);
        free(array);
        printf("Generating... (mergeSort) %d/%d\n", i, maxArraySize);
        fprintf(f, "%d %llu\n", i, swapCounter);
        fprintf(g, "%d %llu\n", i, comparisonCounter);
    }
    fclose(f);
    fclose(g);

    printf("Quick sort stats generated\n");


    f = fopen("merge_sort_improved_swaps.txt", "w");
    g = fopen("merge_sort_improved_comps.txt", "w");

    for (int i = 100; i <= maxArraySize; i += 100) {
        array = generateArray(i, orderType);
        arraySize = i;
        gettimeofday(&start, NULL);
        mergeSortImproved(array);
        gettimeofday(&end, NULL);
        free(array);
        printf("Generating... (mergeSort improved) %d/%d\n", i, maxArraySize);
        fprintf(f, "%d %llu\n", i, swapCounter);
        fprintf(g, "%d %llu\n", i, comparisonCounter);
    }
    fclose(f);
    fclose(g);

    printf("Quick sort stats generated\n");


    printf("All stats files for %d elements array generated!\n", maxArraySize);
    printf("Returning to the beginning...\n\n");
}

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


void generateAverageData(int orderType) {
    int *array;
    int maxArraySize = arraySize;
    unsigned long long swapsSum;
    unsigned long long comparisonsSums;

    FILE *f = fopen("sec_merge_sort_swaps.txt", "w");
    FILE *g = fopen("sec_merge_sort_comps.txt", "w");
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

    f = fopen("sec_merge_sort_impr_swaps.txt", "w");
    g = fopen("sec_merge_sort_impr_comps.txt", "w");
    printf("Generating... (merge sort impr)\n");

    swapsSum = 0;
    comparisonsSums = 0;

    for (int i = 100; i <= maxArraySize; i += 100) {

        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            array = generateArray(i, orderType);
            arraySize = i;
            mergeSortImproved(array);
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

    printf("Merge sort improved stats generated\n");

    f = fopen("sec_quick_sort_swaps.txt", "w");
    g = fopen("sec_quick_sort_comps.txt", "w");
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


    f = fopen("sec_quick_sort_impr_swaps.txt", "w");
    g = fopen("sec_quick_sort_impr_comps.txt", "w");
    printf("Generating... (quickSort improved)\n");

    swapsSum = 0;
    comparisonsSums = 0;

    for (int i = 100; i <= maxArraySize; i += 100) {

        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            array = generateArray(i, orderType);
            arraySize = i;
            quickSortImproved(array);
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

    printf("Quick sort improved stats generated\n");


    printf("All stats files for %d elements array generated!\n", maxArraySize);
    printf("Returning to the beginning...\n\n");
}

void showLog() {

    printf("Log for quickInsertionSort...\n\n\n");

    int *array = generateArray(arraySize, orderType);

    quickSortImproved(array);

    printf("Log for mergeInsertionSort...\n\n\n");

    mergeSortImproved(array);

    printf("End of log...");

    return;


}