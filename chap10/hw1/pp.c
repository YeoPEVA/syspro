#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int data;
	struct node *next;
};

// 스택에 데이터 추가
void push(struct node **top, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        perror("malloc");
        exit(1);
    }
    new_node->data = data;
    new_node->next = *top; // 현재 top을 새로운 노드의 다음 노드로 설정
    *top = new_node;       // top을 새로운 노드로 변경
}


int pop(struct node **top){
    struct node *temp = *top;
    int data = temp->data;
    *top = (*top)->next; // top을 다음 노드로 변경
    free(temp);          // 제거된 노드 메모리 해제
    return data;
}


int main() 
{ 
    int inputData = 0, id;
    struct node *head = NULL;    
    
    while (scanf("%d", &inputData) == 1)  {
        push(&head, inputData);
    }

    printf("Print stack\n");
    while (head != NULL)  {
        printf("%d\n",pop(&head));
    }
    exit(0);
}