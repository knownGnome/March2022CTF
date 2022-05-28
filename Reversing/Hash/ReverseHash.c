/*
 ============================================================================
 Name        : ReverseHash.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


short hash(unsigned char * s){

	unsigned short h = 0, t;
	unsigned int length = 0;
	unsigned char *start , *end = s, v;

	while(*end) {
		start = end;

		if(!(length & 1)) {
			t = (*(short*)(start));
			t = t * 0x1906;
			h ^= t;
		} else {
			v = (*(start));
			v = (0x9 * (v))*2;
			h ^= v;
		}

		length++;
		end++;
	}

	return h;

}
	/*
    goto test;
    do {
        start = end;

        if(!(length & 1)) {
            t = (*(short*)(start));
            t = t * 0x1906;
            h ^= t;
        } else {
            v = (*(start));
            v = (0x9 * (v))*2;
            h ^= v;
        }

        length++;
        end++;
test:} while(*end);

	 */




int main(int argc, char * argv[]){

	for(int i =1;i<argc;i++)
		printf("hash(\"%s\")=0x%04hx\n",argv[1], hash(argv[i]));
	return 0;
}


/*
 * 0000000000001149 <hash>:
	endbr64
    push   rbp
	mov    rbp,rsp
	mov    QWORD PTR [rbp-0x28],rdi
	mov    WORD PTR [rbp-0x18],0x0
	mov    DWORD PTR [rbp-0x14],0x0
	mov    rax,QWORD PTR [rbp-0x28]
	mov    QWORD PTR [rbp-0x10],rax
	jmp    11cb <hash+0x82>
	mov    rax,QWORD PTR [rbp-0x10]
	mov    QWORD PTR [rbp-0x8],rax
	mov    eax,DWORD PTR [rbp-0x14]
	and    eax,0x1
	test   eax,eax
	jne    11a0 <hash+0x57>
	mov    rax,QWORD PTR [rbp-0x8]
	movzx  eax,WORD PTR [rax]
	mov    WORD PTR [rbp-0x16],ax
	movzx  eax,WORD PTR [rbp-0x16]
	imul   ax,ax,0x1906
	mov    WORD PTR [rbp-0x16],ax
	movzx  eax,WORD PTR [rbp-0x16]
	xor    WORD PTR [rbp-0x18],ax
	jmp    11c2 <hash+0x79>
	mov    rax,QWORD PTR [rbp-0x8]
	movzx  eax,BYTE PTR [rax]
	mov    BYTE PTR [rbp-0x19],al
	movzx  edx,BYTE PTR [rbp-0x19]
	mov    eax,edx
	shl    eax,0x3
	add    eax,edx
	add    eax,eax
	mov    BYTE PTR [rbp-0x19],al
	movzx  eax,BYTE PTR [rbp-0x19]
	xor    WORD PTR [rbp-0x18],ax
	add    DWORD PTR [rbp-0x14],0x1
	add    QWORD PTR [rbp-0x10],0x1
	mov    rax,QWORD PTR [rbp-0x10]
	movzx  eax,BYTE PTR [rax]
	test   al,al
	jne    116c <hash+0x23>
	movzx  eax,WORD PTR [rbp-0x18]
	pop    rbp
	ret
 */























