#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char data;
    struct node*next;
}node;

node *front = NULL;
node *rear = NULL;
int curSize = 0;
int maxSize = 0;

void createQueue(int n){
    while(front != NULL){
        node *tmp = front;
        front = front->next;
        free(tmp);
    }
    curSize = 0;
    maxSize = n;
    rear = NULL;
    printf ("OK\n");
}

void enqueue(char c){
    if(curSize >= maxSize){
        printf ("Queue full\n");
        return;
    }
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = c;
    newNode->next = NULL;
    if(rear == NULL){
        front = rear = newNode;
    }
    else{
        rear->next = newNode;
        rear = newNode;
    }
    curSize++;
    printf("OK\n");
}

void dequeue(){
    if(front == NULL){
        printf("Queue empty\n");
        return;
    }
    node *tmp = front;
    front = front->next;
    if(front == NULL) rear = NULL;
    printf ("%c\n", tmp->data);
    free(tmp);
    curSize--;
}

int main(){
    int i;
    while(scanf(" %d", &i) == 1){
        if(i==0){
            printf ("quit");
            break;
        }
        else if(i==1){
            int size;
            scanf (" %d", &size);
            createQueue(size);
        }
        else if(i==2){
            char c;
            scanf(" %c", &c);
            enqueue(c);
        }
        else if(i==3){
            dequeue();
        }
    }
}