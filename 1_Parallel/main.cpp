#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <cstdlib>

#ifndef N_SIZE
#define N_SIZE 2
#endif

#ifndef N_OPR
#define N_OPR 48
#endif 

#ifndef N_ITER
#define N_ITER 1
#endif

FILE *T_out;

int n_iter_0 = N_OPR;//*6000;
int numOfIter = N_ITER;
int n_mtx = N_SIZE;
int m_mtx = N_SIZE;
int max_value =1024;

int l_fld = 20;
int m_fld = 20;

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

int main(int argc, char* argv[]) {

  MPI_Init(NULL, NULL);
    FILE *M_gen;
    FILE *M_out;
    int n_iter;
    int mat_1[N_SIZE][N_SIZE];
    int mat_2[N_SIZE][N_SIZE];
    int mat_O[N_SIZE][N_SIZE];
    int new_o = 1;
    int new_f = 1;
    int x;
    int i_o;
    char fn_gen[20];
    char fn_out[20];
    char tmp_rd[10];
    fpos_t position;
    struct timeval start, end;

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    
    n_iter = n_iter_0/world_size;
    
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
       
  // Read elements 
  gettimeofday(&start, NULL);

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
	
  gettimeofday(&end, NULL);
//  printf("Proc: %s, Rank: %d\tout of %d Time1: %lf us\n", processor_name, world_rank, world_size, (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)))*1.0/numOfIter);
//  printf("Proc: %s, Rank: %d\tout of %d Time2: %lf ms\n", processor_name, world_rank, world_size, (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)))*0.001/numOfIter);
  double e_time = (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)))*0.000001/numOfIter;
  double e_time_g;
  printf("Proc: %s, Rank: %d\tout of %d Time: %lf s\n", processor_name, world_rank, world_size, e_time);

  //printf("processor %s, rank %d out of %d processors\n",processor_name, world_rank, world_size);

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Reduce(&e_time, &e_time_g, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  e_time_g = e_time_g/world_size;

  if(world_rank == 0){
    T_out = fopen ("T_out.txt","a");
    fprintf(T_out, "%d %d %d %lf\n", world_size, N_SIZE, N_OPR, e_time_g);
    fclose (T_out);
  }

  MPI_Finalize();
  return 0;
}