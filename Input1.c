/*
 ============================================================================
 Name        : Input1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

unsigned int check(unsigned int input) {

	return (input ^ 0x735) >> 4 ^ 0x6f0;
}

int main(void) {
	int truther = 0;
	unsigned int checker;
	unsigned int counter = 0;
	unsigned int number = 0x111111;

	number = (number ^ 0x735) >> 4 ^ 0x6f0; //>> 4 ^ 0x6f0;
	printf("%x\n", number);

//	number ^= 0x6f0;
//	number = number << 4;
//	number = (number ^ 0x730); //<< 4 ^ 0x6f0;


	printf("%x\n", number);

	while(truther != 1) {
		checker = check(counter);
		if(checker != 0xb88202) {
			counter++;
			printf("%x\n", counter);
		} else {
			truther = 1;
		}
	}


//	number = number ^ 0x6f0;
//	number = number << 4;
//	number = number ^ 0x735;
//
//	printf("%x", number);




	return 0;
}
