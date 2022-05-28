/*
 ============================================================================
 Name        : Interpreter.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

int main(int argv, char **argc) {
	unsigned char currInst = '\0';
	short bufferLocation = 0;
	long long xorVal = 0;
	unsigned char temp;
	FILE *inputFile = fopen("input_stream.bin", "rb");
	unsigned char *xorBuffer = calloc(8, sizeof(char));

	fseek(inputFile, 0, SEEK_END);
	long fsize = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);  /* same as rewind(f); */

	unsigned char *buffer = malloc(fsize + 1);  //buffer is the input stream
	fread(buffer, fsize, 1, inputFile);
	fclose(inputFile);

	buffer[fsize] = 0; //Set an EOF at the end of the buffer
	currInst = buffer[bufferLocation]; //Set first instruction


	//Test to see if hex values can be read correctly
	//	printf("%02x %02x %02x %02x %02x %02x %02x", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6]);

	//	if(buffer[1] == 182){
	//		printf("\nTrue");
	//	}

	//printf("%02x", *(buffer + 1)); // Testing accessing different locations in buffer


	//	for(int i = 0; i < 8; i++) {
	//		xorBuffer[i] = 0x00;
	//		printf("xorBuff: %02x\n", buffer[0x47 + i]);
	//	}
	//	xorVal = *(long long *)(buffer + 0xba);
	//	printf("%016x\n\n", xorVal);
	//	*(long long *)xorBuffer = *(long long *)(buffer + 0x47) ^ xorVal;//*(long long *)(buffer + 0xba);
	//	printf("-xorBuff: %s\n", xorBuffer);
	//	printf("xorBuff: ");
	//	for(int i = 0; i < 8; i++) {
	//		printf("%02x", xorBuffer[i]);
	//	}



	while(1) {
		switch(currInst){
		case END : //0
			printf("\n\n---Ending Program---");
			exit(0);
			break;
		case JMP :  //1
			//bufferLocation = buffer[bufferLocation + 1] + buffer[bufferLocation + 2];
			//printf("Buffer location before == %04x\n", bufferLocation);  // See location before
			//printf("Next Jump Value location == %04x :: %04d\n", *( short *)(buffer + bufferLocation + 1), *( short *)(buffer + bufferLocation + 1));
			bufferLocation = *( short *)(buffer + bufferLocation + 1) + bufferLocation;  // Add next jump location to bufferLocation
			//printf("Buffer location after == %04x\n", bufferLocation);  // See location after
			currInst = buffer[bufferLocation];  // Set next instruction
			//printf("Jumping to %04x and executing %02x\n", bufferLocation, currInst);  //Testing value being assigned correctly
			break;

		case SWP :  //2
			//printf("First byte == %04x and Second byte == %04x before swap\n", *(buffer + (buffer[bufferLocation + 1])), *(buffer + (buffer[bufferLocation + 2])));  //Testing value being assigned correctly
			temp = *(buffer + (buffer[bufferLocation + 1]));
			*(buffer + (buffer[bufferLocation + 1])) = *(buffer + (buffer[bufferLocation + 2]));
			*(buffer + (buffer[bufferLocation + 2])) = temp;
			//printf("First byte == %04x and Second byte == %04x after swap\n", *(buffer + (buffer[bufferLocation + 1])), *(buffer + (buffer[bufferLocation + 2])));
			bufferLocation += SWP_SIZE;
			currInst = buffer[bufferLocation];
			//printf("Continuing to next Instruction %04x and executing %02x\n", bufferLocation, currInst);  //Testing value being assigned correctly
			break;


		case ADD :  // 3   ---   *(int *)(buffer + ((int)buffer[bufferLocation + 1]))  cast buffer as an integer pointer and dereference it and add the desired location in buffer casted as and int to treat it like an array
			//printf("Addition location before: %08x\n", *(int *)(buffer + ((int)buffer[bufferLocation + 1])));
			//printf("What's being added: %08x\n", *(int *)(buffer + bufferLocation + 2));
			*(int *)(buffer + ((int)buffer[bufferLocation + 1])) = *(int *)(buffer + ((int)buffer[bufferLocation + 1])) + *(int *)(buffer + bufferLocation + 2);
			//printf("Addition location after: %08x\n", *(int *)(buffer + ((int)buffer[bufferLocation + 1])));
			bufferLocation += ADD_SIZE;
			currInst = buffer[bufferLocation];
			//printf("Continuing to next Instruction %04x and executing %02x\n", bufferLocation, currInst);  //Testing value being assigned correctly
			break;


		case XOR :  //4
			//			for(int i = 0; i < 8; i++) {
			//				xorBuffer[bufferLocation + 1 + i];
			//				printf("xorBuff: %02x\n", xorBuffer[i]);
			//			}
			//			printf("Executing Instruction at %04x and executing %02x\n", bufferLocation, currInst);

			//printf("buff: %08x\n", *(long long *)(buffer + ((long)buffer[bufferLocation + 1])));
			//printf("buff: %08x\n", *(long long *)(buffer + bufferLocation + 2));
			//*(long long *)(buffer + buffer[bufferLocation + 1]) =
			*(long long *)(buffer + ((long)buffer[bufferLocation + 1])) = *(long long *)(buffer + ((long)buffer[bufferLocation + 1])) ^ *(long long *)(buffer + bufferLocation + 2);
			//printf("buff: %08x\n", *(long long *)(buffer + ((long)buffer[bufferLocation + 1])));
			bufferLocation += XOR_SIZE;
			currInst = buffer[bufferLocation];
			//printf("Continuing to next Instruction %04x and executing %02x\n", bufferLocation, currInst);  //Testing value being assigned correctly
			break;


		case INVERT :  //5
			//printf("Invert location before: %02x\n", *(buffer + (buffer[bufferLocation + 1])));
			*(buffer + (buffer[bufferLocation + 1])) = reverse(*(buffer + (buffer[bufferLocation + 1])));
			//printf("Invert location after == %02x\n", *(buffer + (buffer[bufferLocation + 1])));
			bufferLocation += INVERT_SIZE;
			currInst = buffer[bufferLocation];
			//printf("Continuing to next Instruction %04x and executing %02x\n", bufferLocation, currInst);  //Testing value being assigned correctly
			break;
//
//
		case PRINT :  //6
			printf("%c", buffer[bufferLocation + 1]); // print character
			//printf("Buffer location before == %04x\n", bufferLocation);  // See location before
			bufferLocation += 2;  // Jump is a 2 byte instruction so add 2 to current buffer location
			//printf("Buffer location after == %04x\n", bufferLocation);
			currInst = buffer[bufferLocation];
			//printf("Continuing to next Instruction %04x and executing %02x\n", bufferLocation, currInst);  //Testing value being assigned correctly
			break;


		default:
			printf("\n\nError Running instruction %02x at location %08x", currInst, bufferLocation);
			return 1;
		}
	}





	return 0;
}
