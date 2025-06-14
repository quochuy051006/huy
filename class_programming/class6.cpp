#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}tree;

void insert(tree **root, int n){
    tree *newNode = (tree*)malloc(sizeof(tree));
    newNode->data = n;
    if(*root == NULL){
        (*root) = newNode;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }
    if(n < (*root)->data){
        insert((&(*root)->left), n);
    }
    else if (n > (*root)->data)
    {
        insert((&(*root)->right), n);
    }
    else{
        printf ("dup");
    }
}

void inOrder(tree *root){
    if(root != NULL){
        inOrder(root->left);
        printf ("%3d", root->data);
        inOrder(root->right);
    }
}

void preOrder(tree*root){
    if(root != NULL){
        printf ("%3d", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(tree*root){
    if(root!=NULL){
        postOrder(root->left);
        postOrder(root->right);
        printf ("%3d", root->data);
    }
}

int main(){
    srand(time(NULL));
    tree *root = NULL;
    printf ("Inserted number:");
    for(int i=0; i<12; i++){
        int n = rand() % 20 + 1;
        printf (" %d", n);
        insert(&root, n);
    }
    printf ("\ninOrder\n ");
    inOrder(root);
    printf("\nPreorder\n ");
    preOrder(root);
    printf ("\npostOrder\n ");
    postOrder(root);
}