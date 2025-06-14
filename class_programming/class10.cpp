#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int pos;
    struct node*next;
}node;

void insert(node **head, int x){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->pos = x;
    newNode->next = NULL;
    if(*head == NULL){
        *head =newNode;
        return;
    }
    node *tmp = *h nbead;
    while(tmp->next != NULL) tmp = tmp->next;
    tmp->next = newNode;
}

void find(node *head, int cnt){
    if(head == NULL) return;
    node *tmp = head;
    while(tmp->pos != cnt && tmp != NULL){
        tmp = tmp->next;
    }
    if(tmp == NULL) return;
    printf ("%d", tmp->pos);
}


int main(){
    node *head = NULL;
    int n, k;
    scanf("%d %d", &n, &k);
    int cnt = n-k+1;
    for(int i=1; i<=n; i++){
        insert(&head, i);
    }
    find(head, cnt);
}