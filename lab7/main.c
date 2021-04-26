#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define min -5
#define max 5


double fun(double x){
    return 1/(x*x+1);
}

void fill_x(int n, double *x){
    double h = ((double)(max-min)/(double)(n-1));
    for(int i=0; i<n; i++){
        x[i] = min + h*i;
    }
}

void fill_x_czebyszew(int n, double *x){
    double h = ((double)(max-min)/(double)(n-1));
    for(int i=0; i<n; i++){
        x[i] =0.5*((min-max)*cos(M_PI*(2*i + 1)/(2*(n-1)+2)));
    }
}

void fill_y(int n, double *x, double *y){
    for(int i=0; i<n; i++){
        y[i] = fun(x[i]);
    }
}

void fill_f(int n, double *x, double **f){
    for(int i=0; i<n; i++){
        f[i][0] = fun(x[i]);
    }
    for(int j=1; j<n; j++){
        for(int i=j; i<n; i++){
            f[i][j] = (f[i][j-1] - f[i-1][j-1])/(x[i]-x[i-j]);
        }
    }
}

double interpolacja_newtona(int n, double *x, double _x, double *f[]){
    double wyn = 0.0;
    for(int j=0; j<n; j++){
        double mn = 1.0;
        for(int i=0; i<j; i++){
            mn *= (_x - x[i]);
        }
        wyn += f[j][j]*mn;
    }
    return wyn;
}

int main(){
    
    FILE *f1 = fopen("zad_1.dat", "w");
    int n_5 =5;
    int n_10 =10;
    int n_15 =15; 
    int n_20 = 20;
    
    double *x_5 = malloc((n_5+1)*sizeof(double));
    fill_x(n_5+1, x_5);
    double *x_10 = malloc((n_10+1)*sizeof(double));
    fill_x(n_10+1, x_10);
    double *x_15 =  malloc((n_15+1)*sizeof(double));
    fill_x(n_15+1, x_15);
    double *x_20 =  malloc((n_20+1)*sizeof(double));
    fill_x(n_20+1, x_20);

    
    double *y_5 = malloc((n_5+1)*sizeof(double));
    fill_y(n_5+1,x_5, y_5);
    double *y_10 =  malloc((n_10+1)*sizeof(double));
    fill_y(n_10+1,x_10,  y_10);
    double *y_15 =  malloc((n_15+1)*sizeof(double));
    fill_y(n_15+1,x_15, y_15);
    double *y_20 =  malloc((n_20+1)*sizeof(double));
    fill_y(n_20+1,x_20, y_20);
    
    double **f_5 = malloc((n_5+1)*sizeof(double*));
    for(int i=0; i<=n_5; i++)
        f_5[i] = malloc((n_5+1)*sizeof(double));
    fill_f(n_5+1, x_5, f_5);
    double **f_10 = malloc((n_10+1)*sizeof(double*));
    for(int i=0; i<=n_10; i++)
        f_10[i] = malloc((n_10+1)*sizeof(double));
    fill_f(n_10+1, x_10, f_10);
    double **f_15 = malloc((n_15+1)*sizeof(double*));
    for(int i=0; i<=n_15; i++)
        f_15[i] = malloc((n_15+1)*sizeof(double));
    fill_f(n_15+1, x_15, f_15);
    double **f_20 = malloc((n_20+1)*sizeof(double*));
    for(int i=0; i<=n_20; i++)
        f_20[i] = malloc((n_20+1)*sizeof(double));
    fill_f(n_20+1, x_20, f_20);
    
    double W_5 = 0;
    for(float j = min; j<=max; j+=0.01){
        W_5 = interpolacja_newtona(n_5+1, x_5, j, f_5);
        fprintf(f1,  "%f  %g\n", j, W_5);
    }
    fprintf(f1,"\n\n");

    double W_10 = 0;
    for(float j = min; j<=max; j+=0.01){
        W_10 = interpolacja_newtona(n_10+1, x_10, j, f_10);
        fprintf(f1,  "%f  %g\n", j, W_10);
    }
    fprintf(f1,"\n\n");

    double W_15 = 0;
    for(float j = min; j<=max; j+=0.01){
        W_15 = interpolacja_newtona(n_15+1, x_15, j, f_15);
        fprintf(f1,  "%f  %g\n", j, W_15);
    }
    fprintf(f1,"\n\n");

    double W_20 = 0;
    for(float j = min; j<=max; j+=0.01){
        W_20 = interpolacja_newtona(n_20+1, x_20, j, f_20);
        fprintf(f1,  "%f  %g\n", j, W_20);
    }
    fprintf(f1,"\n\n");
    

    ///////////////////CZEBYSZEW///////////////////////

    FILE *f2 = fopen("zad_2.dat", "w");

    fill_x_czebyszew(n_5+1, x_5);
    fill_x_czebyszew(n_10+1, x_10);
    fill_x_czebyszew(n_15+1, x_15);
    fill_x_czebyszew(n_20+1, x_20);

    fill_y(n_5+1,x_5, y_5);
    fill_y(n_10+1,x_10, y_10);
    fill_y(n_15+1,x_15, y_15);
    fill_y(n_20+1,x_20, y_20);


    fill_f(n_5+1, x_5, f_5);
    fill_f(n_10+1, x_10, f_10);
    fill_f(n_15+1, x_15, f_15);
    fill_f(n_20+1, x_20, f_20);

    W_5 = 0;
    for(float j = min; j<=max; j+=0.01){
        W_5 = interpolacja_newtona(n_5+1, x_5, j, f_5);
        fprintf(f2,  "%f  %g\n", j, W_5);
    }
    fprintf(f2,"\n\n");

    W_10 = 0;
    for(float j = min; j<=max; j+=0.01){
        W_10 = interpolacja_newtona(n_10+1, x_10, j, f_10);
        fprintf(f2,  "%f  %g\n", j, W_10);
    }
    fprintf(f2,"\n\n");

    W_15 = 0;
    for(float j = min; j<=max; j+=0.01){
        W_15 = interpolacja_newtona(n_15+1, x_15, j, f_15);
        fprintf(f2,  "%f  %g\n", j, W_15);
    }
    fprintf(f2,"\n\n");

    W_20 = 0;
    for(float j = min; j<=max; j+=0.01){
        W_20 = interpolacja_newtona(n_20+1, x_20, j, f_20);
        fprintf(f2,  "%f  %g\n", j, W_20);
    }
    fprintf(f2,"\n\n");
    
    
    for(int i=0; i<=n_5; i++){
        free(f_5[i]);
    }
    free(f_5);
    for(int i=0; i<=n_10; i++){
        free(f_10[i]);
    }
    free(f_10);
    for(int i=0; i<=n_15; i++){
        free(f_15[i]);
    }
    free(f_15);
    for(int i=0; i<=n_20; i++){
        free(f_20[i]);
    }

    free(f_20);
    free(x_5);
    free(x_10);
    free(x_15);
    free(x_20);
    free(y_5);
    free(y_10);
    free(y_15);
    free(y_20);
    fclose(f1);
    fclose(f2);
    return 0;
}