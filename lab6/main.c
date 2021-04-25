
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define N 5
#define IT_MAX 30

double licz_r(double *a, double *b, int n, double xj){
    b[n] = 0;
    for(int k=n-1; k>=0; k--){
        b[k] = a[k+1]+xj*b[k+1];
    }
    return a[0]+xj*b[0];
}

int main(){

    FILE *f = fopen("wyn.dat", "w");
    
    double a[N+1];
    double b[N+1];
    double c[N];
    int n;
    double x0, x1, Rj, Rj_p;

    a[0] = 240;
    a[1] = -196;
	a[2] = -92.0;
	a[3] = 33.0;
	a[4] = 14.0;
	a[5] = 1.0;  

    for(int L=1; L<=N; L++){
        n = N-L+1;
        x0 = 0;
        for(int it=1; it<=IT_MAX; it++){
            Rj = licz_r(a,b,n, x0);
            Rj_p = licz_r(b,c,n-1, x0);
            x1 = x0 - (Rj/Rj_p);

            fprintf(f, "%12d %12d %12g %12g %12g\n", L, it, x1, Rj, Rj_p);

            if (fabs(x1-x0) < 1.0e-7) break;
            x0 = x1;

        }
        
        for(int i=0; i<=(n-1); i++) a[i] = b[i];
        fprintf(f, "\n Znalezione zero wielomianu: %g \n\n\n", x1);
    }

    fclose(f);
    return 0;
}