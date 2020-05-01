#include <x86intrin.h>
#include <stdlib.h>
#include <stdio.h>

void transpose(int* position) {
	
	__m128 r0,r1,r2,r3;
	__m128 t0,t1,t2,t3;
		
	r0 = _mm_castsi128_ps(_mm_loadu_si128(&position[0*4]));
	r1 = _mm_castsi128_ps(_mm_loadu_si128(&position[1*4]));
	r2 = _mm_castsi128_ps(_mm_loadu_si128(&position[2*4]));
	r3 = _mm_castsi128_ps(_mm_loadu_si128(&position[3*4]));
	/*
	r1 = _mm_loadu_si128(&position[1*4]);
	r2 = _mm_loadu_si128(&position[2*4]);
	r3 = _mm_loadu_si128(&position[3*4]);
	
	
	t0 = _mm_unpacklo_epi32(r0,r1);
	t1 = _mm_unpackhi_epi32(r0,r1);
	t2 = _mm_unpacklo_epi32(r2,r3);
	t3 = _mm_unpackhi_epi32(r2,r3);
	*/
	
	t0 = _mm_unpacklo_ps(r0,r1);
	t1 = _mm_unpackhi_ps(r0,r1);
	t2 = _mm_unpacklo_ps(r2,r3);
	t3 = _mm_unpackhi_ps(r2,r3);

	r0 = _mm_shuffle_ps(t0,t2,0x44);
	r1 = _mm_shuffle_ps(t0,t2,0xEE);
	r2 = _mm_shuffle_ps(t1,t3,0x44);
	r3 = _mm_shuffle_ps(t1,t3,0xEE);
	/*
	_mm_storeu_si128(&position[0*4],r0);
	_mm_storeu_si128(&position[1*4],r1);
	_mm_storeu_si128(&position[2*4],r2);
	_mm_storeu_si128(&position[3*4],r3);
	*/

	_mm_storeu_si128(&position[0*4],_mm_castps_si128(r0));
	_mm_storeu_si128(&position[1*4],_mm_castps_si128(r1));
	_mm_storeu_si128(&position[2*4],_mm_castps_si128(r2));
	_mm_storeu_si128(&position[3*4],_mm_castps_si128(r3));
	
}
void flip(int* position) {
	__m128i r0,r1,r2,r3;
	
	r0 = _mm_loadu_si128(&position[0*4]);
	r1 = _mm_loadu_si128(&position[1*4]);
	r2 = _mm_loadu_si128(&position[2*4]);
	r3 = _mm_loadu_si128(&position[3*4]);

	_mm_storeu_si128(&position[0*4],r3);
	_mm_storeu_si128(&position[1*4],r2);
	_mm_storeu_si128(&position[2*4],r1);
	_mm_storeu_si128(&position[3*4],r0);
}
void rotate(int* position) {
	flip(position);
	transpose(position);
}	
void rotate4(int* position) {
	printMatrix(position);
	rotate(position);
	printMatrix(position);
	rotate(position);
	printMatrix(position);
	rotate(position);
	printMatrix(position);
	rotate(position);
	printMatrix(position);
}
void allTogether(int* position) {
	rotate4(position);
	flip(position);
	rotate4(position);
	flip(position);
	printMatrix(position);
}
void printMatrix(int* position) {
	for (int i = 0; i < 4; i++) {
		printf("%2i %2i %2i %2i\n",*(position + (4*i)),*(position+(4*i)+1),*(position+(4*i)+2),*(position+(4*i)+3));
	}
	printf("\n");
}
int* makeTest() {
	int * test = malloc(sizeof(int)*16);
	for (int i = 0; i < 16; i++) {
		*(test+i) = i;
	}
	return test;
}

int main() {
	int* test = makeTest();
	allTogether(test);
	free(test);
	return 0;
}
