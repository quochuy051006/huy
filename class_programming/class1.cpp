#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct node{
    char data;
    struct node *next;
}node;

void push(node**head, char c){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = c;
    newNode->next = NULL;
    if(*head == NULL){
        *head = newNode;
        return;
    }
    newNode->next = (*head);
    *head = newNode;
}

void pop(node **head){
    if(*head == NULL) return;
    node *tmp = *head;
    *head = (*head)->next;
    free(tmp);
}

void print(node*reverse){
    if(reverse == NULL) return;
    while(reverse!=NULL){
        printf("%c", reverse->data);
        reverse = reverse->next;
    }
}

int main(){
    char s[1000];
    while(gets(s)){
        node *head = NULL;
        s[strcspn(s, "\n")] = '\0';
        for(int i=0; i<strlen(s); i++){
            if(s[i]!='*') push(&head, s[i]);
            else pop(&head);
        }
        node *reverse = NULL;
        while(head != NULL){
            push(&reverse, head->data);
            head = head->next;
        }
        print(reverse);
        printf("\n");
    }
}