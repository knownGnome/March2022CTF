/*
 ============================================================================
 Name        : HelloC.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

unsigned char buffer[45] = {0xa8, 0x66, 0xe5, 0xa2, 0xaf, 0x8d, 0x7e, 0xb2, 0xc7, 0xc6, 0x98, 0x95, 0x65, 0x12, 0xee, 0x45, 0xe8, 0xe4, 0x22, 0x84, 0xc6, 0xe9, 0xb9,
		0xaa, 0x61, 0x73, 0xd0, 0x0f, 0xb6, 0xa6, 0xde, 0x06, 0xd4, 0xbb, 0xe0, 0x96, 0x68, 0xe8, 0xc6, 0x44, 0x88, 0x0a, 0x30, 0xc8, 0x54};

unsigned char final[15] = {0x84, 0xe7, 0xcc, 0x30, 0x10, 0x7f, 0xfe, 0x40, 0xe2, 0x4d, 0xb9, 0x99, 0x9c, 0x18, 0x03};

//(buffer[(long)(counter % 3) * 0xf + (long)counter] ^ *(char *)(User_Input + counter)) != final[0xe - counter])




int check1(long User_Input) {
	int counter = 0;

	while(*(char *)(User_Input + counter) != '\0'){
		printf("Input =%c;  Counter= %d\n", *(char *)(User_Input + counter), counter);
		counter++;
	}
	printf("Input =%c;  Counter= %d;  Result= %d\n", *(char *)(User_Input + counter), counter, (counter == 0xf));

	return counter == 0xf;
}

int check2(long User_Input) {
	int counter = 0;
	while(1) {
		if(0xe < counter){
			printf("Good: Counter == %d;  Input == %ld\n", counter, User_Input);
			return 1;
		}
		if((buffer[(long)(counter % 3) * 0xf + (long)counter] ^ *(unsigned char *)(User_Input + counter)) != final[0xe - counter]){
			printf("Bad: Counter= %d;  Buffer= %x;  Final= %x;  Input= %c\n", counter, buffer[(long)(counter % 3) * 0xf + (long)counter], final[0xe - counter], (*(char *)(User_Input + counter)));
			break;
		}
		counter++;
	}
	return 0;
}


int main(void) {
	//long User_Input = -2147483648;
	unsigned char *User_Input;
	User_Input = calloc(24, sizeof(unsigned char));
	//	char *User_Input2;
	//	User_Input2 = calloc(24, sizeof(char));
	//int counter = 1;
	unsigned char test = '\0';
	int checker1 = 0;
	int checker2 = 0;




	//printf("%x", (buffer[(long)(counter % 3) * 0xf + (long)counter]));

	//Used to determine input needs to be 16 characters long with the 16th character being the NULL character.
	//	for(int i = 0; i < 15; i++){
	//		User_Input[i] = 'A';
	//	}
	//	User_Input[15] = '\0';
	//	check1(User_Input);


	//


	for(int counter = 0; counter < 15; counter++){
		while(test < 256) {
			if((buffer[(long)(counter % 3) * 0xf + (long)counter] ^ test) == final[0xe - counter]){
				printf("Character at %d is %c - 0x%x \n", counter, test, test);
				User_Input[counter] = test;
				break;
			} else {
				test++;
			}
		}
	}
	User_Input[15] = '\0';


	printf("\n\n#################################\n\n");

	checker1 = check1((long)User_Input);
	checker2 = check2((long)User_Input);
	if((checker1 != 0) && (checker2 != 0)){
		printf("Success\n");
	}

	printf("\n\n#################################\n\n");

	for(int counter = 0; counter < 15; counter++){
		while(test < 256) {
			if((buffer[(long)(counter % 3) * 0xf + (long)counter] ^ test) == final[0xe - counter]){
				printf("%x", test);
				User_Input[counter] = test;
				break;
			} else {
				test++;
			}
		}
	}
	User_Input[15] = '\0';

	//	while(counter < 1000000000){
	//
	//		for (int i = 0; i < 24; i++) {
	//			if(++User_Input[i]){
	//				break;
	//			}
	//		}
	//		counter++;
	//
	//	}



	//		while(1){
	//			if(check1((long)User_Input)) {//check1((long)User_Input) &&
	//				printf("Answer:  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", User_Input[0],User_Input[1], User_Input[2],User_Input[3], User_Input[4],User_Input[5], User_Input[6],User_Input[7], User_Input[8],User_Input[9], User_Input[10],User_Input[11], User_Input[12],User_Input[13], User_Input[14],User_Input[15], User_Input[16],User_Input[17], User_Input[18],User_Input[19], User_Input[20],User_Input[21], User_Input[22],User_Input[23]);
	//				return 0;
	//			}
	////			if(check1((long)User_Input2)) {//check1((long)User_Input) &&
	////							printf("Answer:  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", User_Input[0],User_Input[1], User_Input[2],User_Input[3], User_Input[4],User_Input[5], User_Input[6],User_Input[7], User_Input[8],User_Input[9], User_Input[10],User_Input[11], User_Input[12],User_Input[13], User_Input[14],User_Input[15], User_Input[16],User_Input[17], User_Input[18],User_Input[19], User_Input[20],User_Input[21], User_Input[22],User_Input[23]);
	////							return 0;
	////						}
	//			for (int i = 0; i < 24; i++) {
	//				if(User_Input[i] += 17){
	//					break;
	//				}
	//			}
	//
	//		}


	return 0;
}





/*
 * This is the solution to Input 1
 *
 *
 *
 *


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

 */


/*
 * Reading and writing binary files is pretty much the same as any other file, the only difference is how you open it:

unsigned char buffer[10];
FILE *ptr;

ptr = fopen("test.bin","rb");  // r for read, b for binary

fread(buffer,sizeof(buffer),1,ptr); // read 10 bytes to our buffer
You said you can read it, but it's not outputting correctly... keep in mind that when you "output" this data, you're not reading ASCII, so it's not like printing a string to the screen:

for(int i = 0; i<10; i++)
    printf("%u ", buffer[i]); // prints a series of bytes
Writing to a file is pretty much the same, with the exception that you're using fwrite() instead of fread():

FILE *write_ptr;

write_ptr = fopen("test.bin","wb");  // w for write, b for binary

fwrite(buffer,sizeof(buffer),1,write_ptr); // write 10 bytes from our buffer
Since we're talking Linux.. there's an easy way to do a sanity check. Install hexdump on your system (if it's not already on there) and dump your file:

mike@mike-VirtualBox:~/C$ hexdump test.bin
0000000 457f 464c 0102 0001 0000 0000 0000 0000
0000010 0001 003e 0001 0000 0000 0000 0000 0000
...
Now compare that to your output:

mike@mike-VirtualBox:~/C$ ./a.out
127 69 76 70 2 1 1 0 0 0
hmm, maybe change the printf to a %x to make this a little clearer:

mike@mike-VirtualBox:~/C$ ./a.out
7F 45 4C 46 2 1 1 0 0 0
Hey, look! The data matches up now*. Awesome, we must be reading the binary file correctly!


 */
