#include <x86intrin.h>
#include <stdio.h>
#include <stdlib.h>
/*
void tranpose(int* position) {
	__m256i ro,r1,r2,r3,r4,r5,r6,r7;
	__m256i t0,t1,t2,t3,t4,t5,t6,t7
	
	r0  = _mm256_insertf128_si256(_mm256_castsi128_si256(_mm_loadu_si128(&position[0*8+0])),_mm_loadu_si128(&position[4*8+0]),1);
	r1  = _mm256_insertf128_si256(_mm256_castsi128_si256(_mm_loadu_si128(&position[1*8+0])),_mm_loadu_si128(&position[5*8+0]),1);
	r2  = _mm256_insertf128_si256(_mm256_castsi128_si256(_mm_loadu_si128(&position[2*8+0])),_mm_loadu_si128(&position[6*8+0]),1);
        r3  = _mm256_insertf128_si256(_mm256_castsi128_si256(_mm_loadu_si128(&position[3*8+0])),_mm_loadu_si128(&position[7*8+0]),1);
	r4  = _mm256_insertf128_si256(_mm256_castsi128_si256(_mm_loadu_si128(&position[0*8+4])),_mm_loadu_si128(&position[4*8+4]),1);
        r5  = _mm256_insertf128_si256(_mm256_castsi128_si256(_mm_loadu_si128(&position[1*8+4])),_mm_loadu_si128(&position[5*8+4]),1);
	r6  = _mm256_insertf128_si256(_mm256_castsi128_si256(_mm_loadu_si128(&position[2*8+4])),_mm_loadu_si128(&position[6*8+4]),1);
        r7  = _mm256_insertf128_si256(_mm256_castsi128_si256(_mm_loadu_si128(&position[3*8+4])),_mm_loadu_si128(&position[7*8+4]),1);
	
	t0 = _mm256_unpacklo_epi32(r0,r1);
	t1 = _mm256_unpackhi_epi32(r0,r1);
	t2 = _mm256_unpacklo_epi32(r2,r3);
	t3 = _mm256_unpackhi_epi32(r2,r3);
	t4 = _mm256_unpacklo_epi32(r4,r5);
	t5 = _mm256_unpackhi_epi32(r4,r5);
	t6 = _mm256_unpacklo_epi32(r6,r7);
	t7 = _mm256_unpackhi_epi32(r6,r7);	
	//TODO:Figure out shuffling and Blending
	__m256i v;
	

	_mm256_storeu_si256(&position[0*8], r0);
        _mm256_storeu_si256(&position[1*8], r1);
        _mm256_storeu_si256(&position[2*8], r2);
        _mm256_storeu_si256(&position[3*8], r3);
        _mm256_storeu_si256(&position[4*8], r4);
        _mm256_storeu_si256(&position[5*8], r5);
        _mm256_storeu_si256(&position[6*8], r6);
        _mm256_storeu_si256(&position[7*8], r7);

}
void flip(int* position) {
        __m128 r0,r1,r2,r3,r4,r5,r6,r7;

        r0 = _mm_load_ps(&position[0*8]);
        r1 = _mm_load_ps(&position[1*8]);
        r2 = _mm_load_ps(&position[2*8]);
        r3 = _mm_load_ps(&position[3*8]);
        r4 = _mm_load_ps(&position[4*8]);
        r5 = _mm_load_ps(&position[5*8]);
        r6 = _mm_load_ps(&position[6*8]);
        r7 = _mm_load_ps(&position[7*8]);

        _mm_store_ps(&position[0*8], r7);
        _mm_store_ps(&position[1*8], r6);
        _mm_store_ps(&position[2*8], r5);
        _mm_store_ps(&position[3*8], r4);
        _mm_store_ps(&position[4*8], r3);
        _mm_store_ps(&position[5*8], r2);
        _mm_store_ps(&position[6*8], r1);
        _mm_store_ps(&position[7*8], r0);
}*/
void flip(int* position) {
        __m256i r0,r1,r2,r3,r4,r5,r6,r7;

        r0 = _mm256_loadu_si256(&position[0*8]);
        r1 = _mm256_loadu_si256(&position[1*8]);
        r2 = _mm256_loadu_si256(&position[2*8]);
        r3 = _mm256_loadu_si256(&position[3*8]);
        r4 = _mm256_loadu_si256(&position[4*8]);
        r5 = _mm256_loadu_si256(&position[5*8]);
        r6 = _mm256_loadu_si256(&position[6*8]);
        r7 = _mm256_loadu_si256(&position[7*8]);

        _mm256_storeu_si256(&position[0*8], r7);
        _mm256_storeu_si256(&position[1*8], r6);
        _mm256_storeu_si256(&position[2*8], r5);
        _mm256_storeu_si256(&position[3*8], r4);
        _mm256_storeu_si256(&position[4*8], r3);
        _mm256_storeu_si256(&position[5*8], r2);
        _mm256_storeu_si256(&position[6*8], r1);
        _mm256_storeu_si256(&position[7*8], r0);
}
/*
void rotate(int* position) {
	transpose(position);
	flip(position);
}
//NEED A WAY TO HASH IN THIS FUNCTION
//Pass the number of o and x into this as well
//API for hash
//int hash(int* position,int o, int x) {}
void CheckedStored(struct table* t, int* position,int o, int x) {
	if (lookupHelper(t,hash(position,o,x) != -1)) {
		return;
	} 
	rotate(position);
	if (lookupHelper(t,hash(position,o,x) != -1)) {
                return;
        } 
	rotate(position);
	if (lookupHelper(t,hash(position,o,x) != -1)) {
                return;
        } 
	rotate(position);
	if (lookupHelper(t,hash(position,o,x) != -1)) {
                return;
        } 
	rotate(position);
	flip(position);
	if (lookupHelper(t,hash(position,o,x) != -1)) {
                return;
        } 
        rotate(position);
        if (lookupHelper(t,hash(position,o,x) != -1)) {
                return;
        } 
        rotate(position);
        if (lookupHelper(t,hash(position,o,x) != -1)) {
                return;
        } 
        rotate(position);
        if (lookupHelper(t,hash(position,o,x) != -1)) {
                return;
        } 
        rotate(position);
        flip(position);
}*/
void printMatrix(int* position) {
	printf("sizeof(int) = %lu\n",sizeof(int));
	printf("\n");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%i ", *(position+(8*i)+j));
		}
		printf("\n");
	}
}
int* createTest() {
	int* position = malloc(sizeof(int)*64);
	for (int i = 0; i<64;i++) {
		*(position+i) = i;
	}
	return position;	
}
int main() {
	int* test = createTest();
	printMatrix(test);
	flip(test);
	printMatrix(test);
	free(test);
	return 0;	
}
