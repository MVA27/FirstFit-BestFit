#include<stdio.h>
#include<stdlib.h>

struct Memory{
int BlockNumber;
int BlockSize;
int status;
struct Memory *next;
};
struct Memory *memoryPointer = NULL;

struct Process{
int ProcessNumber;
int ProcessSize;
int AllocatedBlockNumber;
struct Process *next;
};
struct Process *processPointer = NULL;

void createProcess()
{
    struct Process *p = (struct Process *)malloc(sizeof(struct Process));
    printf("\nEnter Process Number : ");
    scanf("%d",&p->ProcessNumber);

    printf("\nEnter Memory Size : ");
    scanf("%d",&p->ProcessSize);

	p->AllocatedBlockNumber = -1;
    p->next=NULL;

    if(processPointer == NULL){
        processPointer = p;
    }

    else{
		struct Process *temp = processPointer;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = p;
    }
}

void createMemeoryBlock()
{
    struct Memory *p = (struct Memory *)malloc(sizeof(struct Memory));
    printf("\nEnter Block Number : ");
    scanf("%d",&p->BlockNumber);

    printf("\nEnter Block Size : ");
    scanf("%d",&p->BlockSize);

	p->status = 0;
    p->next=NULL;

    if(memoryPointer == NULL){
        memoryPointer = p;
    }

    else{
		struct Memory *temp = memoryPointer;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = p;
    }
}


void main()
{
	int i,numberOfProcess,numberOfBlocks;

	//Data Input
    printf("\nENTER THE NUMBER OF PROCESS : ");
    scanf("%d",&numberOfProcess);

    for(i=1;i<=numberOfProcess;i++){
        createProcess();
    }

	printf("\nENTER THE NUMBER OF Blocks : ");
    scanf("%d",&numberOfBlocks);

    for(i=1;i<=numberOfBlocks;i++){
        createMemeoryBlock();
    }

	//Dispaly Data
	struct Process *p = processPointer;
	struct Memory *m = memoryPointer;
    while(p != NULL){
        printf(" P[%d]size(%d) ",p->ProcessNumber,p->ProcessSize);
        p = p->next;
    }
	printf("\n");
	while(m != NULL){
        printf(" B[%d]size(%d) ",m->BlockNumber,m->BlockSize);
        m = m->next;
    }

	//Main Logic
	p = processPointer;
	m = memoryPointer;

	printf("\nACCORDING TO FIRST FIT ALGORITHM ::::::::::::::::::");
	while(p!=NULL)
	{
		m = memoryPointer;
		while(m!=NULL)
		{
			if(p->ProcessSize <= m->BlockSize && m->status != 1)
			{
				m->status = 1;
				p->AllocatedBlockNumber = m->BlockNumber;
				printf("\nProcess P[%d] of Size(%d) Allocated Block Number B[%d] of Size(%d) ",p->ProcessNumber,p->ProcessSize,m->BlockNumber,m->BlockSize);
				break;
			}
			m=m->next;
		}

		if(p->AllocatedBlockNumber == -1)
		{
			printf("\nProcess P[%d] of Size(%d) Was Not Allocated Any Block",p->ProcessNumber,p->ProcessSize);
		}
		p=p->next;
	}

	p = processPointer;
	while(p!=NULL)
	{
		p->AllocatedBlockNumber = -1;
		p=p->next;
	}

	m = memoryPointer;
	while(m != NULL)
	{
		m->status = 0;
        m = m->next;
    }
	
	printf("\n\nACCORDING TO BEST FIT ALGORITHM ::::::::::::::::::");

	p = processPointer;
	m = memoryPointer;
	int recorderArrayOfBlockSize[numberOfBlocks],index = 0,smallestBlockSize;

	while(p!=NULL)
	{
		m = memoryPointer;
		while(m!=NULL)
		{
			if(p->ProcessSize <= m->BlockSize && m->status != 1)
			{
				recorderArrayOfBlockSize[index] = m->BlockSize;
				index++;
			}
			m=m->next;
		}

		if(index != 0)
		{
			smallestBlockSize = recorderArrayOfBlockSize[0];
			for(i=1;i<index;i++)
			{
				if(recorderArrayOfBlockSize[i]<smallestBlockSize)
				{
					smallestBlockSize = recorderArrayOfBlockSize[i];
				}
			}

			m = memoryPointer;
			while(m != NULL)
			{
				if(m->BlockSize == smallestBlockSize)
				{
					break;
				}
				m = m->next;
			}

			p->AllocatedBlockNumber = m->BlockNumber;
			printf("\nProcess P[%d] of Size(%d) Allocated Block Number B[%d] of Size(%d) ",p->ProcessNumber,p->ProcessSize,m->BlockNumber,m->BlockSize);
			index = 0;
			m->status = 1;
		}

		if(p->AllocatedBlockNumber == -1)
		{
			printf("\nProcess P[%d] of Size(%d) Was Not Allocated Any Block",p->ProcessNumber,p->ProcessSize);
		}
		p=p->next;
	}
}
