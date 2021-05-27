#include <stdio.h>
#include <math.h>
#include <time.h>
#include "nrutil.c"
#include "nrutil.h"
#include "four1.c"

float los(){
    return (float)rand() / RAND_MAX - 0.5;
}

float fun(float t,float T){
    float w = 2.0*M_PI/T;
    return sin(w*t)+sin(2*w*t)+sin(3*w*t);
}

float fun_s(float t,float T){
    
    return fun(t, T)+los();
}

float g(float sigma, float t){
    return (1.0/sqrt(2*M_PI))*exp(-(t*t/(2*sigma*sigma)));
}

void fill(float *f, int n, float dt, float T, float sigma, float *g1, float *g2){
    for (int i=1; i<=n; i++){
        float t_i = dt*(i-1);
        f[2*i-1] =  fun_s(t_i, T);
        f[2*i] = 0;
        g1[2*i-1] = g(sigma, t_i);
        g2[2*i-1] = g(sigma, t_i);
        g1[2*i]=0;
        g2[2*i]=0;
    }
}

void splot(int n, float *f, float *g1, float *g2){
    float a1, a2, b1, b2;
    for(int i=1; i<n; i++){
        a1 = f[2*i-1];
        b1 = f[2*i];
        a2 = g1[2*i-1]+g2[2*i-1];
        b2 = g1[2*i]+g2[2*i];
        f[2*i-1] = a1*a2-b1*b2;
        f[2*i] = a1*b2+a2*b1;
    }
}

int main(){
    srand(time(NULL));
    // FILE* file =  fopen("k8.dat", "w");
    // int k = 8;

    // FILE* file =  fopen("k10.dat", "w");
    // int k = 10;

    FILE* file =  fopen("k12.dat", "w");
    int k = 12;


    int n = pow(2,k);
    float T = 1.0;
    float t_max = 3.0*T;
    float dt = t_max/n;
    printf("dt = %g\n", dt);
    float sigma = T/20.0;
    float *f = vector(1, 2*n); 
    float *g1 = vector(1, 2*n);
    float *g2 = vector(1, 2*n);
    fill(f, n, dt, T, sigma, g1, g2);

    for(int i=1; i<=n; i++){
        fprintf(file, "%f %f\n", dt*(i-1), f[2*i - 1]);
    }
    fprintf(file, "\n\n");


    four1(f, n, 1);
    four1(g1, n, 1);
    four1(g2, n, -1);

    splot(n, f, g1, g2);

    four1(f, n, -1);

    float f_max = f[1];
    for(int i=2; i<=n; i++){
        if(f[2*i-1]>f_max) f_max = f[2*i-1];
    }
    printf("f_max = %g dla k = %d\n", f_max, k);
    for(int i=1; i<=n; i++){
        fprintf(file, "%f %f\n", dt*(i-1), f[2*i - 1]*(2.5/f_max));
    }
    fprintf(file, "\n\n");

    free_vector(f, 1, 2*n);
    free_vector(g1, 1, 2*n);
    free_vector(g2, 1, 2*n);
    fclose(file);
    return 0; 
}