#include <stdio.h>
#include <malloc.h>
#include <windows.h>

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

void show(doublyLinkedList list);

int main(void) {

    doublyLinkedList list = createDoublyLinkedList();
    add(5, list);
    add(6, list);
    add(7, list);
    add(8, list);
    add(9, list);
    add(10, list);
    show(list);
    printf("\n");



    printf("%d", get(1, list));
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
    if (list->size - 1 < elementNumber) {
        printf("Index Out of Bound...");
        return 0;
    } else if (elementNumber > (list->size / 2)) {
        doublyLinkedListElement *current = list->head;
        int iterator = list->size - elementNumber;
        while (iterator > 0) {
            current = current->prev;
            iterator--;
        }
        return current->value;
    } else {
        doublyLinkedListElement *current = list->head;
        int iterator = elementNumber;
        while (iterator > 0) {
            current = current->next;
            iterator--;
        }
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
    }
    else if(elementNumber == 0) {

        doublyLinkedListElement* secondElement = list->head->next;
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
    if(list->size == 0) {
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