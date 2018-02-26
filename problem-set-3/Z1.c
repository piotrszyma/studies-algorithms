#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <math.h>
#include <limits.h>


#define NUMBER_OF_TESTS 1

int maxNumberOfDigits;
int logEnabled;
int descOrder;
int arraySize;
int graphGenerating;

int counterSwaps;
int counterComparisons;

void radixSort(int *array);

void countingSort(int *array, int, int);

int getNthDigit(int number, int n);

void show(int *);

void sshow(int *array, int size);

void check(int *);

int *generateArray(int);

void generateDataFile();

int getNthDigitByBase(int number, int n, int base);

int getBiggestValue(int *array);

int main(int argc, char *argv[]) {

    if (argc != 5) {
        printf("Wrong number of arguments\n");
        return 0;
    }


//# ./radixsort
//# [n: wielkość tablicy]
//# [0: losowe, 1: posortowane malejąco]
//# [0: bez loga, 1: z logiem]
//# [0: nie generuj wykresu, 1: generuj wykres]

    arraySize = atoi(argv[1]);
    descOrder = atoi(argv[2]);
    logEnabled = atoi(argv[3]);
    graphGenerating = atoi(argv[4]);

//    arraySize = 100000;
//    descOrder = 0;
//    logEnabled = 0;
//    graphGenerating = 1;


//Generate array
    int *array = generateArray(arraySize);

//Sort
    if (logEnabled) {
        radixSort(array);
        logEnabled = 0;
    }

    free(array);

//Generate graph
    if (graphGenerating) {
        generateDataFile();
    }

    return 0;
}

void radixSort(int *array) {
    if (logEnabled) {
        printf("RADIXLG: Starting radix sort for array:\n");
        show(array);
    }

    if(arraySize == 1) {
        if (logEnabled) {
            printf("RADIXLG: Array size 1, returning:\n");
            show(array);
        }
        return;
    }

    int max = getBiggestValue(array);
    int base = (int)ceil(sqrt(max));
    int digitsNumber = 3;

    for (int i = 1; i <= digitsNumber; i++) {
        if (logEnabled) printf("RADIXLG: Running counting sort for %d element\n", i);
        countingSort(array, i, base);
    }
}

void countingSort(int *array, int sortedElementIndex, int base) {
    if (logEnabled) printf("RADIXLG: Generating positionsArray for digits at %d index\n", sortedElementIndex);

    int positionsArray[base + 1];

    memset(positionsArray, 0, sizeof(long) * (base + 1));

    for (int i = 0; i < arraySize; i++) {
        positionsArray[getNthDigitByBase(array[i], sortedElementIndex, base)]++;
    }

    if (logEnabled) {
        printf("RADIXLG: positionsArray generated:\n");
        sshow(positionsArray, base);
    }

    int lastNonZeroNumber;

    int i = 0;

    while (i < base) {
        lastNonZeroNumber = positionsArray[i];
        do {
            i++;
        } while (positionsArray[i] == 0);
        positionsArray[i] += lastNonZeroNumber;
    }

    if (logEnabled) {
        printf("RADIXLG: Adding previous element of positionsArray to next, for all, from left to right:\n");
        printf("RADIXLG: positionsArray elements summed:\n");
        sshow(positionsArray, base);
    }

    int orderedArray[arraySize];

    if (logEnabled) {
        sshow(positionsArray, base);
        printf("RADIXLG: positionsArray generated:\n");
    }


    for (int j = arraySize - 1; j >= 0; j--) {
        int elementAtNthIndex = getNthDigitByBase(array[j], sortedElementIndex, base);
        orderedArray[positionsArray[elementAtNthIndex] - 1] = array[j];
        counterSwaps++;
        positionsArray[elementAtNthIndex]--;
    }

    if (logEnabled) {
        printf("RADIXLG: Generating orderedArray (sorted by %d index):\n", sortedElementIndex);
        printf("RADIXLG: orderedArray generated:\n");
        show(orderedArray);
    }

    memcpy(array, orderedArray, arraySize * sizeof(int));

    return;
}

//n-th number of 12345 -> 5 - first, 4 - second, 3 - third and so on
int getNthDigit(int number, int n) {
    while (n--) {
        number /= 10;
    }
    return number % 10;
}

int getNthDigitByBase(int number, int n, int base) {
    return ((number % (int) (pow(base, n))) / (int) pow(base, n - 1));
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
            printf("\nTEST FAILED!");
            return;
        }
    }
    printf("\nTEST PASSED!");
}

void generateDataFile() {

    unsigned long long swapsSum = 0;
    unsigned long long comparisonsSum = 0;
    int *array;

    printf("Generating stats for RADIX SORT...\n");
    FILE *f = fopen("radix_sort_swaps.txt", "w");
    FILE *g = fopen("radix_sort_comps.txt", "w");

    int maxArraySize = arraySize;
    for (int i = 100; i < maxArraySize; i += 100) {
        arraySize = i;
        for (int j = 0; j < NUMBER_OF_TESTS; j++) {
            array = generateArray(i);

            counterComparisons = 0;
            counterSwaps = 0;

            radixSort(array);

            free(array);

            swapsSum += counterSwaps;
            comparisonsSum += counterComparisons;
        }
        printf("%d / 100000\n", i);

        fprintf(f, "%d %llu\n", i, swapsSum / NUMBER_OF_TESTS);
        fprintf(g, "%d %llu\n", i, comparisonsSum / NUMBER_OF_TESTS);
        swapsSum = 0;
        comparisonsSum = 0;
    }
    fclose(f);
    fclose(g);
    printf("Stats for RADIX SORT generated...\n");

}

int *generateArray(int thisArraySize) {

    int *array = malloc(sizeof(int) * thisArraySize);

    if (descOrder) {
        for (int i = thisArraySize - 1; i >= 0; i--) {
            array[i] = i;
        }
    } else {
        srand(time(NULL));
        for (int i = 0; i < thisArraySize; i++) {
            array[i] = abs((rand()*thisArraySize))/RAND_MAX;
        }
    }

    return array;
}

int getBiggestValue(int *array) {

    int max = array[0];

    for (int i = 1; i < arraySize; i++) {
        if (array[i] > max) max = array[i];

    }
    return max;
}