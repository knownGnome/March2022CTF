/*
 ============================================================================
 Name        : LinkListSorter.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/*

	unsigned short num = 0xaabb;
	unsigned short swapped = (num >> 8) | (num << 8);

	printf("Num == %x | Swp == %x", num, swapped);

 */
typedef struct node {
	unsigned short value;// data field
	unsigned short length;
	unsigned short flink;
	unsigned char *flagPieces;
	struct node *next;
} node;

unsigned short byteSwap(unsigned short input) {
	printf("in %02x \n", input);
	unsigned short output = (input >> 8) | (input << 8);
	printf("out %02x \n", output);
	return output;
}


node* selectionSort(node* head)
{
	node *a, *b, *c, *d, *temp;

	a = b = head;

	// While b is not the last node
	while (b->next) {

		c = d = b->next;

		// While d is pointing to a valid node
		while (d) {

			if (b->value > d->value) {

				// If d appears immediately after b
				if (b->next == d) {

					// Case 1: b is the head of the linked list
					if (b == head) {

						// Move d before b
						b->next = d->next;
						d->next = b;

						// Swap b and d pointers
						temp = b;
						b = d;
						d = temp;

						c = d;

						// Update the head
						head = b;

						// Skip to the next element
						// as it is already in order
						d = d->next;
					} else {  // Case 2: b is not the head of the linked list


						// Move d before b
						b->next = d->next;
						d->next = b;
						a->next = d;

						// Swap b and d pointers
						temp = b;
						b = d;
						d = temp;

						c = d;

						// Skip to the next element
						// as it is already in order
						d = d->next;
					}
				}

				// If b and d have some non-zero
				// number of nodes in between them
				else {

					// Case 3: b is the head of the linked list
					if (b == head) {

						// Swap b->next and d->next
						temp = b->next;
						b->next = d->next;
						d->next = temp;
						c->next = b;

						// Swap b and d pointers
						temp = b;
						b = d;
						d = temp;

						c = d;

						// Skip to the next element
						// as it is already in order
						d = d->next;

						// Update the head
						head = b;
					}

					// Case 4: b is not the head of the linked list
					else {

						// Swap b->next and d->next
						temp = b->next;
						b->next = d->next;
						d->next = temp;
						c->next = b;
						a->next = d;

						// Swap b and d pointers
						temp = b;
						b = d;
						d = temp;

						c = d;

						// Skip to the next element
						// as it is already in order
						d = d->next;
					}
				}
			}
			else {

				// Update c and skip to the next element
				// as it is already in order
				c = d;
				d = d->next;
			}
		}

		a = b;
		b = b->next;
	}

	return head;
}

int main(void) {

	//Read in and initialize the buffer.
	FILE *inputFile = fopen("input_stream.bin", "rb");
	fseek(inputFile, 0, SEEK_END);
	long fsize = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);  /* same as rewind(f); */

	unsigned char *buffer = malloc(fsize + 1);  //buffer is the input stream
	fread(buffer, fsize, 1, inputFile);
	fclose(inputFile);
	buffer[fsize] = 0; //Set an EOF at the end of the buffer


	unsigned short bufferLocation = 0;
	int flagSize = 0;

	//	for(int i = 0; i < fsize; i++) { // Verify all bytes are being read;
	//		if(i % 16 == 0) { 			//print out all the bytes of the buffer on a 16 byte width
	//			printf("\n");
	//		}
	//		printf("%02x ", buffer[i]);
	//	}

	node *head = calloc(1, sizeof(struct node));
	node *curr = NULL;






	// Establish first node
	//printf("\n---newNode---\n");
	head->flink = *(unsigned short *)(buffer + bufferLocation);
	//printf("flink %02x \n", head->flink);
	head->value = *(unsigned short *)(buffer + bufferLocation + 2);
	//printf("value %02x \n", head->value);
	head->length = *(unsigned short *)(buffer + bufferLocation + 4);
	//printf("length %02x \n", head->length);
	head->flagPieces = calloc(head->length, sizeof(char));
	for(int i = 0; i < head->length; i++) {
		head->flagPieces[i] = *(buffer + bufferLocation + 6 + i);
		//printf("%02d | piece == %02x | buffer == %02x\n", i, head->flagPieces[i], *(buffer + bufferLocation + 6 + i)); // Make sure things match
	}
	flagSize = head->length;

	bufferLocation = bufferLocation + 6 + head->length;
	curr = head;
	while(bufferLocation < fsize) {
		//printf("\n---newNode---\n");
		curr->next = calloc(1, sizeof(struct node));
		curr->next->flink = *(unsigned short *)(buffer + bufferLocation);
		//printf("flink %02x \n", curr->next->flink);
		curr->next->value = *(unsigned short *)(buffer + bufferLocation + 2);
		//printf("value %02x \n", curr->next->value);
		curr->next->length = *(unsigned short *)(buffer + bufferLocation + 4);
		//printf("length %02x \n", curr->next->length);
		curr->next->flagPieces = calloc(curr->next->length, sizeof(char));
		for(int i = 0; i < curr->next->length; i++) {
			curr->next->flagPieces[i] = *(buffer + bufferLocation + 6 + i);
			//printf("%02d | piece == %02x | buffer == %02x\n", i+1, curr->next->flagPieces[i], *(buffer + bufferLocation + 6 + i)); // Make sure things match
		}
		if(curr->next->length > flagSize) { //Capture the size of the flag for later
			//printf("\t\t\t\t New max flag size: from %d to %d\n", flagSize, curr->next->length);
			flagSize = curr->next->length;
		}

		curr = curr->next;
		bufferLocation = bufferLocation + 6 + curr->length;
		curr->next = NULL;
	}

	head = selectionSort(head);

	//Verify list is created correctly by printing out all structures.
	//	while(curr != NULL) {
	//		printf("\n---newNode---\n");
	//				printf("flink %02x \n", curr->flink);
	//				printf("value %02x \n", curr->value);
	//				printf("length %02x \n", curr->length);
	//				for(int i = 0; i < curr->length; i++) {
	//					printf("%02d | piece == %02x |\n", i+1, curr->flagPieces[i]); // Make sure things match
	//				}
	//				curr = curr->next;
	//	}

	char *flag = calloc(flagSize, sizeof(char));

	curr = head;
	int oddEven = 0;
	while(curr){// XOR all the flag pieces from even indices

		if(oddEven % 2 == 0) { // Skip odd indexes.
			for(int i = 0; i < curr->length; i++) {
				flag[i] = flag[i] ^ curr->flagPieces[i];
			}
		}
		oddEven++;
		curr  = curr->next;
	}

	printf("\n");
	for(int i = 0; i < flagSize; i++) { //Print flag
		printf("%c", flag[i]);
	}
	printf("\n");


	printf("\n---Ending Program---");
	return 0;
}

































