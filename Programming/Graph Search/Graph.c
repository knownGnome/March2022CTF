/*
 ============================================================================
 Name        : Graph.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define INFINITY 9999



// adjMtx == adjacencyList; mtxLength == lengths; size == counter; vals == values
//    0x73 x mtxLengths[i]			  0x73				0x73			0x73
void dijkstra(short **adjMtx, short *mtxLength, int size, char* vals, int start) {

	short **cost = NULL;
	int *distance = calloc(size, sizeof(int));
	int *pred = calloc(size, sizeof(int));
	int *visited = calloc(size, sizeof(int));
	int count = 1;
	int minDistance = INFINITY;
	int nextNode = 0;

	//Initialize cost
	cost = calloc(size, sizeof(short *));
	for(int i = 0; i <= size; i++) {
		cost[i] = calloc(size, sizeof(short));
		//printf("%x \n", i);
	}

	for(int i = 0; i <= size; i++) {
		for(int j = 0; j <= size; j++) {
			cost[i][j] = 9999;
			//printf("%x ", cost[i][j]);
		}
		//printf("\n");
		//printf("%x \n", i);
	}

	//printf("%d ", adjMtx[size][1]);

	for(int i = 0; i <= size; i++) {
		for(int j = 0; j < mtxLength[i]; j++) {
			cost[i][adjMtx[i][j + 1]] = 1;
			//printf("%x ", adjMtx[i][j + 1]);
		}
		//printf("\n");
	}

	//initialize pred, distance and visited
	for (int i = 0; i <= size; i++) {
		distance[i] = cost[start][i];
		pred[i] = start;
		visited[i] = 0;
	}
	distance[start] = 0;
	visited[start] = 1;
	while (count < size - 1) {
		minDistance = INFINITY;
		for(int i = 0; i <= size; i++) {
			if((distance[i] < minDistance) && !visited[i]) {
				minDistance = distance[i];
				nextNode = i;
			}
			//Check if a better path exists
			visited[nextNode] = 1;
			for(int i = 0; i <= size; i++) {
				if(!visited[i]) {
					if((minDistance + cost[nextNode][i]) < distance[i]) {
						distance[i] = minDistance + cost[nextNode][i];
						pred[i] = nextNode;
					}

				}
			}
		}
		count++;
	}


	// Get the path from start to }
	int j = 0;
	int counter = 1;
	for(int i = size; i >= 0; i--) {
		if((i != start) && i == 0x4a) {
			printf("\nDistance of node: %c = %d",vals[i],distance[i]);
			printf("\nPath=%c",vals[i]);
			j=i;
			do
			{
				j=pred[j];
				printf("%c",vals[j]);
				counter += 1;
			}while(j!=start);
		}
	}

	//Reverse the path and save to flag
	int save = counter;
	char *flag = calloc(counter + 1, sizeof(char));
	j = 0;

	for(int i = size; i >= 0; i--) {
		if((i != start) && i == 0x4a) {
			flag[counter - 1] = vals[i];
			counter = counter - 1;
			j=i;
			do
			{
				j=pred[j];
				flag[counter - 1] = vals[j];
				counter = counter - 1;
			}while(j!=start);
		}
	}

	//Print the flag
	printf("\nFlag= ");
	for(int i = 0; i < save; i++) {
		printf("%c",flag[i]);
	}



}

short byteShift(unsigned short num) {
	unsigned short output = num;
	output = output >> 8;
	return output;
}



int main(int argv, char **argc) {
	FILE *inputFile = fopen("input_stream.bin", "rb");
	fseek(inputFile, 0, SEEK_END);
	long fsize = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);  /* same as rewind(f); */

	char *buffer = malloc(fsize + 1);  //buffer is the input stream
	fread(buffer, fsize, 1, inputFile);
	fclose(inputFile);
	buffer[fsize] = 0; //Set an EOF at the end of the buffer
	int i = 0;
	int counter = 0;
	char *values = NULL;
	short *lengths = NULL;
	short **adjacencyList = NULL;


	while( i < fsize) {


		//printf("%c\n", *(buffer + i));
		//printf("%02x\n", i);
		printf("%02x | Val == %c | Length == %d ", counter, *(buffer + i), *( short *)(buffer + i + 1));

		for (int j = i + 2; j <= (i + (*( short *)(buffer + i + 1) * 2)); j += 2) {
			printf("| Out %d == %04x ", ((j - i)/2), (*( short *)(buffer + j)) >> 8);
		}

		printf("|\n");
		counter++;
		i = i + (*( short *)(buffer + i + 1) * 2) + 3; /* The +3 is for the 1 char Val byte and the 2 bytes for the length.
														And since it's a char buffer the * 2 is to double the length to be
														the same size as a short for the out locations*/
		//		if(i % 16 == 0) { //print out all the bytes of the buffer on a 16 byte width
		//			printf("\n");
		//		}
		//		printf("%02x ", buffer[i]);
	}

	printf("\n\n**********************************************\n\n");
	counter = counter - 1;
	//printf("\n%x", counter);
	values = calloc(counter, sizeof(char));
	lengths = calloc(counter, sizeof(short));
	adjacencyList = calloc(counter, sizeof(short *));
	i= 0;
	counter = 0;


	while( i < fsize) {


		values[counter] = *(buffer + i); // Assign values to the value list to correspond to its position in adjacencyList
		lengths[counter] = *( short *)(buffer + i + 1); // Assign lengths for use with pathing later
		adjacencyList[counter] = calloc(*( short *)(buffer + i + 1), sizeof(short)); // Allocate the space for the adjacency

		for (int j = i + 2; j <= (i + (*( short *)(buffer + i + 1) * 2)); j += 2) {
			adjacencyList[counter][((j - i)/2)] = (*( short *)(buffer + j)) >> 8;;  // map connections to vertices, assign the adjacencies
		}
		counter++;
		i = i + (*( short *)(buffer + i + 1) * 2) + 3; /* The +3 is for the 1 char Val byte and the 2 bytes for the length.
															And since it's a char buffer the * 2 is to double the length to be
															the same size as a short for the out locations*/

	}
	counter = counter - 1;

	//	for(int j = 0; j <= counter; j ++){
	//		printf("%c ", values[j]);
	//	}

	//printf("%04x", byteSwap(0x5c00));



	dijkstra(adjacencyList, lengths, counter, values, 0);



	return 0;
}
