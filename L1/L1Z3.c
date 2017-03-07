#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct doublyLinkedListElement {
    int value;
    struct doublyLinkedListElement *prev;
    struct doublyLinkedListElement *next;
} doublyLinkedListElement;

typedef struct doublyLinkedListHead {
    int size;
    doublyLinkedListElement *head;
} doublyLinkedListHead;

typedef doublyLinkedListHead *doublyLinkedList;

doublyLinkedListHead *createDoublyLinkedList();

int add(int value, doublyLinkedList list);

int get(int elementNumber, doublyLinkedList list);

int pop(int elementNumber, doublyLinkedList list);

int merge(doublyLinkedList firstList, doublyLinkedList secondList);

void show(doublyLinkedList list);

int main(void) {

    double time = 0;

    doublyLinkedList list = createDoublyLinkedList();
    printf("Generating 1000 elements list... \n");
    for (int i = 0; i < 1000; i++) add(rand() % 100, list);
    printf("Generated \n");
//
//    doublyLinkedList list2 = createDoublyLinkedList();
//
//    add(1, list2);
//    add(2, list2);
//    add(3, list2);
//    add(4, list2);
//    add(4, list2);
//    add(4, list2);
//    add(4, list2);
//    add(4, list2);
//    add(4, list2);
//
//    show(list2);
//
//    printf("\n");
//
//    printf("%d", get(3, list2));
//    printf("\n");
//
//    printf("%d", get(7, list2));
//    printf("\n");

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
    for (int i = 0; i < 10000000; i++) {
        get(999, list);
    }
    gettimeofday(&end, NULL);


    printf("Average time for   last element access: %0.5f [microseconds]\n",  ((float)((end.tv_sec * 1000000 + end.tv_usec)
                                                                                    - (start.tv_sec * 1000000 + start.tv_usec))) /10000000);

    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(rand()%1000, list);
    }
    gettimeofday(&end, NULL);


    printf("Average time for random element access: %0.5f [microseconds]\n",  ((float)((end.tv_sec * 1000000 + end.tv_usec)
                                                                                    - (start.tv_sec * 1000000 + start.tv_usec))) /1000000);


    return 0;
}

doublyLinkedListHead *createDoublyLinkedList() {
    doublyLinkedListHead *headPointer = malloc(sizeof(doublyLinkedListHead));
    headPointer->size = 0;
    headPointer->head = NULL;
    return headPointer;
}

int add(int value, doublyLinkedList list) {
    if (list->head == NULL) {
        doublyLinkedListElement *newElement = malloc(sizeof(doublyLinkedListElement));
        newElement->prev = newElement;
        newElement->next = newElement;
        newElement->value = value;
        list->head = newElement;
    } else {
        doublyLinkedListElement *current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        doublyLinkedListElement *newElement = malloc(sizeof(doublyLinkedListElement));
        newElement->value = value;
        newElement->next = list->head;
        newElement->prev = list->head->prev;
        list->head->prev->next = newElement;
        list->head->prev = newElement;
    }
    list->size++;
}

int get(int elementNumber, doublyLinkedList list) {

    int LOOP_NR = 0;
    if (list->size - 1 < elementNumber) {
        printf("Index Out of Bound...");
        return 0;
    } else if (elementNumber > (list->size / 2)) {
        doublyLinkedListElement *current = list->head;
        int iterator = list->size - elementNumber;
        while (iterator > 0) {
            current = current->prev;
            iterator--;
            LOOP_NR++;
        }
//        printf("UP %d\n", LOOP_NR);

        return current->value;
    } else {
        doublyLinkedListElement *current = list->head;
        int iterator = elementNumber;
        while (iterator > 0) {
            current = current->next;
            iterator--;
            LOOP_NR++;
        }
//        printf("LOW %d\n", LOOP_NR);
        return current->value;
    }
}

int pop(int elementNumber, doublyLinkedList list) {
    if (list->size - 1 < elementNumber) {
        printf("Index Out of Bound...");
        return -1;
    } else if (list->size == 1) {
        free(list->head);
        list->head = NULL;
        list->size--;
        return 1;
    } else if (elementNumber == 0) {

        doublyLinkedListElement *secondElement = list->head->next;
        list->head->prev->next = secondElement;
        free(list->head);
        list->head = secondElement;
        list->size--;

    } else if (elementNumber > (list->size / 2)) {
        doublyLinkedListElement *current = list->head;
        int iterator = list->size - elementNumber;
        while (iterator > 0) {
            current = current->prev;
            iterator--;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
        list->size--;
        return 1;
    } else {
        doublyLinkedListElement *current = list->head;
        int iterator = elementNumber;
        while (iterator > 0) {
            current = current->next;
            iterator--;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
        list->size--;
        return 1;
    }
}

void show(doublyLinkedList list) {
    if (list->size == 0) {
        printf("List is empty");
        return;
    }

    int iterator = 0;
    doublyLinkedListElement *current = list->head;
    while (iterator < list->size) {
        printf("%d ", current->value);
        current = current->next;
        iterator++;
    }
}

int merge(doublyLinkedList firstList, doublyLinkedList secondList) {
    doublyLinkedListElement *secondListLastElement = secondList->head->prev;
    firstList->head->prev->next = secondList->head;
    secondList->head->prev = firstList->head->prev;
    secondListLastElement->next = firstList->head;
    firstList->head->prev = secondListLastElement;
    firstList->size += secondList->size;
    secondList->size = 0;
    free(secondList);
    return 1;

}