#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int player;
    struct node *next;
}node;

void insertNode(node **head, int i){
    node *newNode = (node*) malloc(sizeof(node));
    newNode->player = i;
    newNode->next = NULL;
    if(*head == NULL){
        *head = newNode;
        return;
    }
    node*tmp = *head;
    while(tmp->next) tmp = tmp->next;
    tmp->next = newNode;
}

void eliminate(node**head, int n){
    if(*head == NULL) return;
    node*tmp = *head;
    if(tmp->player == n){
        *head = (*head)->next;
        free(tmp);
        return;
    }
    while(tmp && tmp->next && tmp->next->player != n) tmp = tmp->next;
    if(tmp == NULL || tmp->next == NULL) return;
    node *del = tmp->next;
    tmp->next = del->next;
    free(del);
}

void pass(node**head, int n){
    if((*head)->player == n || *head == NULL) return;
    node *prev = NULL;
    node *cur = *head;
    while(cur && cur->player != n){
        prev = cur;
        cur = cur->next;
    }
    if(cur == NULL || prev == NULL) return;
    if(prev != (*head)){
        node *tmp = *head;
        while(tmp && tmp->next != prev) tmp = tmp->next;
        tmp->next = cur;
    }
    else{
        *head = cur;
    }
    prev->next = cur->next;
    cur->next = prev;
}

void printList(node*head){
    if(head == NULL) return;
    while (head != NULL)
    {
        printf ("%d ", head->player);
        head = head->next;
    }
    
}

int main(){
    int n, m;
    node *head = NULL;
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; i++){
        insertNode(&head, i);
    }
    while(m--){
        int t, x;
        scanf ("%d%d", &t, &x);
        if(t==0){
            eliminate(&head, x);
        }
        else{
            pass(&head, x);
        }
    }
    printList(head);
}
