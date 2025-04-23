#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
typedef struct PCB{
    int parent;
    struct node *children;
} PCB;

typedef struct node{
    int value;
    int child;
    struct node *next;
} node;
//got an error when I did not make the struct typedef
PCB PCB_TABLE[1000];

void initialize()
{
    for(int i = 0; i < 1000; i++)
    {
        PCB_TABLE[i].parent = -100;
        PCB_TABLE[i].children = NULL;
    }
}

void create(int p){
    //allocate PCB
    int q = -100;
    for(int i = 1; i < 1000; i++)
    {
        if(PCB_TABLE[i].parent == -100)
        {
            q = i;
            break;
        }
    }
    if(q == -100) { return; } // for no free spaces

    PCB_TABLE[q].parent = p;
    PCB_TABLE[q].children = NULL;
    node *mynode = (node*)malloc(sizeof(node)); //create a node 
    mynode->child = q;
    mynode->next = NULL;
    if(PCB_TABLE[p].children == NULL)
    {
        PCB_TABLE[p].children = mynode;
    }
    else {
        node *curr = PCB_TABLE[p].children;
        while(curr->next != NULL)
        {
            //to iterate the LL
            curr = curr->next;
        }
        curr->next = mynode;
    }
}

void destroy(int p)
{
    node* curr = PCB_TABLE[p].children;
    while(curr != NULL)
    {
        node *next_index = curr->next;
        destroy(curr->child); // recursive element to it
        free(curr);
        curr = next_index;
    }
    PCB_TABLE[p].parent = -100;
    PCB_TABLE[p].children = NULL;
}

void printList(int p){
    node* curr = PCB_TABLE[p].children;
    if(curr == NULL)
    {
        //handles empty list
        printf("The list is empty\n");
        return;
    }
    printf("Children of process %d : ", p);
    while(curr != NULL) // used for iteration purposes when going through the nodes
    {
        printf("%d ", curr->child);
        curr = curr->next;
    }
    printf("\n");
}

int main()
{
    double start, finish, elapsed;
    GET_TIME(start);
    initialize();
    for(int i = 0; i < 100; i++)
    {
        create(0);
        create(1);
        create(2);
    }
    printList(0);
    printList(1);
    printList(2);
    destroy(0);
    printf("List after destroy 0:\n");
    printList(0);
    printList(1);
    printList(2);
    GET_TIME(finish);
    elapsed = finish - start;
    printf("The code to be timed took %e seconds\n", elapsed);
    return 0;
}
