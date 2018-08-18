#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int id;          //Node ID/value
    struct node * esq; //Left child, always smaller than the father.
    struct node * dir; //Right child, always bigger than the father.   
}Node;

typedef struct queueNode{
    struct node * treeNode;
    struct queueNode * next;
}QNode;

typedef struct queue{
    struct QNode * start;
    struct QNode * end;
}Queue;

Queue * createQueue(void){
	Queue * new = (Queue*) malloc(sizeof(Queue));
    new->start = new->end = NULL;
	return new;
}

int isEmpty(Queue * q){
	return (!q->start);
}

void push(Queue * q, Node * node){
    QNode * newNode = (QNode *) malloc(sizeof(QNode));
    newNode->treeNode = node;
    newNode->next=NULL;
    if(isEmpty(q)){
        q->start = newNode;
        q->end = newNode;
    }
    else{
        QNode * aux = q->end;
        aux->next = newNode;
        q->end = newNode;        
    } 
}
Node * pop(Queue * q){
	if(isEmpty(q)) return NULL;
    
    QNode * startQ = q->start;
    Node * popped = startQ->treeNode;   	
	q->start = startQ->next;

    if(!startQ) q->end = NULL;
    free(startQ);
    return popped;
}


//Begins a new tree.
Node * initialize(){
    Node * tree = NULL;
    return tree;
}

//Creates a new node.
Node * createNode(int num){
    Node * newNode = (Node *) malloc(sizeof(Node));
    newNode->dir = newNode->esq = NULL;
    newNode->id = num;
    return newNode;
}

//Destroys the whole tree.
void destroyTree(Node * t){
    if(t != NULL){ //Could also use if(t){}
        destroyTree(t->esq);
        destroyTree(t->dir);
        free(t);
    }
}

void printDepth(Node * t){
    if(!t) return;
    Queue * q = createQueue();
    push(q, t);
    while(!isEmpty(q)){
        Node * aux = pop(q);
        printf("%d",aux->id);
        if(aux->esq) push(q,aux->esq);
        if(aux->dir) push(q, aux->dir);
    }
}

Node * searchNode(Node * t, int num){
    if(!t) return NULL; //Empty tree.
    if(num == t->id) return t; //Found it!
    if(num < t->id) return searchNode(t->esq, num); //Look for it in the left subtree.
    else return searchNode(t->dir, num); //Look for it in the right subtree.
}

Node * insertNode(Node * t, int num){
    if(!t) t = createNode(num);            
    else if(num < t->id) t->esq = insertNode(t->esq, num); //Inserts in the left subtree.
    else if(num > t->id) t->dir = insertNode(t->dir, num); //Inserts in the right subtree.
    return t;   
}

Node * removeNode(Node * t, int num){
    if(!t) return NULL;
    if(num < t->esq->id) t->esq = removeNode(t->esq, num); //Node is in the left subtree.
    else if(num > t->dir->id) t->dir = removeNode(t->dir, num); //Node is in the right subtree.
    
    else{
        //Case 1: leaf node, that is, no children.
        if((!t->dir) && (!t->esq)){
            free(t);
            t = NULL;
        }
    

        //Case 2.1: the tree contains left children only.
        else if(!t->dir){
           Node * aux =  t;
           t = t->esq; //New left child
           free(aux);  //Removes node
        }

        //Case 2.2: the tree contains right children only.
        else if(!t->esq){
            Node * aux = t;
            t = t->dir; //New right child
            free(aux);  //Removes node
        }

        //Case 3: the tree contains both left and right children.
        else{
            Node * newFather = t->esq;
            //Look for the biggest element in the left tree.
            while(newFather->dir != NULL){
                newFather = newFather->dir;
            }

            //Copy the new father value to this node. 
            int aux = t->id;
            t->id = newFather->id;
            newFather->id = aux;
            
            //Remove node.
            t->esq = removeNode(t,num);            
        }
    }
    return t;
}

int main(){
    return 0;
}