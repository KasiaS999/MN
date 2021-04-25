#include <stdio.h>
#include <math.h>
#define N 7
#define IT_MAX 300

void matrix_vector(double (*M)[N], double *v0, double *v1){
  for(int i=0; i<N; i++){
    v1[i] =0;
    for(int j=0; j<N; j++){
      v1[i]+=M[i][j]*v0[j];
    }
  }
}


double vector_vector(double *v0, double *v1){
  double r = 0.0;
  for(int i=0; i<N; i++){
    r+= v0[i]*v1[i];
  }
  return r;
}

void macierz_macierz(double (*M1)[N], double (*M2)[N], double (*M_W)[N]){
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      M_W[i][j] =0;
      for(int k=0; k<N; k++)
        M_W[i][j] += M1[i][k]*M2[k][j]; 
    }
  }
}

int main(){
  
  double A[N][N];
  double W[N][N];
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      A[i][j] = 1./(sqrt(2.0+fabs(i-j)));
      W[i][j] = A[i][j];
    }
  }
  double x[N];
  double x_n[N];
  double lambda = 0;
  double norma = 0;
  FILE *f1 = fopen("wyn_l.dat", "w");
  FILE *f2 = fopen("wyn_D.dat", "w");
  FILE *f3 = fopen("wyn_x.dat", "w");
 
  double X[N][N];

  for(int k=0; k<N; k++){

    fprintf(f3, "%d \n",k);
    for(int i=0; i<N; i++){
      x[i] = 1;
    }
    for(int i=1; i<= IT_MAX; i++){
      matrix_vector(W, x, x_n);
      lambda = vector_vector(x_n, x)/vector_vector(x, x);
      fprintf(f1, "%d %g \n",i, lambda);
      norma = sqrt(vector_vector(x_n, x_n));
      for(int j=0; j<N; j++){
        x[j] = x_n[j]/norma;
      }
    }
    for(int i =0; i<N; i++){
      fprintf(f3, "%g \n",x[i]);
    }
    fprintf(f1, "\n\n");
    for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        W[i][j] = W[i][j] - lambda*x[i]*x[j];
      }
    }
    //fprintf(f1, "%d ", k);
    for(int i=0; i<N; i++){
      //fprintf(f1, " %g ", x[i]);
      X[i][k] = x[i];
    }
    //fprintf(f1, "\n");
  }

  double X_T[N][N];
  double Temp[N][N];
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      X_T[j][i] = X[i][j];
    }
  }

  /*for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      fprintf(f2, "%g ",A[i][j]);
    }
    fprintf(f2, "\n");
  }
  fprintf(f2, "\n");

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      fprintf(f2, "%g ", X[i][j]);
    }
    fprintf(f2, "\n");
  }
  fprintf(f2, "\n");

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      fprintf(f2, "%g ", X_T[i][j]);
    }
    fprintf(f2, "\n");
  }
  fprintf(f2, "\n");*/

  macierz_macierz(X_T, A, Temp);
    /*for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      fprintf(f2, "%g ", Temp[i][j]);
    }
    fprintf(f2, "\n");
  }
  fprintf(f2, "\n");*/
  double D[N][N];
  macierz_macierz(Temp, X, D);

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      fprintf(f2, "%g ", D[i][j]);
    }
    fprintf(f2, "\n");
  }
  fclose(f3);
  fclose(f1);
  fclose(f2);
  return 0;
}