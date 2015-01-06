/*
	Advance C Programming
	Encrypted (XOR) ContactList Manager created using Dynamic memory allocation/pointers/linkedlist
	Developed By : Arjun Kharel
	Id: G00298984@gmit.ie
	IDE: Visual Studio 2010
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ContactList.h"
#include "SortContact.h"
#define FIRST_LINE 1
int showMenu();

struct ContactList* head;//created the global head pointer so i can access from any function
//This array is used when reading contacts from the file and separating the fields by commas. It's a temp storage.
char *contactInformation[60+1];

struct ContactList* getNewNode(){
	struct ContactList* newNode = (struct ContactList*)malloc(sizeof(struct ContactList));
	newNode->next=NULL;
	newNode->prev=NULL;
	return newNode;
}
int getSizeOfTheLinkedList(struct ContactList *temp)
{
	int counter=0;
	while(temp!=NULL)
	{
		//increment the counter and return the size 
		counter++;
		temp=temp->next;
	}
	return counter;

}
void insertContactInfo(struct ContactList* temp,int whichOne)
{
	//getting information from the user
	if(whichOne==CONTACT_ADDED_MANUALLY)
	{
		fflush(stdin);
		printf("Enter Contact Number:" );
		gets(temp->contactNumber);
		while(strlen(temp->contactNumber)<1)
		{
			printf("\nYou must enter the contact number:" );
			gets(temp->contactNumber);
		}
		printf("\nBoth first name and last are case sensetive. While sorting the list they do matter \n");
		
		printf("Enter Contact first name:" );
		gets(temp->contactFirstName);

		while(strlen(temp->contactFirstName)<1)
		{
			printf("Enter Contact first name:" );
			gets(temp->contactFirstName);
		}
		
		printf("Enter Contact Second Name:" );
		gets(temp->contactSurName);

		while(strlen(temp->contactSurName)<1)
		{
			printf("Enter Contact Second Name:" );
			gets(temp->contactSurName);
		}

		printf("Enter Contact Company:" );
		gets(temp->contactCompany);
		while(strlen(temp->contactCompany)<1)
		{
			printf("Enter Contact Company:" );
			gets(temp->contactCompany);
		}

		printf("Enter Contact Email:" );
		gets(temp->contactEmail);
		while(strlen(temp->contactEmail)<1)
		{
			printf("Enter Contact Email:" );
			gets(temp->contactEmail);
		}

		printf("Enter Contact Address:" );
		gets(temp->contactAddress);
		while(strlen(temp->contactAddress)<1)
		{
			printf("Enter Contact Address:" );
			gets(temp->contactAddress);
		}

		//adding manually added contacts into the file
		writeContactDetailsToFile(temp);
		printf("\n\t Contact saved successfully to the file\n\t press 1 to view your newly created contact from the menu");
	}
	else
	{
		strcpy(temp->contactNumber,contactInformation    [0]);
		strcpy(temp->contactFirstName,contactInformation [1]);
		strcpy(temp->contactSurName,contactInformation   [2]);
		strcpy(temp->contactCompany,contactInformation   [3]);
		strcpy(temp->contactEmail,contactInformation     [4]);
		strcpy(temp->contactAddress,contactInformation   [5]);
	}
	//printf("Inserted Successfully\n");
	
}//end of insertion
/*
THIS IS ONE OF THE IMPORTANT FUNCTION AND BEST FEATURE OF MY APPLICATION. WHEN YOUR READINT THE CONTACT FROM THE FILE OR YOUR CREATING MANUALLY
IT SORTED THE CONTACT AT THAT TIME BASED ON THEIR SECOND NAME AND LINKS THE POINTERS REFERENCES. IT FINDS THE CORRECT PLACE TO INSERT BEFORE LINKING
THE POINTER TO ONE ANOTHER.
*/
void insertContact(int option)
{
	struct ContactList* newNode = getNewNode();//contains the reference to newly created node..
	struct ContactList* curr=head;
	struct ContactList* tail= 0 ;
	int counter=1;
	if(head==NULL)
	{
		head=newNode;
		insertContactInfo(newNode,option);
		return;
	}
	else
	{
		struct ContactList* curr=head;
		insertContactInfo(newNode,option);
			while(curr!=NULL)//TRAVERSING THE LIST TO FIND THE CORRECT INSERTION POSITION
			{
				if(strcmp(newNode->contactSurName,curr->contactSurName)>=1)
				{
					tail=curr;
					curr=curr->next;	
				}
				else
				{
					break;
				}
			}//end of while
			if(curr==head)//IF THE CURR HAPPENS TO BE POINTING AT HEAD. THEN SIMPLY CHANGE HEAD TO NEWNODE.
			{
				head->prev=newNode;
				newNode->next=head;
				head=newNode;
			}
			else//CHANGING LINKS HERE..
			{
				newNode->prev=tail;
				newNode->next=curr;
				newNode->prev->next=newNode;
				curr=head;
			}	
	}
	
}
void print_list( struct ContactList *list )
{
    while( list != NULL ) {
        printf( "\n\t\t%s", list->contactFirstName );
        list = list->next;
    }
}
//function that calls the sort method for sorting.
void sortHelper()
{
	struct ContactList* list = head;// pointing to the first element of the list or head
	struct ContactList* sortedList=NULL;// initially sorted list is empty or its an empty list
	printf("\n\t\tOriginal list \n");
				
	print_list(list);
	printf("\n----------------------------------------------------------");
	printf("\n\t\tNew list contacts were sorted by first name\n");
	sortedList=sort(list);//calling the sort function that recursevely sort the list and return the sorted one
	print_list(sortedList);
	head=head;//This is very important to set the head(global var) to it's original state.If i don't do this then references will be mixed up while sorting the element.
}
/*
A simple function that takes in the original list and sort them by their first name. Initially list were sorted by secondName using my own version of insertion sort.
This function sort the list using recursevely
*/
struct ContactList *sort( struct ContactList *start )
{
	if( start == NULL ) return NULL;
    start->next = sort(start->next);
    if( start->next != NULL && strcmp(start->contactFirstName,start->next->contactFirstName)>=1) {
        start = move( start );
		
    }
	head=start;
    return start;
}
/*
The following function moves the top item in the linked list to its correct position.The item that was the second item in the list becomes the top item.
*/
struct ContactList* move( struct ContactList *x )
{
    struct ContactList *n, *p, *ret;

    p = x;
    n = x->next;
    ret = n;
    while( n != NULL && strcmp(x->contactFirstName,n->contactFirstName)>=1){
        p = n;
        n =  n->next;
    }
    /* we now move the top item between p and n */
    p->next = x;
    x->next = n;
    return ret;
}
/*
This function is for editing the contact.
You much specify the index number of the contact  inorder to edit/delete/update BECAUSE in reality we can't use firstname/lastname because you have 
another contact with the same fields. I could have used contact number as a unique id but its again its complex to type the entire number to make any changes
simply doesn't make sense therefore i came up with index/Id to elimate this problem...
*/
void editContact(struct ContactList* listHead)
{
	int index=0; 
	char option ;
	int listSize = getSizeOfTheLinkedList(head);
	//traversing through the list till (n-1) and adjusting the pointer
	int i = 0;
	printf("Enter index: ");
	scanf("%d",&index);
	if(index==0)
	{
		printf("index should greater than 0 and less then max(size)");
	}
	else if(index>listSize)
	{
		printf("Invalid out of range. The max index is %d",listSize);
	}
	//traversing through the list till (n-1) times to find the correct contactto modify
	if(index>=1 && index<=getSizeOfTheLinkedList(head))
	{
		for(i=0;i<index-1;i++)
		{
			listHead=listHead->next;
		}
	
		printf("\nCurrent information");
		displayContactDetails(listHead);
		//printf("\n\nF(FirstName)/L(LastName)/N(Number)/E(Email)/C(Company)/A(Address) 0(exit)");
		scanf("%c",&option);
		while(option!='0')
		{
			fflush(stdin);
	
			switch (option)
			{
			case 'F':
			case'f':
			
				printf("\n\tCurrent name is : %s",listHead->contactFirstName);
				printf("\n\tEnter new name: ");
				gets(listHead->contactFirstName);
				printf("\n\tFirst Name updated to: %s",listHead->contactFirstName);
			break;
			case 'L':
			case 'l':
				printf("\n\tCurrent name is : %s",listHead->contactSurName);
				printf("\n\tEnter new surname: ");
				gets(listHead->contactSurName);
				printf("\n\tLast Name  updated to: %s",listHead->contactSurName);
				break;
			case 'N':
			case 'n':
				printf("\n\tCurrent number is : %s",listHead->contactNumber);
				printf("\n\tEnter new number: ");
				gets(listHead->contactNumber);
				printf("\n\tNumber updated to: %s",listHead->contactNumber);
				break;
			case 'E':
			case 'e':
				printf("\n\tCurrent E-mail is : %s",listHead->contactEmail);
				printf("\n\tEnter new Email: ");
				gets(listHead->contactEmail);
				printf("\n\tEmail updated to: %s",listHead->contactEmail);
				break;
			case 'C':
			case 'c':
				printf("\n\tCurrent Company name is : %s",listHead->contactCompany);
				printf("\n\tEnter new company name: ");
				gets(listHead->contactCompany);
				printf("\n\tCompany name updated to: %s",listHead->contactCompany);
				break;
			case 'A':
			case 'a':
				printf("\n\tCurrent Address is : %s",listHead->contactAddress);
				printf("\n\tEnter new Address: ");
				gets(listHead->contactAddress);
				printf("\n\tAddress updated to: %s",listHead->contactAddress);
				break;
			default:
				printf("\nInvalid option selected");

		
			}
				printf("\n\nF(FirstName)/L(LastName)/N(Number)/E(Email)/C(Company)/A(Address) 0(exit)");
			scanf("%c",&option);
		}
		updateToFile(head);
		}

}
//This function takes in the contact and display it's relevant information for the specific one
void displayContactDetails(struct ContactList* contact)
{
		printf("\n%-10s%-10s%-8s%-10s%-20s%-10s ","Number","FName","SName","Company","Email "," Address");
		printf("\n-------------------------------------------------------------------------------");
		printf("\n%-10s %-10s%-8s%-10s%-20s%-10s ",contact->contactNumber,contact->contactFirstName,contact->contactSurName,contact->contactCompany,contact->contactEmail,contact->contactAddress);
}
void deleteContact()
{
	struct ContactList* temp = head;
	struct ContactList* curr;
	int i = 0;
	int index=0; 
	printf("Enter index: ");
	scanf("%d",&index);

	printf("\n\tBefore");
	if(index>=1 && index<=getSizeOfTheLinkedList(head))
	{
		
	//display the contacts before deleting.
		showAllContact();
		if(index==1){
			head=temp->next;
			free(temp);
			showAllContact();
		}
		else
		{
			//traversing the list to find the position of the node and to delete.
			for(i=1;i<index-1;i++){
				temp=temp->next;
			}
			curr = temp->next;//Once i have deleted the contact i'm changing the links here..
			temp->next=curr->next;
			free(curr);
			printf("\n\tAfter");
			showAllContact();
			//update changes to the file
		}
		updateToFile(head);//ONCE THE CONTACT HAS BEEN DELETED I HAVED MADE CHANGES TO MY CSV FILE TOO.
	}
	else
	{
		printf("\nInvalid index entered, please enter the valid index of a contact ");
	}
	

}
/*
Display all the contacts
*/
void showAllContact()
{
	
	int indexTracker= 0 ;
	struct ContactList* temp = head;
	//readDataFormFile();
	if(temp==NULL)
	{
		printf("\n-------------------------------------------------------------------------------");
		printf("\n\t contact list empty");
		printf("\n-------------------------------------------------------------------------------");
		
	}
	else
	{
		printf("\n-------------------------------------------------------------------------------");
		printf("\n%-8s%-10s%-10s%-8s%-10s%-20s%-10s\n","Index","Number","FName","SName","Company","Email "," Address");
		printf("\n-------------------------------------------------------------------------------");
		while(temp!=NULL)
		{
			indexTracker++;
			printf("\n%-5d%-10s %-12s%-8s%-10s %-20s %-10s",indexTracker,temp->contactNumber,temp->contactFirstName,temp->contactSurName,temp->contactCompany,temp->contactEmail,temp->contactAddress);
			temp=temp->next;  
		}
		printf("\nAll the contact were sorted by second name while reading from the file.The ordering of contacts doesn't matter in the file because I have sorted the entire contacts while I am creating the contact List (NODE)");
	}
}
void main()
{	
	int iChoice;
	readDataFormFile();
	
	do
	{
		iChoice = showMenu();
		switch(iChoice)
		{
		case 1:
			{
				fflush(stdin);
				showAllContact();
				//readDataFormFile();
				break;
			}
		case 2:
			{
				fflush(stdin);
				insertContact(CONTACT_ADDED_MANUALLY);
				break;
			}
		case 3:
			fflush(stdin);
			editContact(head);
			break;

		case 4:
			//searchContactByFirstName();
			fflush(stdin);
			searchContact(head);
			break;
		case 5:
			sortHelper();
			
				break;
		case 6:
			deleteContact();
			break;
		case 7:
			encryptHelper();
			break;
		case 8:
			decrypt();
			break;
		default:
			{
				printf("\nInvalid option selected");
				break;
			}
		}// end switch(iChoice)

	} while(iChoice != 9);//while 
	
}
void readDataFormFile()
{
	int fieldCounter = 0;
	int index=0 ;
	int lineNumber = 0;

	char firstName[20+1];
	FILE* file =fopen("contacts.csv","r");
	char buffer[200];
	char * pch;
	if(file!=NULL){
	while(fgets(buffer,100,file)!=NULL)
	{
		fieldCounter=0;
		lineNumber++;//line number counter for avoiding first line / header
		pch = strtok (buffer,",");//separating the information by comma.
		while(pch!=NULL)
		{
			contactInformation[fieldCounter]=pch;
			fieldCounter++;
			pch = strtok (NULL, ","); 
		}//inner while	
		
		if(lineNumber!=FIRST_LINE)
		{
			insertContact(CONTACT_FROM_FILE);
		}
	}//outer while
	}
	else{
		printf("Contact List is empty -> No CSV file detected");
	}
}
void searchContact(struct ContactList* temp){
	int foundContact = 0;
	char nameToSearch[20+1];
	char option;
	struct ContactList* headPointer=temp;

	printf("\nSearch By FirstName ( F ) / ContactNumber ( C) ");
	scanf("%c",&option);
	
	switch(option){
	case 'F':
	case 'f':
		//search by firstName
	printf("\nEnter the name or substr you would like to  search for: ");
	scanf("%s",&nameToSearch);
	
	while(headPointer!=NULL)
	{
		//indexTracker++;
		if(strstr((headPointer->contactFirstName),(nameToSearch))!=NULL){
			printf("\n%-10s %-10s%-8s%-10s%-20s%-10s ",headPointer->contactNumber,headPointer->contactFirstName,headPointer->contactSurName,headPointer->contactCompany,headPointer->contactEmail,headPointer->contactAddress);
			foundContact=1;
		}
		headPointer=headPointer->next;
	}//while
	if(foundContact==0){
			printf("Not found - This comparasion is case SENSATIVE. TRY: Eg. Arj for Arjun , chael for Michael , ohn for John etc...\n ");
	}
		break;
	case 'C':
	case 'c':
		printf("\nEnter contact Number or part of number eg.( 87 / 89 / 83 / 85) :  ");
		scanf("%s",&nameToSearch);
		while(headPointer!=NULL)
		{
			//indexTracker++;
			if(strstr((headPointer->contactNumber),(nameToSearch))!=NULL){
				printf("\n%-10s %-10s%-8s%-10s%-20s%-10s ",headPointer->contactNumber,headPointer->contactFirstName,headPointer->contactSurName,headPointer->contactCompany,headPointer->contactEmail,headPointer->contactAddress);
				foundContact=1;
			}
			headPointer=headPointer->next;
		}//while
		if(foundContact==0){
				printf("No contact number found");
		}

			break;
	default:
		printf("Invalid option entered. Should be C/F");
		return;

	}//switch
}
void writeContactDetailsToFile(struct ContactList* temp)
{
	FILE* inFile;
	inFile=fopen("contacts.csv","a+");

	//This means contact list csv file doesn't contain anything at all. EMPTY file
	//Therefore need to add the header eg. FirstName / SurName etc..
	//If the contact that is to be written into the file happens to be the first one then write header first and write contact details
	if(getSizeOfTheLinkedList(head)==1)
	{
		fprintf(inFile,"%s,","Contact Number");
		fprintf(inFile,"%s,","First Name");
		fprintf(inFile,"%s,","Second Name");
		fprintf(inFile,"%s,","Company");
		fprintf(inFile,"%s,","Email");
		fprintf(inFile,"%s\n","Address");
	}
	//writing/apending the manually created contact to the file
	fprintf(inFile,"%s,",temp->contactNumber);
	fprintf(inFile,"%s,",temp->contactFirstName);
	fprintf(inFile,"%s,",temp->contactSurName);
	fprintf(inFile,"%s,",temp->contactCompany);
	fprintf(inFile,"%s,",temp->contactEmail);
	fprintf(inFile,"%s%s",temp->contactAddress,"\n");
	
	fclose(inFile);
}
void updateToFile(struct ContactList* list)
{
	FILE* inFile;
	//Headers
	inFile=fopen("contacts.csv","w");
	fprintf(inFile,"%s,","Contact Number");
	fprintf(inFile,"%s,","First Name");
	fprintf(inFile,"%s,","Last Name");
	fprintf(inFile,"%s,","Company");
	fprintf(inFile,"%s,","Email");
	fprintf(inFile,"%s\n","Address");
	//Headers
	while(list!=NULL)
	{
		fprintf(inFile,"%s,",list->contactNumber);
		fprintf(inFile,"%s,",list->contactFirstName);
		fprintf(inFile,"%s,",list->contactSurName);
		fprintf(inFile,"%s,",list->contactCompany);
		fprintf(inFile,"%s,",list->contactEmail);
		fprintf(inFile,"%s",list->contactAddress);
		printf("\n");
		list=list->next;
	}
	fclose(inFile);
	printf("\nSuccessfully updated the changes to the file");
}
int showMenu()
{
	int iC;
	
	printf("\n\n\t\tWelcome");
	printf("\n\n\t 1. Show all contacts");
	printf("\n\n\t 2. Add New contact");
	printf("\n\n\t 3. Edit Contact");
	printf("\n\n\t 4. Seach contact by Name /  Number");
	printf("\n\n\t 5. Sort Contact - FirstName ");
	printf("\n\n\t 6. Delete Contact");
	printf("\n\n\t 7. Encrypt csv file");
	printf("\n\n\t 8. Decrypt csv File");
	printf("\n\n\t 9. Exist");
	printf("\n\n\t Your Choice: ");

	fflush(stdin);
	scanf("%d", &iC);

	return(iC);
} // end showMenu
void encryptHelper(){

	FILE* input =fopen("contacts.csv","r");
	if(input==NULL)
	{
		printf("Contact File not found!!!, please create your csv file first  (contacts.csv)");
	}
	else{
		FILE* output = fopen("encrypted.csv","w");
		char key[] ={"1201"};//key used for both encrypting the decrypting
		encrypt_data(input, output, key);
		printf("Successfully encrypted the file --> encrypted.csv");
		fclose(input);
		fclose(output);
	}
	
}
void encrypt_data(FILE* input_file, FILE* output_file, char key[])
{
	int key_count = 0; //Used to restart key if strlen(key) < strlen(encrypt)
	int encrypt_byte;
	while( (encrypt_byte = fgetc(input_file)) != EOF) //Loop through each byte of file until EOF
	{
		//XOR the data and write it to a file
		fputc(encrypt_byte ^ key[key_count], output_file);
		//Increment key_count and start over if necessary
		key_count++;
		if(key_count == strlen(key))
			key_count = 0;
	}
	
}
//Decrypting the information
void decrypt()
{
	FILE* input =fopen("encrypted.csv","r");
	if(input==NULL)
	{
		printf("File doesn't exist, encrypted file should exist first inorder to decrypt. please encrypt the file first");
	}
	else{
		FILE* output = fopen("decrypted.csv","w");
		char key[] ={"1201"};
		encrypt_data(input, output, key);
		printf("Successfully decrypted the file --> decrypted.csv");
		fclose(input);
		fclose(output);
	}
}