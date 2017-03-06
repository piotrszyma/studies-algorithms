#include <stdio.h>
#include <malloc.h>
#include <windows.h>

typedef struct node {
    int val;
    struct node *next;
} node;

//Add new element to the end of the list
int add(struct node **headPointer, int val);

//Add new element to the beginning of the list
int push(struct node **headPointer, int val);

//Get value of element at [index] position
int get(struct node **headPointer, int index);

//Remove element on [index] position
int pop(struct node **headPointer, int index);

int merge(struct node **firstList, struct node **secondList);

void show(struct node **list);

int listSize(struct node **list);


int main() {
    LARGE_INTEGER t1, t2;
    LARGE_INTEGER freq;
    double time = 0;
    node *head = NULL;
    int randomElement;


    printf("Generating 1000 elements list... \n");
    for (int i = 0; i < 1000; i++) add(&head, rand() % 100);
    printf("Generated \n");

    QueryPerformanceFrequency(&freq);
    for (int i = 0; i < 1000; i++) {
        QueryPerformanceCounter(&t1);
        get(&head, 100);
        QueryPerformanceCounter(&t2);
        time += ((t2.QuadPart - t1.QuadPart) * 1000.0) / freq.QuadPart;
    }
    printf("Average time for same element access: %.10f [s]\n", time / 1000.0);

    for (int i = 0; i < 1000; i++) {
        randomElement = rand() % 1000;
        QueryPerformanceCounter(&t1);
        get(&head, randomElement);
        QueryPerformanceCounter(&t2);
        time += ((t2.QuadPart - t1.QuadPart) * 1000.0) / freq.QuadPart;
    }

    printf("Average time random element access:   %.10f [s]\n", time / 1000.0);

    node *firstList = NULL;
    node *secondList = NULL;

    add(&firstList, 1);
    add(&firstList, 2);

    add(&secondList, 5);
    add(&secondList, 9);
    merge(&firstList, &secondList);

//    show(&firstList);
//    printf("\n");
    add(&firstList, 8);


    show(&firstList);
    printf("\n");

    pop(&firstList, 4);
    pop(&firstList, 3);
    pop(&firstList, 2);
    pop(&firstList, 1);
    pop(&firstList, 0);

    push(&firstList, 1);
    push(&firstList, 12);
    pop(&firstList, 0);
    pop(&firstList, 0);
    show(&firstList);

    printf("\n%d", listSize(&firstList));

//    printf("%d", firstList->next->next->next->val);


    return 0;
}

int add(struct node **headPointer, int val) {
    if (*headPointer == NULL) {
        *headPointer = malloc(sizeof(struct node));
        if ((int) (*headPointer) == -1) return -1;
        (*headPointer)->val = val;
        (*headPointer)->next = NULL;
        return 1;
    } else {
        struct node *current = *headPointer;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = malloc(sizeof(node));
        if ((int) (current->next) == -1) return -1;
        current->next->val = val;
        current->next->next = NULL;
        return 1;
    }
}

int push(struct node **headPointer, int val) {
    node *new = (node *) malloc(sizeof(node));
    new->next = *headPointer;
    new->val = val;
    *headPointer = new;
    return 1;
}

int get(struct node **headPointer, int index) {
    node *current = (*headPointer);
    while (index--) {
        current = current->next;
    }
    return current->val;

}

int pop(struct node **headPointer, int index) {
    node *current = *headPointer;
    node *prev = NULL;

    while (index > 0) {
        prev = current;
        current = current->next;
        index--;
    }

    if (prev != NULL) {
        prev->next = current->next;
    } else {
        *headPointer = current->next;
    }
    free(current);

}

int merge(struct node **firstList, struct node **secondList) {
    node *firstLastElement = *firstList;
    while (firstLastElement->next != NULL) {
        firstLastElement = firstLastElement->next;
    }
    firstLastElement->next = *secondList;
}

void show(struct node **list) {
    node *current = *list;
    if (current == NULL) printf("List is empty");
    while (current) {
        printf("%d ", current->val);
        current = current->next;
    }
}

int listSize(struct node **list) {
    int size = 0;
    node *current = *list;
    while (current != NULL) {
        current = current->next;
        size++;
    }
    return size;
}

