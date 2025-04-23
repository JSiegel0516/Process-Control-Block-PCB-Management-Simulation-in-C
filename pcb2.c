#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
/*
p = parent
fs = first child
ys = younger sibling
os = older sibling
*/
typedef struct PCB{
    int p, fs, ys, os;
} PCB;

PCB PCB_TABLE[1000];

void initialize(){
    for(int i = 0; i < 1000; i++)
    {
        PCB_TABLE[i].p = -100;
        PCB_TABLE[i].fs = -100;
        PCB_TABLE[i].ys = -100;
        PCB_TABLE[i].os = -100;
    }
}

void create(int p)
{
    int q = -100;
    for(int i = 1; i < 1000; i++)
    {
        if(PCB_TABLE[i].p == -100)
        {
            q = i;
            break;
        }
    }
    if(q == -100) { return; } //no free space
    PCB_TABLE[q].p = p;
    PCB_TABLE[q].fs = -100;
    PCB_TABLE[q].ys = -100;
    PCB_TABLE[q].os = -100;
    if(PCB_TABLE[p].fs == -100) { PCB_TABLE[p].fs = q; }
    else {
        int curr = PCB_TABLE[p].fs;
        while(PCB_TABLE[curr].ys != -100)
        {
            curr = PCB_TABLE[curr].ys;
        }
        PCB_TABLE[curr].ys = q;
        PCB_TABLE[q].os = curr;
    }

}

void destroy(int p)
{
    while(PCB_TABLE[p].fs != -100)
    {
        int next = PCB_TABLE[PCB_TABLE[p].fs].ys;
        destroy(PCB_TABLE[p].fs);
        PCB_TABLE[p].fs = next;
    }
    
    if(PCB_TABLE[p].os != -100)
    {
        PCB_TABLE[PCB_TABLE[p].os].ys = PCB_TABLE[p].ys;
    } else {
        if(PCB_TABLE[p].p != - 100)
        {
            PCB_TABLE[PCB_TABLE[p].p].fs = PCB_TABLE[p].ys;
        }

    }

    if(PCB_TABLE[p].ys != -100)
    {
        PCB_TABLE[PCB_TABLE[p].ys].os = PCB_TABLE[p].os;
    }
    PCB_TABLE[p].p = -100;
    PCB_TABLE[p].fs = -100;
    PCB_TABLE[p].ys = -100;
    PCB_TABLE[p].os = -100;
}

void printList(int p)
{
    if(PCB_TABLE[p].fs == -100) { 
        printf("List is empty\n");
        return; 
    } //no child
    printf("Child of process %d: ", p);
    int c = PCB_TABLE[p].fs;
    while(c != -100)
    {
        printf("%d ", c);
        c = PCB_TABLE[c].ys;
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
