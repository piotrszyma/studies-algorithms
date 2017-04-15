#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void swap(int *array, int firstElementIndex, int secondElementIndex) {
    int tmp = array[secondElementIndex];
    array[secondElementIndex] = array[firstElementIndex];
    array[firstElementIndex] = tmp;
}

void show(int *array) {
    int i = 0;
    while (array[i] != '\n') {
        printf("%3d ", array[i]);
        i++;
    }
    printf("\n");
}

int size(int *array) {
    int i = 0;
    while (array[i] != '\n') i++;

    return i;
}