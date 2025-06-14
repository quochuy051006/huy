#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char data;
    struct node* next;
}node;

typedef struct stack
{
    node *top;
}stack;

void initStack(stack *s){
    s->top = NULL;
}

void push(stack *s, char c){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = c;
    newNode->next = (s->top);
    s->top = newNode;
}

char pop(stack *s){
    if(s->top == NULL) return '\0';
    node *tmp = s->top;
    s->top = s->top->next;
    char c = tmp->data;
    free(tmp);
    return c;
}

int empty(stack *s){
    return s->top == NULL;
}

typedef struct queue
{
    stack in;
    stack out;
    int curSize;
    int maxSise;
}queue;

void initQueue(queue *q, int size){
    initStack(&q->in);
    initStack(&q->out);
    q->curSize = 0;
    q->maxSise = size;
}

void pushQueue(queue *q, char c){
    if(q->curSize >= q->maxSise) {
        printf ("Queue full\n");
        return;
    }
    push(&q->in, c);
    q->curSize ++;
    printf ("OK\n");
}

void popQueue(queue *q){
    if(q->curSize <= 0){
        printf ("Queue empty\n");
        return ;
    }
    if(empty(&q->out)){
        while(!empty(&q->in)){
            push(&q->out, pop(&q->in));
        }
    }
    q->curSize --;
    printf ("%c\n", pop(&q->out));
}

int isEmpty(queue *q){
    return empty(&q->in) && empty(&q->out);
}

int main(){
    int i;
    queue q;
    while (scanf (" %d", &i) == 1)
    {
        if(i==0){
            printf ("quit\n");
            return 0;
        }
        else if(i==1){
            int size;
            scanf(" %d", &size);
            initQueue(&q, size);
            printf ("OK\n");
        }
        else if(i==2){
            char c;
            scanf(" %c",&c);
            pushQueue(&q, c);
        }
        else if(i==3){
            popQueue(&q);
        }
        else if(i==4){
            if(isEmpty(&q)) printf ("True\n");
            else printf ("False\n");
        }
    }  
}


