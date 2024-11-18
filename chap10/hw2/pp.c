#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int data;
	struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        perror("malloc");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;

    if (*tail == NULL) { 
        *head = *tail = new_node;
    } else {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) { 
        perror("Queue is empty\n");
        exit(1);
    }
    struct node *temp = *head;
    int data = temp->data;
    *head = (*head)->next;

    if (*head == NULL) { 
        *tail = NULL;
    }
    free(temp);
    return data;
}

int main() 
{ 
    int inputData = 0, id;
    struct node *head = NULL, *tail = NULL;    
    
    while (scanf("%d", &inputData) == 1)  {
        addq(&head, &tail, inputData);
    }

    printf("Print queue\n");
    while (head != NULL)  {
        printf("%d\n",delete(&head, &tail));
    }
    exit(0);
}