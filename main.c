#include <stdio.h>
#include <stdlib.h>



typedef struct{
  char name[100];
  int startTime;
  int executionTime;
}Process;



typedef struct{

 Process data;
 struct Node*next;
}Node;

typedef struct{

 Node *front, *rear;

}Queue;

//DEFINING NEW NODE//

 Node*newNode(Process value)
 {
     Node *n= (Node*) malloc(sizeof(Node));
     n->data=value;
     n->next=NULL;
     return n;
 }


  //INITIALIZING A NEW QUEUE//
void initializeQueue(Queue *q)
{
    q->front=q->rear=NULL;
}

  //PUTTING A NUMBER IN THE QUEUE//
void enqueue(Queue *q, Process value)
{
    Node *ptr=newNode(value);
     if(q->front==NULL)
        q->front=q->rear=ptr;
     else
     {
         q->rear->next=ptr;
         q->rear=ptr;
     }
}

  //REMOVING A NUMBER FROM THE QUEUE//
Process dequeue(Queue *q)
{
    Process slot;
     if(q->front==NULL)
        exit(1);
     else
     {
         slot=q->front->data;
         q->front=q->front->next;
         return slot;
     }
}


   //MAKING SURE QUEUE IS NOT EMPTY BEFORE OPERATIONS//
int isEmpty(Queue *q)
{
    if(q->front==NULL)
        return 1;
    return 0;
}

Process processarray[100];
int processn=0;
int numofslots;
char string[100];

void loadFile()
{
    FILE*f;
    f=fopen("file.txt","r");
    if(f != NULL)
    {fscanf(f,"%[^=]=%d",string,&numofslots);

        while (!feof(f))
        {
            fscanf(f,"%s %d %d",processarray[processn].name,&processarray[processn].startTime,&processarray[processn].executionTime);
            fscanf(f,"\n");
            processn++;
        }

        fclose(f);
    }
    else printf("File Not Found");
}

void roundRobin()
{
    Queue q;
    initializeQueue(&q);
    int i;
    int j;

    for(i=0; i<processn;i++)
         if(processarray[i].startTime==0)
           enqueue(&q,processarray[i]);

    for(j=0;j<numofslots;j++)
   {

         if(isEmpty(&q))
        {
            printf("\nidle\t (%d-->%d)",j,j+1);
         for(i=0;i<processn;i++)
            if(processarray[i].startTime==j+1)
            enqueue(&q,processarray[i]);
        }
        else
        {
            Process copy;
            copy=dequeue(&q);
            printf("\n%s\t (%d-->%d)",copy.name,j,j+1);
            copy.executionTime--;
            for(i=0;i<processn;i++)
               {
                if(processarray[i].startTime==(j+1))
                enqueue(&q,processarray[i]);}
            if(copy.executionTime==0)
                    printf("   %s   aborts",&copy.name);
            else
                    enqueue(&q,copy);



        }
   }
   printf("\nstop!\n");
}



int main()
{
    loadFile();
    roundRobin();
    return 0;
}
