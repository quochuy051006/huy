#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char data[100];
    int rear, front;
}queue;

void initQueue(queue *q){
    q->front = q->rear = 0;
}

void enqueue(queue *q, char c){
    q->data[q->rear++] = c;
}

char dequeue(queue *q){
    return q->data[q->front++];
}

typedef struct stack
{
    queue q;
    int curSize;
    int maxSize;
}stack;

void initStack(stack *s, int size){
    initQueue(&s->q);
    s->curSize = 0;
    s->maxSize = size;
}

void push(stack *s, char c){
    if(s->curSize >= s->maxSize){
        printf ("Stack full\n");
        return;
    }
    enqueue(&s->q, c);
    for(int i=0 ; i<s->curSize; i++){
        enqueue(&s->q, dequeue(&s->q));
    } 
    s->curSize++;
    printf("OK\n");
}

void pop(stack *s){
    if(s->curSize > 0){
        printf ("%c\n", dequeue(&s->q));
        s->curSize--;
        return;
    }
    else printf ("Stack empty\n");
}

int isEmpty(stack *s){
    if(s->curSize <= 0) return 1;
    return 0;
}

int main(){
    int i;
    stack s;
    while (scanf (" %d", &i) == 1)
    {
        if(i==0){
            printf ("quit\n");
            return 0;
        }
        else if(i==1){
            int size;
            scanf(" %d", &size);
            initStack(&s, size);
            printf ("OK\n");
        }
        else if(i==2){
            char c;
            scanf(" %c",&c);
            push(&s, c);
        }
        else if(i==3){
            pop(&s);
        }
        else if(i==4){
            if(isEmpty(&s)) printf ("True\n");
            else printf ("False\n");
        }
    }  
}

