/*
 ============================================================================
 Name        : ArraySorter.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
	short val;
	char flag[13];
	struct NODE* next;
} NODE;

// Helper function to print a given linked list
void printList(struct NODE* head)
{
	struct NODE* ptr = head;
	while (ptr)
	{
		printf("%d : %s  —> ", ptr->val, ptr->flag);
		ptr = ptr->next;
	}

	printf("NULL");
}




int main(int argc, char *argv[]) {

	FILE *ptr_inStream;

	ptr_inStream=fopen("input_stream.bin","rb");  //open file to read in binary
	if (!ptr_inStream) {  // Print error opening file
		printf("Unable to open input stream!");
		return 1;
	}

	//	NODE testNode;
	//	testNode.val = 5;
	//	testNode.flag = "test";
	//
	//
	//	printf("Val: %d, Flag: %s\n", testNode.val, testNode.flag);

	//	for ( int i = 0; i < width; i++) {  //
	//			for (int j = 0; j < width; j++) {
	//				fread(&a, sizeof(a), 1, ptr_aBin);



	NODE* head;
	head = calloc(1, sizeof(NODE));

	fread(&head->val, sizeof(head->val), 1, ptr_inStream);
	fread(&head->flag, sizeof(head->flag), 1, ptr_inStream);
	//	fread(&head->val, sizeof(head->val), 1, ptr_inStream);
	//	fread(&head->flag, sizeof(head->flag), 1, ptr_inStream);
	//	fread(&head->val, sizeof(head->val), 1, ptr_inStream);
	//	fread(&head->flag, sizeof(head->flag), 1, ptr_inStream);
	//	fread(&head->val, sizeof(head->val), 1, ptr_inStream);
	//	fread(&head->flag, sizeof(head->flag), 1, ptr_inStream);
	head->next = NULL;
	printf("Val: %d, Flag: %s\n", head->val, head->flag);

	//printf("Int Size: %I64d;  Char Size: %I64d\n", sizeof(head->val), sizeof(head->flag));

	NODE* newNode;
	NODE* curr = head;

	newNode = calloc(1, sizeof(NODE));

	while ((fread(&newNode->val, sizeof(newNode->val), 1, ptr_inStream) != 0) && (fread(&newNode->flag, sizeof(newNode->flag), 1, ptr_inStream ) != 0)) {
		curr = head;
		//printf("Val: %d, Flag: %s\n", newNode->val, newNode->flag);
		while(curr->next != NULL) {

			if(newNode->val < head->val){
				newNode->next = &head;
				head = newNode;
				curr = head;
			} else if (newNode->val < curr->val) {
				newNode->next = curr->next;
				curr->next = newNode;
				curr = newNode;
			} else if (curr->next == NULL){
				newNode->next = curr->next;
				curr->next = newNode;
			}

			curr = curr->next;
		}




	}

	curr = head;
	while(curr != NULL) {
		printf("Val: %d, Flag: %s\n", curr->val, curr->flag);
		curr = curr->next;
	}

	printf("Flag: %s\n", head->flag);

	fclose(ptr_inStream);
	printf("End\n");
	return EXIT_SUCCESS;
}
