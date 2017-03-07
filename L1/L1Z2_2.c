#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct singleLinkedListElement {
    int value;
    struct singleLinkedListElement* next;
} singleLinkedListElement;

typedef struct singleLinkedListHead {
    int size;
    singleLinkedListElement* head;
} singleLinkedListHead;

typedef singleLinkedListHead* singleLinkedList;

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

int main(void){
    singleLinkedList list = createSingleLinkedList();
//    add(1, list);
//    add(2, list);
//    add(3, list);
//    show(list);
//    printf("%d", get(0, list));
//    printf("%d", get(1, list));
//    printf("%d", get(2, list));
    printf("Generating 1000 elements list... \n");
    for (int i = 0; i < 1000; i++) add(rand() % 100, list);
    printf("Generated \n");

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < 10000000; i++) {
        get(0, list);
    }
    gettimeofday(&end, NULL);

    printf("Average time for  first element access: %0.5f [microseconds]\n",  ((float)((end.tv_sec * 1000000 + end.tv_usec)
                                                                                       - (start.tv_sec * 1000000 + start.tv_usec))) /10000000);

    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(749, list);
    }
    gettimeofday(&end, NULL);

    printf("Average time for    749 element access: %0.5f [microseconds]\n",  ((float)((end.tv_sec * 1000000 + end.tv_usec)
                                                                                       - (start.tv_sec * 1000000 + start.tv_usec))) /1000000);


    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(499, list);
    }
    gettimeofday(&end, NULL);

    printf("Average time for    499 element access: %0.5f [microseconds]\n",  ((float)((end.tv_sec * 1000000 + end.tv_usec)
                                                                                       - (start.tv_sec * 1000000 + start.tv_usec))) /1000000);
    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(999, list);
    }
    gettimeofday(&end, NULL);


    printf("Average time for   last element access: %0.5f [microseconds]\n",  ((float)((end.tv_sec * 1000000 + end.tv_usec)
                                                                                       - (start.tv_sec * 1000000 + start.tv_usec))) /1000000);

    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(rand()%1000, list);
    }
    gettimeofday(&end, NULL);


    printf("Average time for random element access: %0.5f [microseconds]\n",  ((float)((end.tv_sec * 1000000 + end.tv_usec)
                                                                                       - (start.tv_sec * 1000000 + start.tv_usec))) /1000000);


    return 0;
}

int add(int value, singleLinkedList list) {
    if(list->head == NULL) {
        singleLinkedListElement *newElement = malloc(sizeof(singleLinkedListElement));
        newElement->next = NULL;
        newElement->value = value;
        list->size = 1;
        list->head = newElement;
        return 1;
    } else {
        singleLinkedListElement* current = list->head;
        while(current->next != NULL) {
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
    if(elementNumber > list->size - 1 || elementNumber < 0)
    {
        printf("Index out of bound");
        return -1;
    }
    singleLinkedListElement* current = list->head;
    while(elementNumber--) {
        current = current->next;
    }
    return current->value;
}

void show(singleLinkedList list) {
    singleLinkedListElement* current = list->head;
    while(current) {
        printf("%d ", current->value);
        current = current->next;
    }
}