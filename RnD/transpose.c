#include <stdio.h>
#include <x86intrin.h>
#include <omp.h>   
#include <time.h>
void NaiveTranspose(float* mat, float* matT) {
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++) {
			*(matT+(8*j)+i) = *(mat+(8*i)+j);
		}
	}
} 
/*
void tran(float* mat, float* matT) {
  __m256  r0, r1, r2, r3, r4, r5, r6, r7;
  __m256  t0, t1, t2, t3, t4, t5, t6, t7;

  r0 = _mm256_load_ps(&mat[0*8]);
  r1 = _mm256_load_ps(&mat[1*8]);
  r2 = _mm256_load_ps(&mat[2*8]);
  r3 = _mm256_load_ps(&mat[3*8]);
  r4 = _mm256_load_ps(&mat[4*8]);
  r5 = _mm256_load_ps(&mat[5*8]);
  r6 = _mm256_load_ps(&mat[6*8]);
  r7 = _mm256_load_ps(&mat[7*8]);

  t0 = _mm256_unpacklo_ps(r0, r1);
  t1 = _mm256_unpackhi_ps(r0, r1);
  t2 = _mm256_unpacklo_ps(r2, r3);
  t3 = _mm256_unpackhi_ps(r2, r3);
  t4 = _mm256_unpacklo_ps(r4, r5);
  t5 = _mm256_unpackhi_ps(r4, r5);
  t6 = _mm256_unpacklo_ps(r6, r7);
  t7 = _mm256_unpackhi_ps(r6, r7);

  r0 = _mm256_shuffle_ps(t0,t2,_MM_SHUFFLE(1,0,1,0));  
  r1 = _mm256_shuffle_ps(t0,t2,_MM_SHUFFLE(3,2,3,2));
  r2 = _mm256_shuffle_ps(t1,t3,_MM_SHUFFLE(1,0,1,0));
  r3 = _mm256_shuffle_ps(t1,t3,_MM_SHUFFLE(3,2,3,2));
  r4 = _mm256_shuffle_ps(t4,t6,_MM_SHUFFLE(1,0,1,0));
  r5 = _mm256_shuffle_ps(t4,t6,_MM_SHUFFLE(3,2,3,2));
  r6 = _mm256_shuffle_ps(t5,t7,_MM_SHUFFLE(1,0,1,0));
  r7 = _mm256_shuffle_ps(t5,t7,_MM_SHUFFLE(3,2,3,2));

  t0 = _mm256_permute2f128_ps(r0, r4, 0x20);
  t1 = _mm256_permute2f128_ps(r1, r5, 0x20);
  t2 = _mm256_permute2f128_ps(r2, r6, 0x20);
  t3 = _mm256_permute2f128_ps(r3, r7, 0x20);
  t4 = _mm256_permute2f128_ps(r0, r4, 0x31);
  t5 = _mm256_permute2f128_ps(r1, r5, 0x31);
  t6 = _mm256_permute2f128_ps(r2, r6, 0x31);
  t7 = _mm256_permute2f128_ps(r3, r7, 0x31);

  _mm256_store_ps(&matT[0*8], t0);
  _mm256_store_ps(&matT[1*8], t1);
  _mm256_store_ps(&matT[2*8], t2);
  _mm256_store_ps(&matT[3*8], t3);
  _mm256_store_ps(&matT[4*8], t4);
  _mm256_store_ps(&matT[5*8], t5);
  _mm256_store_ps(&matT[6*8], t6);
  _mm256_store_ps(&matT[7*8], t7);
}
*/

void tran(float* mat, float* matT) {
  __m256  r0, r1, r2, r3, r4, r5, r6, r7;
  __m256  t0, t1, t2, t3, t4, t5, t6, t7;

  r0 = _mm256_insertf128_ps(_mm256_castps128_ps256(_mm_load_ps(&mat[0*8+0])), _mm_load_ps(&mat[4*8+0]), 1);
  r1 = _mm256_insertf128_ps(_mm256_castps128_ps256(_mm_load_ps(&mat[1*8+0])), _mm_load_ps(&mat[5*8+0]), 1);
  r2 = _mm256_insertf128_ps(_mm256_castps128_ps256(_mm_load_ps(&mat[2*8+0])), _mm_load_ps(&mat[6*8+0]), 1);
  r3 = _mm256_insertf128_ps(_mm256_castps128_ps256(_mm_load_ps(&mat[3*8+0])), _mm_load_ps(&mat[7*8+0]), 1);
  r4 = _mm256_insertf128_ps(_mm256_castps128_ps256(_mm_load_ps(&mat[0*8+4])), _mm_load_ps(&mat[4*8+4]), 1);
  r5 = _mm256_insertf128_ps(_mm256_castps128_ps256(_mm_load_ps(&mat[1*8+4])), _mm_load_ps(&mat[5*8+4]), 1);
  r6 = _mm256_insertf128_ps(_mm256_castps128_ps256(_mm_load_ps(&mat[2*8+4])), _mm_load_ps(&mat[6*8+4]), 1);
  r7 = _mm256_insertf128_ps(_mm256_castps128_ps256(_mm_load_ps(&mat[3*8+4])), _mm_load_ps(&mat[7*8+4]), 1);

  t0 = _mm256_unpacklo_ps(r0,r1);
  t1 = _mm256_unpackhi_ps(r0,r1);
  t2 = _mm256_unpacklo_ps(r2,r3);
  t3 = _mm256_unpackhi_ps(r2,r3);
  t4 = _mm256_unpacklo_ps(r4,r5);
  t5 = _mm256_unpackhi_ps(r4,r5);
  t6 = _mm256_unpacklo_ps(r6,r7);
  t7 = _mm256_unpackhi_ps(r6,r7);

  __m256 v;

  //r0 = _mm256_shuffle_ps(t0,t2, 0x44);
  //r1 = _mm256_shuffle_ps(t0,t2, 0xEE);  
  v = _mm256_shuffle_ps(t0,t2, 0x4E);
  r0 = _mm256_blend_ps(t0, v, 0xCC);
  r1 = _mm256_blend_ps(t2, v, 0x33);

  //r2 = _mm256_shuffle_ps(t1,t3, 0x44);
  //r3 = _mm256_shuffle_ps(t1,t3, 0xEE);
  v = _mm256_shuffle_ps(t1,t3, 0x4E);
  r2 = _mm256_blend_ps(t1, v, 0xCC);
  r3 = _mm256_blend_ps(t3, v, 0x33);

  //r4 = _mm256_shuffle_ps(t4,t6, 0x44);
  //r5 = _mm256_shuffle_ps(t4,t6, 0xEE);
  v = _mm256_shuffle_ps(t4,t6, 0x4E);
  r4 = _mm256_blend_ps(t4, v, 0xCC);
  r5 = _mm256_blend_ps(t6, v, 0x33);

  //r6 = _mm256_shuffle_ps(t5,t7, 0x44);
  //r7 = _mm256_shuffle_ps(t5,t7, 0xEE);
  v = _mm256_shuffle_ps(t5,t7, 0x4E);
  r6 = _mm256_blend_ps(t5, v, 0xCC);
  r7 = _mm256_blend_ps(t7, v, 0x33);

  _mm256_store_ps(&matT[0*8], r0);
  _mm256_store_ps(&matT[1*8], r1);
  _mm256_store_ps(&matT[2*8], r2);
  _mm256_store_ps(&matT[3*8], r3);
  _mm256_store_ps(&matT[4*8], r4);
  _mm256_store_ps(&matT[5*8], r5);
  _mm256_store_ps(&matT[6*8], r6);
  _mm256_store_ps(&matT[7*8], r7);
}


int verify(float *mat) {
    int i,j;
    int error = 0;
    for(i=0; i<8; i++) {
      for(j=0; j<8; j++) {
        if(mat[j*8+i] != 1.0f*i*8+j) error++;
      }
    }
    return error;
}

void print_mat(float *mat) {
    int i,j;
    for(i=0; i<8; i++) {
      for(j=0; j<8; j++){ 
	printf("%2.0f ", mat[i*8+j]);
	}
	printf("\n");
    }
    printf("\n");
    return;
}

int main(void) {
    int i,j, rep;
    float mat[64] __attribute__((aligned(64)));
    float matT[64] __attribute__((aligned(64)));
    double dtime;
    time_t avxtime; time_t naivetime;
    time_t start;
    rep = 10000000;
    for(i=0; i<64; i++) mat[i] = i;
    printf("Naive\n");
    time(&start);
    for (i = 0; i < 1000000; i++) {
	NaiveTranspose(mat,matT);
    }
    naivetime = time(NULL) -start;
    printf("errors %d\n", verify(matT));
    printf("AVX\n");
    time(&start);
    for (i = 0; i < 1000000; i++) {
    	tran(mat,matT);
    }
    avxtime = time(NULL)-start;
    //dtime = -omp_get_wtime();
    //tran(mat, matT, rep);
    //dtime += omp_get_wtime();
    printf("errors %d\n", verify(matT));
    //printf("dtime %f\n", dtime);
    printf("Naive Time: %ld\n", naivetime);
    printf("AVX Time: %ld\n",avxtime);
}
