#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node*next;
}node;

void insert(node **head, int n){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = n;
    newNode->next = NULL;
    if(*head == NULL){
        *head = newNode;
        return;
    }
    node *tmp = *head;
    if(n == (*head)->data) return;
    if(n <(*head)->data){
        newNode->next = *head;
        *head = newNode;
        return;
    }
    while(tmp && tmp->next && n > tmp->next->data) tmp = tmp->next;
    if(tmp->next == NULL){
        newNode->next = tmp->next;
        tmp->next = newNode;
        return;
    }
    if(n == tmp->next->data) return;
    newNode->next = tmp->next;
    tmp->next = newNode;
}

void print(node *head){
    if(head == NULL) return;
    while(head->next!=NULL){
        printf ("%d ", head->data);
        head = head->next;
    }
    printf ("%d", head->data);
}

int main(){
    node *head = NULL;
    char s[10001];
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';
    char *tok = strtok(s, " ");
    while(tok!= NULL){
        int x = atoi(tok);
        insert(&head, x);
        tok = strtok(NULL, " ");
    }
    print(head);
}