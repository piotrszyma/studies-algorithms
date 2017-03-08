#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct singleLinkedListElement {
    int value;
    struct singleLinkedListElement *next;
} singleLinkedListElement;

typedef struct singleLinkedListHead {
    int size;
    singleLinkedListElement *head;
} singleLinkedListHead;

typedef singleLinkedListHead *singleLinkedList;

singleLinkedListHead *createSingleLinkedList() {
    singleLinkedListHead *headPointer = malloc(sizeof(singleLinkedListHead));
    headPointer->size = 0;
    headPointer->head = NULL;
    return headPointer;
}

int add(int value, singleLinkedList list);

int get(int elementNumber, singleLinkedList list);

int pop(int elementNumber, singleLinkedList list);

int merge(singleLinkedList firstList, singleLinkedList secondList);

void show(singleLinkedList list);

int main(void) {
    singleLinkedList list = createSingleLinkedList();

    add(1, list);
    add(2, list);
    add(3, list);
    add(4, list);

    singleLinkedList list2 = createSingleLinkedList();

    add(5, list2);
    add(6, list2);
    add(7, list2);
    add(8, list2);

    merge(list, list2);

    show(list);
    show(list2);
    add(1, list2);
    show(list2);
    printf("\n");


    return 0;

    printf("Generating 1000 elements list... \n");
    for (int i = 0; i < 1000; i++) add(rand() % 100, list);
    printf("Generated \n");

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < 10000000; i++) {
        get(0, list);
    }
    gettimeofday(&end, NULL);

    printf("Average time for  first element access: %0.5f [microseconds]\n",
           ((float) ((end.tv_sec * 1000000 + end.tv_usec)
                     - (start.tv_sec * 1000000 + start.tv_usec))) / 10000000);

    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(749, list);
    }
    gettimeofday(&end, NULL);

    printf("Average time for    749 element access: %0.5f [microseconds]\n",
           ((float) ((end.tv_sec * 1000000 + end.tv_usec)
                     - (start.tv_sec * 1000000 + start.tv_usec))) / 1000000);


    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(499, list);
    }
    gettimeofday(&end, NULL);

    printf("Average time for    499 element access: %0.5f [microseconds]\n",
           ((float) ((end.tv_sec * 1000000 + end.tv_usec)
                     - (start.tv_sec * 1000000 + start.tv_usec))) / 1000000);
    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(999, list);
    }
    gettimeofday(&end, NULL);


    printf("Average time for   last element access: %0.5f [microseconds]\n",
           ((float) ((end.tv_sec * 1000000 + end.tv_usec)
                     - (start.tv_sec * 1000000 + start.tv_usec))) / 1000000);

    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(rand() % 1000, list);
    }
    gettimeofday(&end, NULL);


    printf("Average time for random element access: %0.5f [microseconds]\n",
           ((float) ((end.tv_sec * 1000000 + end.tv_usec)
                     - (start.tv_sec * 1000000 + start.tv_usec))) / 1000000);


    return 0;
}

int add(int value, singleLinkedList list) {
    if (list->head == NULL) {
        singleLinkedListElement *newElement = malloc(sizeof(singleLinkedListElement));
        newElement->next = NULL;
        newElement->value = value;
        list->size = 1;
        list->head = newElement;
        return 1;
    } else {
        singleLinkedListElement *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = malloc(sizeof(singleLinkedListElement));
        current->next->value = value;
        current->next->next = NULL;
        list->size++;
        return 1;
    }
}

int get(int elementNumber, singleLinkedList list) {
    if (elementNumber > list->size - 1 || elementNumber < 0) {
        printf("Index out of bound");
        return -1;
    }
    singleLinkedListElement *current = list->head;
    while (elementNumber--) {
        current = current->next;
    }
    return current->value;
}


void show(singleLinkedList list) {
//    if(list == NULL) {
//        printf("List is not initialized");
//        return;
//    }
    singleLinkedListElement *current = list->head;
    while (current) {
        printf("%d ", current->value);
        current = current->next;
    }
}

int merge(singleLinkedList firstList, singleLinkedList secondList) {

    singleLinkedListElement *firstListLastElement = firstList->head;

    while (firstListLastElement->next != NULL) {
        firstListLastElement = firstListLastElement->next;
    }

    firstListLastElement->next = secondList->head;
    secondList->head = NULL;
    secondList->size = 0;
}

int pop(int index, singleLinkedList list) {
    if(index + 1 > list->size) {
        printf("Array out of bound");
        return -1;
    } else if(index < 0) {
        printf("Index under 0");
        return -1;
    }
    singleLinkedListElement* current = list->head;
    singleLinkedListElement* previous = NULL;

    while(index > 0) {
        previous = current;
        current = current->next;
        index--;
    }

    if(previous!= NULL) {
        previous->next = current->next;
    } else {
        list->head = current->next;
    }

    free(current);

}