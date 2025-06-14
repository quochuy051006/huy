#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node* next;
}node;

void push(node **head, int n){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = n;
    newNode->next = *head;
    *head = newNode;
}

void print(node*head){
    if(head == NULL) return;
    while(head != NULL){
        printf ("%d ", head->data);
        head = head->next;
    }
}

int main(){
    int t;
    scanf("%d", &t);
    getchar();
    while(t--){
        node *head = NULL;
        char s[1000];
        fgets(s, sizeof(s), stdin);
        s[strcspn(s, "\n")]=  '\0';
        char *token = strtok(s, " ");
        while(token != NULL){
            int x = atoi(token);
            push(&head, x);
            token = strtok(NULL, " ");
        }
        print(head);
        printf ("\n");
    }
}

