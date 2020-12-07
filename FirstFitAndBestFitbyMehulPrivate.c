#include<stdio.h>
#include<stdlib.h>

struct Memory{
int BlockNumber;	//Unique Block Number
int BlockSize;		//Block Memeory Size
int status;			//status : To check if a particular block holds any process
struct Memory *next;
};
struct Memory *memoryPointer = NULL;

struct Process{
int ProcessNumber;			//Unique Process Number
int ProcessSize;			//Process Memeory Size
int AllocatedBlockNumber;	//Will tell which memory block number is assigned to it
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
	//STEP 1 : Travers Through All Processes one by one
	while(p!=NULL)
	{
		//STEP 2 : For Every Process, Check if There is Any Memeory Block Which can Accommodate That Particular Process
		m = memoryPointer;
		while(m!=NULL)
		{
			//STEP 3 : Check if BlockSize is >= than Process Size and If It Already Dosent Hold Any Process
			if(p->ProcessSize <= m->BlockSize && m->status != 1)
			{
				m->status = 1;    //Set status 1 to indicate that particular memory block contains a process
				p->AllocatedBlockNumber = m->BlockNumber; //Will store corrosponding Block number for every process
				printf("\nProcess P[%d] of Size(%d) Allocated Block Number B[%d] of Size(%d) ",p->ProcessNumber,p->ProcessSize,m->BlockNumber,m->BlockSize);
				break;
			}
			m=m->next;
		}

		//STEP 4 : If No Block Has Been Assigned Then It Will Have Default Value -1
		if(p->AllocatedBlockNumber == -1)
		{
			printf("\nProcess P[%d] of Size(%d) Was Not Allocated Any Block",p->ProcessNumber,p->ProcessSize);
		}
		p=p->next;
	}

	//Reset The Values for next Algorithm
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

	//STEP 1 : Travers Through All Processes one by one
	while(p!=NULL)
	{
		//STEP 2 : For Every Process, Check if There is Any Memeory Block Which can Accommodate That Particular Process
		m = memoryPointer;
		while(m!=NULL)
		{
			//STEP 3 : Check if BlockSize is >= than Process Size and If It Already Dosent Hold Any Process
			if(p->ProcessSize <= m->BlockSize && m->status != 1)
			{
				//STEP 4 : For Every Process Record All The Memory Blocks Eligible To Store the Process In An Array
				recorderArrayOfBlockSize[index] = m->BlockSize;
				index++;
			}
			m=m->next;
		}

		//STEP 5 : If index == 0 then There Was no Memeory Block Eligible for This Block. Hence This Process Is Not Allocated
		if(index != 0)
		{
			//STEP 6 : Find The Block With The Smallest Block Size Out of All Eligible Blocks
			smallestBlockSize = recorderArrayOfBlockSize[0];
			for(i=1;i<index;i++)
			{
				if(recorderArrayOfBlockSize[i]<smallestBlockSize)
				{
					smallestBlockSize = recorderArrayOfBlockSize[i];
				}
			}

			//STEP 7 : See Where Is The 'smallestBlockSize' Pointing At in Memeory Block Linked List
			m = memoryPointer;
			while(m != NULL)
			{
				if(m->BlockSize == smallestBlockSize)
				{
					break;
				}
				m = m->next;
			}

			//STEP 8 : Assign That 'BlockNumber' To The Process ie 'AllocatedBlockNumber'
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
