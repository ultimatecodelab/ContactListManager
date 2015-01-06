#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void insertAtHead(int x);
void print();
void reversePrint();
//struct Node* getNewNode(int x);
void insertAt(int x,int data);

void sort();

struct Node
{
	int data;
	char firstName[20+1];
	char lastName[20+1];
	char contactN[20+1];
	char address[20+1];
	char email[20+1];
	struct Node* prev;
	struct Node* next;

};
struct Node* head;
struct Node* getNewNode(int x)
{
	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
	newNode->prev=NULL;
	newNode->data= x;
	
	newNode->next = NULL;
	
	return newNode;
}
void insertAtHead(int x)
{
	struct Node* newNode = getNewNode(x);
	if(head==NULL)
	{
		head=newNode;
		return;
	}
	head->prev = newNode;
	newNode ->next= head;
	newNode->data = x;
	head = newNode;
}
void getIndex()
{
	sort();
}
void sort()
{

}
void insertAt(int index,int data)
{
	int i=0; 

	struct Node* temp = head;
	
	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
	newNode->data=data;
	
	if(index==1)
	{
		insertAtHead(data);
	}
	else
	{
		for(i=0;i<index-2;i++)
		{
			temp=temp->next;
			head->prev=newNode;
		}
		newNode->next=temp->next;
		temp->next=newNode;
		newNode->next->prev=newNode;
		newNode->prev=temp;
	}
}

void print()//forward
{
	struct Node* temp = head;
	printf("forward \t");
	while(temp!=NULL)
	{
		printf("%d ",temp->data);
		temp=temp->next;  
	}
	printf("\n");
	

}

void reversePrint()
{
	struct Node* temp = head;
	if(temp==NULL) return;

	printf("Reverse \t");
	while(temp->next!=NULL)
	{
		temp = temp ->next;
	}
	printf("hello");
	//Transversing backward using prev pointer
	while(temp!=NULL)
	{
		printf("%d ",temp->data);
		temp=temp->prev;
	}
	printf("\n");
}
void main1()
{
	head= NULL;
	
	insertAtHead(1); 
	insertAtHead(2); //print(); //reversePrint();
	insertAtHead(3); //print(); //reversePrint();
	insertAtHead(4); //print(); //reversePrint();
	insertAtHead(5); //print(); reversePrint();
	insertAt(1,0);
	insertAt(2,60);
	insertAt(7,1000);
	print();

	system("pause");
}

