#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node*next;
}node;

void insert(node **head, int x){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = x;
    newNode->next = NULL;
    if(*head == NULL){
        *head = newNode;
        return;
    }
    node *tmp = *head;
    while(tmp->next != NULL) tmp = tmp->next;
    tmp->next = newNode;
}

void find(node *head){
    if(head == NULL) return;
    node* fast = head;
    node *slow = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    printf ("%d\n", slow->data);
}

int main(){
    int t;
    scanf(" %d", &t);
    getchar();
    while(t--){
        node *head = NULL;
        char s[1000];
        gets(s);
        s[strcspn(s, "\n")] = '\0';
        char *token = strtok(s, " ");
        while(token!=NULL){
            int x = atoi(token);
            insert(&head, x);
            token = strtok(NULL, " ");
        }
        find(head);
    }
}



