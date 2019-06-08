#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>

#ifndef N_SIZE
#define N_SIZE 2
#endif

#ifndef N_OPR
#define N_OPR 48
#endif 

#ifndef N_ITER
#define N_ITER 1
#endif

FILE *M_gen;
FILE *M_out;
FILE *T_out;

int n_iter = N_OPR;//48*10;//*6000;
int numOfIter = N_ITER;
int n_mtx = N_SIZE;
int m_mtx = N_SIZE;
int max_value =1024;

int l_fld = 20;
int m_fld = 20;
int x;
int i_o;
int offst;
int mat_1[N_SIZE][N_SIZE];
int mat_2[N_SIZE][N_SIZE];
int mat_O[N_SIZE][N_SIZE];
int new_o = 1;
int new_f = 1;

char tmp_rd[10];

struct timeval start, end;

fpos_t position;

void mult_m(int mat1[][N_SIZE], int mat2[][N_SIZE], int res[][N_SIZE]){ 
    int i, j, k; 
    for (i = 0; i < N_SIZE; i++){ 
        for (j = 0; j < N_SIZE; j++){ 
            res[i][j] = 0; 
            for (k = 0; k < N_SIZE; k++) 
                res[i][j] += mat1[i][k] * mat2[k][j]; 
        } 
    } 
} 

int main(){
  // Create an array of elements
  // ID, N, M, M1, M2
  if (new_f == 1){
    M_gen = fopen ("M_gen.txt","w");
    for(int i=0; i < n_iter; i++){
      fprintf(M_gen, "%d %d %d ", i, n_mtx, m_mtx);
      for(int j=0; j < (2 * n_mtx); j++){
        for(int k=0; k < m_mtx; k++){
          // x in the range 0 to 1023
          x = rand() % max_value;  
          fprintf(M_gen, "%d ", x);
        }
      }
      fprintf(M_gen, "\n");
    }
    fclose (M_gen);
  }
  // Graphic representation
        
  // Read elements 
  gettimeofday(&start, NULL);
  for(int m=0; m < numOfIter; m++){
    new_o = 1;
    for(int i=0; i < n_iter; i++){
      M_gen = fopen ("M_gen.txt","r");
      fsetpos (M_gen, &position);
      fscanf(M_gen, "%d %d %d ", &i_o, &n_mtx, &m_mtx);
      //printf("--Loading \n"), i_o; 
      for(int j=0; j < n_mtx; j++){
        for(int k=0; k < m_mtx; k++){
          fscanf(M_gen, "%d ", &mat_1[j][k]);
          //printf("--Loading NUM: %d \n", mat_1[j][k]); 
        }
      }
      //printf("--Loading \n"); 
      for(int j=0; j < n_mtx; j++){
        for(int k=0; k < m_mtx; k++){
          fscanf(M_gen, "%d ", &mat_2[j][k]);
          //printf("--Loading NUM: %d \n", mat_2[j][k]); 
        }
      }
      fgetpos (M_gen, &position);
      //
      //position = position + 1;
      //
      fclose (M_gen);
      if(new_o == 1){
        M_out = fopen ("M_out.txt","w");
        new_o = 0;
      }else{
        M_out = fopen ("M_out.txt","a");
      }
      

      fprintf(M_out, "%d %d %d ", i, n_mtx, m_mtx);
      mult_m (mat_1, mat_2, mat_O);
      for(int j=0; j < n_mtx; j++){
        for(int k=0; k < m_mtx; k++){
          fprintf(M_out, "%d ", mat_O[j][k]);
        }
      }
      fprintf(M_out, "\n");
      fclose (M_out);

    }
  }
	gettimeofday(&end, NULL);

  
//  printf("Time1: %lf us\n", (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)))*1.0/numOfIter);
//  printf("Time2: %lf ms\n", (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)))*0.001/numOfIter);

double e_time = (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)))*0.000001/numOfIter;
printf("Time: %lf s\n", e_time);

T_out = fopen ("T_out.txt","a");
fprintf(T_out, "%d %d %lf\n", N_SIZE, N_OPR, e_time);
fclose (T_out);

return 0;
}