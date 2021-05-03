#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "nrutil.h"
#include "gaussj.c"
#include "nrutil.c"

#define x_min -5.0
#define x_max 5.0

float fun1(float x){
    return 1.0/(1.0+x*x);
}

float fun2(float x){
    return cos(2.0*x);
}


void wyzM(float *xw,float *yw, float *m, int n, float alfa, float beta){
    float **A = matrix(1,n,1,n);
    float **d = matrix(1,n,1,1);

    for(int i=1; i<n; i++){
        for(int j=1; j<=n; j++){
            A[i][j]=0;
        }
        d[i][1] =0;
    }

    m[1] = alfa;
    m[n] = beta;
    d[1][1] = alfa;
    d[n][1] = beta;
    A[1][1] = 1.0;
    A[n][n] = 1.0;
    A[1][2] = 0.0;
    A[n][n-1] = 0.0;
    float h = (x_max - x_min)/(n-1);
   
    float lambda = h/(h+h);
    
    float mi = 1.0 - lambda;
   
    for (int i=2; i < n; ++i) {
       
        A[i][i-1] = mi; 
        A[i][i] = 2.0;  
        A[i][i+1] = lambda;    
        d[i][1] = 6.0/(h + h) * ((yw[i+1] - yw[i])/h - (yw[i] - yw[i-1])/h);  
    }

    
    gaussj(A, n, d, 1);
     
    for(int i=2; i<n; i++){
        m[i] = d[i][1];
    }
    free_matrix(A,1,n,1,n);
    free_matrix(d,1,n,1,1);


}

float wyzSx(float *xw,float *yw, float *m, int n, float x){
    int j =1 ;
    for (int i=2; i<=n; i++){
        if (xw[i-1] <= x && x<= xw[i]) {
            j=i;
        }
    }
    float h = (x_max - x_min)/(n-1.0);
    float A = (yw[j] - yw[j-1])/h - (h/6)*(m[j]-m[j-1]);
    float B = yw[j-1] - m[j-1]*(h*h/6);
    float sx = m[j-1]*pow((xw[j]-x), 3)/(6*h) + m[j]* pow((x-xw[j-1]), 3)/(6*h)+A*(x-xw[j-1])+B;
    
    return sx;
}

float druga_pochodna(float (*f)(float), float x){
    float dx = 0.01;
    float df_2 =  (f(x-dx) - 2*f(x) + f(x+dx))/(dx*dx);
    return df_2;
}

void fill_x(float *xw, int n){
    float h = (x_max-x_min)/(n-1);
    xw[1] = x_min;
    xw[n] = x_max;
    for(int i=2; i<n; i++){
        xw[i] = x_min +(i-1)*h;
    }
}

void fill_y(float *yw, int n, float (*fun)(float), float *xw){
    for(int i=1; i<=n; i++){
        yw[i] = fun(xw[i]);
    }
}

void oblicz(float (*fun)(float), int n, FILE *f, float alfa, float beta){
    float *xw = vector(1,n);
    fill_x(xw,n);
   
    float *yw = vector(1,n);
    fill_y(yw, n, fun, xw);
    
    float *m = vector(1,n);
    wyzM(xw, yw, m, n, alfa, beta);
    for(int i=1; i<=n; i++){
        printf(" %f ", m[i]);
    }

    printf("AAAAAA");
    for (float x = x_min; x <= x_max; x += 0.01){
        float sx = wyzSx(xw, yw, m, n, x);
        printf("%f  %f\n", x, sx );
        fprintf(f,"%f  %f\n", x, sx);
    }   
    printf("\n\n");
    fprintf(f,"\n\n");

    free_vector(xw,1,n);
    free_vector(yw,1,n);
    free_vector(m,1,n);

}


int main(){
    float alfa = 0.0;
    float beta = 0.0;
    printf("AAAAAA\n");
    FILE *f1 = fopen("f1.dat", "w");
    oblicz(fun1, 5, f1, alfa, beta);
    oblicz(fun1, 8, f1, alfa, beta);
    oblicz(fun1, 21, f1, alfa, beta);
    fclose(f1);


    FILE *f2 = fopen("f2.dat", "w");
    oblicz(fun2, 5, f2, alfa, beta);
    oblicz(fun2, 8, f2, alfa, beta);
    oblicz(fun2, 21, f2, alfa, beta);
    fclose(f2);

    FILE *f3 = fopen("pochodne.dat", "w");
    int n= 10;
    float *xw = vector(1,n);
    fill_x(xw,n);
    float *yw = vector(1,n);
    fill_y(yw, n, fun1, xw);
    float *m = vector(1,n);
    wyzM(xw, yw, m, n, alfa, beta );
    for (int i = 1; i <= n; i++){
        float dp = druga_pochodna(fun1, xw[i]);
        printf("%f  %f  %f\n", xw[i], m[i], dp);
        fprintf(f3,"%f  %f  %f\n", xw[i], m[i], dp);
    }    
    printf("\n\n");
    fclose(f3);

    return 0;
}