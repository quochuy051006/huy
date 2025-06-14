#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char data;
    struct node* next;
}node;

typedef struct stack
{
    node *top;
}stack;

void push(stack *s, char c){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = c;
    newNode->next = s->top;
    s->top = newNode;
}

typedef struct queue
{
    node *front;
    node *rear;
}queue;


void enqueue(queue *q, char c){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = c;
    newNode->next = NULL;
    if(q->rear == NULL){
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

int cmp(stack *s, queue *q){
    while(s->top && q->front){
        if((s->top->data) != (q->front->data)) return 0;
        s->top = s->top->next;
        q->front = q->front->next;
    }
    if(s->top == NULL && q->front == NULL) return 1;
    return 0;
}

int main(){
    int t;
    scanf("%d", &t);
    getchar();
    while(t--){
        stack s = {NULL};
        queue q = {NULL, NULL};
        char str[1000];
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        for(int i=0; i<strlen(str); i++){
            push(&s, str[i]);
            enqueue(&q, str[i]);
        }
        if(cmp(&s, &q)) printf ("Yes\n");
        else printf ("No\n");
    }
}
