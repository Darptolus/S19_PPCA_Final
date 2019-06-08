#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <cstdlib>
#define N 10 

int n_iter_0 = 12;//1024*100;//*6000;
int n_mtx = N;
int m_mtx = N;
int max_value =1024;
int numOfIter = 10;

int l_fld = 20;
int m_fld = 20;

void mult_m(int mat1[][N], int mat2[][N], int res[][N]){ 
    int i, j, k; 
    for (i = 0; i < N; i++){ 
        for (j = 0; j < N; j++){ 
            res[i][j] = 0; 
            for (k = 0; k < N; k++) 
                res[i][j] += mat1[i][k] * mat2[k][j]; 
        } 
    } 
} 

int main(int argc, char* argv[]) {
/*    struct timeval start, end;
gettimeofday(&start, NULL);
*/
  MPI_Init(NULL, NULL);
    FILE *M_gen;
    FILE *M_out;
    int n_iter;
    int mat_1[N][N];
    int mat_2[N][N];
    int mat_O[N][N];
    int new_o = 1;
    int new_f = 1;
    int x;
    int i_o;
    char fn_gen[20];
    char fn_out[20];
    char tmp_rd[10];
    fpos_t position;
    
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    
    n_iter = n_iter/world_size;
    
    //printf("Hello world from processor %s, rank %d out of %d processors\n",processor_name, world_rank, world_size);

  // Create an array of elements
  // ID, N, M, M1, M2
  //for (int g = 0; g< world_size; g++){
  sprintf(fn_gen, "M_gen_%d.txt", world_rank);
  sprintf(fn_out, "M_out_%d.txt", world_rank);
    //printf("%s\n", tmp_fn);
  //}
  if (new_f == 1){
    M_gen = fopen (fn_gen,"w");
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
/*        
  // Read elements 
  for(int m=0; m < numOfIter; m++){
    new_o = 1;
    for(int i=0; i < n_iter; i++){
      M_gen = fopen (fn_gen,"r");
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
        M_out = fopen (fn_out,"w");
        new_o = 0;
      }else{
        M_out = fopen (fn_out,"a");
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
	
*/
  printf("processor %s, rank %d out of %d processors\n",processor_name, world_rank, world_size);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
/*
  gettimeofday(&end, NULL);
  printf("Time1: %lf us\n", (((end.tv_sec * 1000000 + end.tv_usec)
				- (start.tv_sec * 1000000 + start.tv_usec)))*1.0/numOfIter);
  printf("Time2: %lf ms\n", (((end.tv_sec * 1000000 + end.tv_usec)
				- (start.tv_sec * 1000000 + start.tv_usec)))*0.001/numOfIter);
  printf("Time3: %lf ms\n", (((end.tv_sec * 1000000 + end.tv_usec)
				- (start.tv_sec * 1000000 + start.tv_usec)))*0.000001/numOfIter);
*/
  return 0;
}