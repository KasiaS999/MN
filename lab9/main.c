#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 201
#define frand() ((double)rand())/(RAND_MAX+1.0)
#define x_min -4
#define x_max 4


double f(double x){
    double s = (x_max-x_min)/16.0;
    double x0 = 2.0;
    return sin(14*M_PI*x / (x_max - x_min))*(exp(-(x-x0)*(x-x0) / (2*s*s)) + exp(-(x+x0)*(x+x0)/ (2*s*s)));
}

double f_szum(double x){
    return f(x)+(frand()-0.5)/5;
}

void X(double *x){
    double h = (x_max-x_min)/(N-1.0);
    for(int i=0; i<N; i++){
        x[i] = x_min+h*i;
        
    }
}

void Y(double *y, double *x){
    for(int i=0; i<N; i++){
        y[i] = f_szum(x[i]);
    }
}
double alfa(double *phi_1, double *x){
    double l = 0.0;
    double m = 0.0;
    for(int i=0; i<N; i++){
        l+= x[i] * phi_1[i] * phi_1[i];
        m+= phi_1[i] * phi_1[i];

    }
    return (double)l/m;
}
double beta(double *phi_1, double *phi_2, double *x){
    double l = 0.0;
    double m = 0.0;
    for(int i=0; i<N; i++){
        l+= x[i] * phi_2[i] * phi_1[i];
        m+= phi_2[i] * phi_2[i];

    }
    return (double)l/m;
}
void PHI(double **phi, double *x, int m){
    for(int i=0; i<N; i++) phi[0][i] = 1;
    double a = alfa(phi[0], x);
    //printf("%g \n",a);
    for(int i=0; i<N; i++) phi[1][i] = (x[i]-a)*phi[0][i];
    for(int i=2; i<(m+1); i++){
        a = alfa(phi[i-1], x);
        double b = beta(phi[i-1], phi[i-2], x);
        //if(i<6) printf("%g %g \n", a,b);
        for(int j=0; j<N; j++){
            phi[i][j] = (x[j]- a)*phi[i-1][j]- b*phi[i-2][j];
        }
    }
}

double c(double *y, double *phi){
    double c = 0.0;
    for(int i=0; i<N; i++) c+= y[i]*phi[i];
    return c;
}

double s(double *phi){
    double sum = 0.0;
    for(int i=0; i<N; i++) sum+= phi[i]*phi[i];
    

    return sum;
}

void aproksymacja(double *F, double *y, double **phi, int m){
    for(int i = 0; i<N; i++){
        double sum = 0.0;
        for(int j = 0; j<(m+1); j++){
            sum += (c(y, phi[j])/s(phi[j]))*phi[j][i];
        }
        F[i] = sum;
    }
}

int main(){
    int m = 50;

    double *x = malloc(N*sizeof(double));
    X(x);

    double *y = malloc(N*sizeof(double));
    Y(y,x);

    FILE * f1 = fopen("pkt.dat", "w");
	for(int i = 0; i < N; ++i)
		fprintf(f1, "%g  %g\n", x[i], y[i]);
	fclose(f1);


    double **phi = malloc((m+1)*sizeof(double*));
    for(int i=0; i<(m+1); i++){
        phi[i] = malloc(N*sizeof(double));
    }
    PHI(phi, x, m);

    FILE *f2 = fopen("Gram.dat", "w");
    for(int i = 0; i<N; ++i)
	{
		fprintf(f2, "%g  ", x[i]);
		for(int j = 0; j<7; ++j)
			fprintf(f2, "%g  ", phi[j][i] / phi[j][0]);
		fprintf(f2, "\n");
	}
	fclose(f2);


    FILE *f =  fopen("approx.dat", "w");
    double *F1 = malloc(N*sizeof(double));
    aproksymacja(F1, y, phi, 10);
    for(int j = 0; j < N; ++j)
			fprintf(f, "%g  %g\n", x[j], F1[j]);
	fprintf(f, "\n\n");
    free(F1);

    double *F2 = malloc(N*sizeof(double));
    aproksymacja(F2, y, phi, 30);
    for(int j = 0; j < N; ++j)
			fprintf(f, "%g  %g\n", x[j], F2[j]);
	fprintf(f, "\n\n");
    free(F2);

    double *F3 = malloc(N*sizeof(double));
    aproksymacja(F3, y, phi, 50);
    for(int j = 0; j < N; ++j)
			fprintf(f, "%g  %g\n", x[j], F3[j]);
	fprintf(f, "\n\n");
    free(F3);

    fclose(f);
    free(x);
    free(y);
    for(int i=0; i<(m+1); i++){
        free(phi[i]);
    }
    free(phi);
    

}