#include <stdio.h>
#include <math.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

double ro(int alfa, double x){
    return 1+4.0*alfa*x*x;
}

int d(int i, int j){
    if(i==j) return 1;
    else return 0;
}

double x_i(int i, double L, double dx){
    return (-L)/2.0+dx*(i+1);
}


void matrix_set(gsl_matrix *A, int n, double N, double dx, int alfa, double L){
     for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if( i == j)
                gsl_matrix_set(A, i, j, (2.0*N)/(ro(alfa, x_i(i, L, dx))*dx*dx));
            if (i == j+1 || i == j-1)
                 gsl_matrix_set(A, i, j, (-1.0*N)/(ro(alfa, x_i(i, L, dx))*dx*dx));
  
            
        }
    }
}

int main(){

    FILE *f1 = fopen("w.dat", "w");
    FILE *f2 = fopen("a_0.dat", "w");
    FILE *f3 = fopen("a_100.dat", "w");

    int N=1, n=200;
    double L = 10;
    double dx = L/(n+1);

  
    gsl_matrix *A = gsl_matrix_calloc(n,n);
    

    gsl_vector_complex *eval=gsl_vector_complex_calloc(n);
    gsl_matrix_complex *evec=gsl_matrix_complex_calloc(n,n);
    gsl_eigen_nonsymmv_workspace *w = gsl_eigen_nonsymmv_alloc(n);

    for(int alfa=0; alfa<=100; alfa+=2){
        gsl_matrix_set_zero(A);
        matrix_set(A, n, N, dx, alfa, L);

        gsl_eigen_nonsymmv(A, eval, evec, w);
        gsl_eigen_nonsymmv_sort(eval, evec, GSL_EIGEN_SORT_ABS_ASC);


        fprintf(f1, "%d ", alfa);
        for(int i=0; i<6; i++){
            gsl_complex cval = gsl_vector_complex_get(eval,i) ;
            double val =GSL_REAL(cval);
            fprintf(f1, "%6g ", sqrt(val));
        }
        fprintf(f1, "\n");

        if(alfa == 0 ){
            
            for ( int i =0; i<n ; i ++){
                fprintf(f2, "%6g ", x_i(i, L, dx));
                for(int j=0; j<6; j++){
                    gsl_complex cv = gsl_matrix_complex_get ( evec , i , j);
                    double val = GSL_REAL(cv);
                    fprintf(f2, "%6g ", val);
                }
                fprintf(f2, "\n");
            }           
        }

        if(alfa == 100 ){
            
            for ( int i =0; i<n ; i ++){
                fprintf(f3, "%6g ", x_i(i, L, dx));
                for(int j=0; j<6; j++){
                    gsl_complex cv = gsl_matrix_complex_get ( evec , i ,j);
                    double val = GSL_REAL(cv);
                    fprintf(f3, "%6g ", val);
                }
                fprintf(f3, "\n");
            }           
        }

    }

    gsl_matrix_free(A);
    gsl_matrix_complex_free(evec);
    gsl_vector_complex_free(eval);
    gsl_eigen_nonsymmv_free (w) ;
    fclose(f1);
    fclose(f2);
    fclose(f3);

    return 0;
}