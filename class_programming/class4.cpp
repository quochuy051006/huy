#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char data;
    struct node*next;
}node;

node *top = NULL;
int curSize = 0;
int maxSize = 0;

void createStack(int size){
    while(top != NULL){
        node *tmp = top;
        top = top->next;
        free(tmp);
    }
    curSize = 0;
    maxSize = size;
    printf("OK\n");
}

void push(char c){
    if(curSize >= maxSize) {
        printf ("Stack full\n");
        return;
    }
    node *newNode = (node*) malloc(sizeof(node));
    newNode->data = c;
    newNode->next = top;
    top = newNode;
    curSize++;
    printf ("OK\n");
}

void pop(){
    if(top == NULL){
        printf("Stack empty\n");
        return;
    }
    node *tmp = top;
    top = top->next;
    printf ("%c\n", tmp->data);
    free(tmp);
    curSize--;
}

int main(){
    int i;
    while(scanf (" %d", &i) == 1){
        if(i == 0){
            printf ("quit");
            break;
        }
        else if(i == 1){
            int size;
            scanf (" %d", &size);
            createStack(size);
        }
        else if(i==2){
            char c;
            scanf (" %c", &c);
            push(c);
        }
        else if(i == 3){
            pop();
        }
    }
}
