#pragma once
#ifndef Contact
#define Contact
#define  MAX_NUMBER  20
#define MAX_NAME    40
#define MAX_COMPANY 40
#define MAX_ADDRESS 100
#define MAX_EMAIL   60
#define CONTACT_FROM_FILE 0
#define CONTACT_ADDED_MANUALLY 1
#define FOUND_CONTACT 1

//defining the structure
  struct  ContactList
 {
	 struct ContactList *next;
	 struct ContactList *prev;
	 char contactNumber [MAX_NUMBER];
	 char contactFirstName[MAX_NAME];
	 char contactSurName[MAX_NAME];
	 char contactCompany[MAX_COMPANY];
	 char contactEmail[MAX_EMAIL];
	 char contactAddress[MAX_ADDRESS];
 } ;//end of structure

  //functions declarations
  int showMenu();
 void insertContactInfo(struct ContactList*);
 int getSizeOfTheLinkedList(struct ContactList*);

 void insertIntoHead(struct ContactList* listHead);
 struct ContactList* getNewNode();
 void displayContactDetails();
 void printList(struct ContactList* list);

 void showAllContact();
 void insertContact(int option);
 void updateToFile(struct ContactList* list);
 void writeContactDetailsToFile(struct ContactList *contact);

 void editContact(struct ContactList* temp);
 void deleteContact();
 void searchContact(struct ContactList* head);
 void readDataFormFile();

 //end of function declarations
 ///Encrypting and decrypting
void encrypt_data(FILE* input_file, FILE* output_file, char key[]);
void encryptHelper();
void decrypt();

#endif