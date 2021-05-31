#include <stdio.h>
#include <math.h>

double a = 0;
double b = 1;

double f(double x){
    return log(x*x*x+3*x*x+x+0.1)*sin(18*x);
}

void Simpson(int n, double D[n+1][n+1]){

    for (int w=0; w<=n; w++){
        double N = pow(2, w+1);
        double h = (b-a)/N;
        double s = 0.0;
        for(int i=0; i<=N/2-1; i++){
            s+=(h/3)*
            (f(a+2*i*h)+
            4*f(a+(2*i+1)*h)+
            f(a+(2*i+2)*h));
        }
        D[w][0] = s;
       
    }  
}

void Milne(int n, double D[n+1][n+1]){
    for (int w=0; w<=n; w++){
        double N = pow(2, w+2);
        double h = (b-a)/N;
        double s = 0.0;
        for(int i=0; i<=N/4-1; i++){
            s+=(4*h/90)*
            (7*f(a+4*i*h)+
            32*f(a+(4*i+1)*h)+
            12*f(a+(4*i+2)*h)+
            32*f(a+(4*i+3)*h)+
            7*f(a+(4*i+4)*h));
        }
        D[w][0] = s;
       
    }  
}



void Richardson(int n, double D[n+1][n+1]){
    for(int w=1; w<=n; w++){
        for(int k=1; k<=w; k++){
            D[w][k] = (pow(4, k)*D[w][k-1]-D[w-1][k-1])/(pow(4, k)-1);
        }
    }
}

int main(){

    int n = 8; 
    double D[n+1][n+1];
    Simpson(n, D);
    Richardson(n, D);
    printf("\nSIMPSON\n\n");
    for(int i=0; i<=n; i++)   printf("%.10f     %.10f\n", D[i][0], D[i][i]);
    FILE *f = fopen("wyniki.dat", "w");
    fprintf(f, "\n\n-------------Simpson--------------\n\n");
    for(int w = 0; w<=n; w++){
        for(int k=0; k<=w; k++){
            fprintf(f, "%15.10f  ", D[w][k]);
        }
        fprintf(f, "\n");
    }
    Milne(n, D);
    Richardson(n, D);
    printf("\nMILNE\n\n");
    for(int i=0; i<=n; i++)   printf("%.10f     %.10f\n", D[i][0], D[i][i]);
    fprintf(f, "\n\n-------------Milne--------------\n\n");
    for(int w = 0; w<=n; w++){
        for(int k=0; k<=w; k++){
            fprintf(f, "%15.10f  ", D[w][k]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return 0;
}