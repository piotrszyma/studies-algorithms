#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>


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
    double time = 0;
    node *head = NULL;
    int randomElement;


    printf("Generating 1000 elements list... \n");
    for (int i = 0; i < 1000; i++) add(&head, rand() % 100);
    printf("Generated \n");


    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < 10000000; i++) {
        get(&head, 0);
    }
    gettimeofday(&end, NULL);

    printf("Average time for  first element access: %0.5f [microseconds]\n",  ((float)((end.tv_sec * 1000000 + end.tv_usec)
                                                                                      - (start.tv_sec * 1000000 + start.tv_usec))) /1000000);

    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(&head, 749);
    }
    gettimeofday(&end, NULL);

    printf("Average time for    749 element access: %0.5f [microseconds]\n",  ((float)((end.tv_sec * 1000000 + end.tv_usec)
                                                                                      - (start.tv_sec * 1000000 + start.tv_usec))) /1000000);


    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(&head, 499);
    }
    gettimeofday(&end, NULL);

    printf("Average time for    499 element access: %0.5f [microseconds]\n",  ((float)((end.tv_sec * 1000000 + end.tv_usec)
                                                                                      - (start.tv_sec * 1000000 + start.tv_usec))) /1000000);
    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(&head, 999);
    }
    gettimeofday(&end, NULL);


    printf("Average time for   last element access: %0.5f [microseconds]\n",  ((float)((end.tv_sec * 1000000 + end.tv_usec)
                                                                                      - (start.tv_sec * 1000000 + start.tv_usec))) /1000000);

    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++) {
        get(&head, rand()%1000);
    }
    gettimeofday(&end, NULL);


    printf("Average time for random element access: %0.5f [microseconds]\n",  ((float)((end.tv_sec * 1000000 + end.tv_usec)
                                                                                       - (start.tv_sec * 1000000 + start.tv_usec))) /1000000);



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

