#include <stdio.h>
#include <malloc.h>

typedef struct node {
    int val;
    struct node *next;
} node;


int add(struct node **head_ptr, int val);

int pop(struct node **head_ptr);

void show(struct node** head_ptr);

int main() {
    node *head = NULL;

    add(&head, 117);
    show(&head);

    printf("\n");

    add(&head, 328);
    add(&head, 522);
    add(&head, 129);

    show(&head);
    pop(&head);

    printf("\n");

    show(&head);

}

int add(struct node **head_ptr, int val) {
    if (*head_ptr == NULL) {
        *head_ptr = malloc(sizeof(struct node));
        if ((int)(*head_ptr) == -1) return -1;
        (*head_ptr)->val = val;
        (*head_ptr)->next = NULL;
        return 1;
    } else {
        struct node *current = *head_ptr;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = malloc(sizeof(node));
        if ((int)(current->next) == -1) return -1;
        current->next->val = val;
        current->next->next = NULL;
        return 1;
    }
}

int pop(struct node **head_ptr) {
    if (*head_ptr == NULL) return -1;
    int retVal = (*head_ptr)->val;
    (*head_ptr) = (*head_ptr)->next;
    return retVal;
}

void show(struct node** head_ptr) {
    node* current = *head_ptr;
    while(current) {
        printf("%d ", current->val);
        current = current->next;
    }
}