#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char data;
    struct node*next;
}node;

void push(node **head, char c){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = c;
    newNode->next = (*head);
    *head = newNode;
}

int pop(node**head){
    if(*head == NULL) return 0;
    node *tmp = *head;
    *head = (*head)->next;
    free(tmp);
    return 1;
}

int main(){
    int t;
    scanf ("%d", &t);
    getchar();
    while(t--){
        node *head = NULL;
        int cnt = 0;
        char s[10000];
        fgets(s, sizeof(s), stdin);
        s[strcspn(s, "\n")] = '\0';
        for(int i=0; i< strlen(s); i++){
            if(s[i]=='p') push(&head, s[i]);
            else if(s[i]=='q'){
                if(pop(&head)) cnt++;
            }
        }
        printf ("%d\n", cnt);
    }
}
