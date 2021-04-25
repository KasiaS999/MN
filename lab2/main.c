#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nrutil.c"
#include "ludcmp.c"
#include "lubksb.c"
#include "nrutil.h"

#define N 3
void set_AB(float **A, float **B){
  int a = 1;
  for(int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
      A[i][j] = B[i][j] = a;
      a++;
    }
  }
  B[1][1]=1.1;
}


void fprint(char *s, float **M, FILE *f){
  fprintf(f, "%s\n", s);
  for(int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
      fprintf(f, " %14g ", M[i][j]);
    }
    fprintf(f, "\n");
  }
  fprintf(f, "\n");

}

void set_L_U(float **M, float **M_U, float **M_L){
  for(int i = 1; i<=N; i++){
    for(int j=1; j<=N; j++){
      if(i<j){
        M_L[i][j] = 0;
        M_U[i][j] = M[i][j];
      }
      else if (i == j){
        M_L[i][j] = 1;
        M_U[i][j] = M[i][j];
      }
      else{
        M_L[i][j] = M[i][j];
        M_U[i][j] = 0;
      }
    }
  }
}


void find_M_i(float **M, float ** M_i, int *indx_M){
  float *x = vector(1, N);
  for(int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
      x[j] =0;
    }
    x[i] = 1;
    lubksb(M,N, indx_M, x);
    for(int j=1; j<=N; j++){
      M_i[j][i] = x[j];
    }
  }
  free_vector(x, 1, N);
}

float find_max(float **M){
  float max = fabs(M[1][1]);
  for(int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
      if (max < fabs(M[i][j])){
        max = fabs(M[i][j]);
      }
    }
  }
  return max;
}

void matrix_mult(float **MM_i, float **M, float **M_i){
  
  for (int i=1; i<=N; i++){
    for(int j=1; j<=N; j++){
      MM_i[i][j] = 0;
      for(int k = 1; k<=N; k++) MM_i[i][j]+=M[i][k]*M_i[k][j];
    }   
  }
}
int main(){
  float **A = matrix(1, N, 1, N);
  float **B = matrix(1, N, 1, N);
  FILE *f = fopen("f.dat", "w");
  set_AB(A, B);
  fprint("Macierz A:", A, f);
  fprint("Macierz B:", B, f);

  int * indx_A = ivector(1, N);
  int * indx_B = ivector(1, N);
  float d_A; 
  float d_B;

  ludcmp(A, N, indx_A, &d_A);
  ludcmp(B, N, indx_B, &d_B);

  float **A_L = matrix(1, N, 1, N);
  float **A_U = matrix(1, N, 1, N);
  float **B_U = matrix(1, N, 1, N);
  float **B_L = matrix(1, N, 1, N);

  set_L_U(A, A_U, A_L);
  set_L_U(B, B_U, B_L);
  
  fprint("Macierz A_L:", A_L, f);
  fprint("Macierz A_U:", A_U, f);
  fprint("Macierz B_L:", B_L, f);
  fprint("Macierz B_U:", B_U, f);

  float **A_i = matrix(1, N, 1, N);
  float **B_i = matrix(1, N, 1, N);

  find_M_i(A, A_i, indx_A);
  find_M_i(B, B_i, indx_B);

  fprint("Macierz A^(-1): ", A_i, f);
  fprint("Macierz B^(-1): ", B_i, f);

  set_AB(A, B);

  float max_A = find_max(A);
  float max_A_i = find_max(A_i);
  float K_A = max_A*max_A_i;
  
  float max_B = find_max(B);
  float max_B_i = find_max(B_i);
  float K_B = max_B*max_B_i;

  fprintf(f, "Wskaźnik uwarunkowania macierzy A: \n");
  fprintf(f, "norma A (= %g ) * norma A^(-1) (= %g) = %g \n", max_A, max_A_i, K_A);

  fprintf(f, "Wskaźnik uwarunkowania macierzy B: \n");
  fprintf(f, "norma B (= %g ) * norma B^(-1) (= %g) = %g \n\n", max_B, max_B_i, K_B);

  float **AA_i = matrix(1, N,1,N);
  float **BB_i = matrix(1, N,1,N);

  matrix_mult(AA_i, A, A_i);
  matrix_mult(BB_i, B, B_i);

  fprint("Macierz A*A^(-1): ", AA_i, f);
  fprint("Macierz B*B^(-1): ", BB_i, f);

  fclose(f);
  free_matrix(A,1,N,1,N);
  free_matrix(B,1,N,1,N);
  free_matrix(A_L,1,N,1,N);
  free_matrix(A_U,1,N,1,N);
  free_matrix(B_L,1,N,1,N);
  free_matrix(B_U,1,N,1,N);
  free_matrix(A_i,1,N,1,N);
  free_matrix(B_i,1,N,1,N);
  free_matrix(AA_i,1,N,1,N);
  free_matrix(BB_i,1,N,1,N);
  free_ivector(indx_A, 1, N);
  free_ivector(indx_B, 1, N);
}