#include <stdio.h>
#include <malloc.h>

typedef struct node {
    int val;
    struct node *next;
} node;


int add(struct node **head_ptr, int val);

int pop(struct node **head_ptr);

int main() {
    node *head = NULL;
    add(&head, 7);
    add(&head, 8);
    add(&head, 9);
    printf("%d", pop(&head));
    printf("%d", pop(&head));
    printf("%d", pop(&head));
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