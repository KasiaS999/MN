#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 200

double f(double x, double y){
    return sin(x)*sin(y)-exp(-(x+M_PI/2.0)*(x+M_PI/2.0)-(y-M_PI/2.0)*(y-M_PI/2.0));
}

double d_rand(const double min, const double max){
    double r = (double)rand()/ RAND_MAX;
    r = r *(max-min)+min;
    return r;
}

void wsp_poczatkowe(double wedrowcy[N][2]){
    for(int i=0; i<N; i++){
        wedrowcy[i][0] = 5;
        wedrowcy[i][1] = 5;
    }
}

double losuj_x(double wedrowcy[N][2], int i, double x_min, double x_max){
    double x;
    while(1){
        x = d_rand(-1, 1);
        if(wedrowcy[i][0]+x <= x_max && wedrowcy[i][0]+x >= x_min) return x;
    }
}

double losuj_y(double wedrowcy[N][2], int i, double y_min, double y_max){
    double y;
    while(1){
        y = d_rand(-1, 1);
        if(wedrowcy[i][1]+y <= y_max && wedrowcy[i][1]+y >= y_min) return y;
    }
}



int main(){
    
    double x_min = -10;
    double x_max = 10;
    double y_min = -10;
    double y_max = 10;
    double wedrowcy[N][2];

    wsp_poczatkowe(wedrowcy);

    FILE *f1= fopen("w0.dat", "w");
    FILE *f2 = fopen("T.dat", "w");

    for(int it = 0; it<=20; it++){
        double T = 10/pow(2, it);

        for(int k=0; k<100; k++){
            for(int i=0; i<N; i++){
                double delta_x = losuj_x(wedrowcy, i, x_min, x_max);
                double delta_y = losuj_y(wedrowcy, i, y_min, y_max);
                if(f(wedrowcy[i][0]+delta_x, wedrowcy[i][1]+delta_y)<f(wedrowcy[i][0], wedrowcy[i][1])){
                    wedrowcy[i][0] += delta_x;
                    wedrowcy[i][1] += delta_y; 
                }
                else if(d_rand(0,1)< exp(-(f(wedrowcy[i][0]+delta_x,  wedrowcy[i][1]+delta_y ) - f(wedrowcy[i][0], wedrowcy[i][1]) )/(T))){
                    wedrowcy[i][0] += delta_x;
                    wedrowcy[i][1] += delta_y;
                }
                if (i == 0 ) fprintf(f1, "%g\n", f(wedrowcy[i][0], wedrowcy[i][1]));
            }
        }
        if(it == 0 || it == 7 || it == 20){
            for( int i=0; i<N; i++){
                fprintf(f2, "%g %g\n", wedrowcy[i][0], wedrowcy[i][1] );
            }
            fprintf(f2, "\n\n");
        }
    }
    double min_wedrowiec[2];
    min_wedrowiec[0] = wedrowcy[0][0];
    min_wedrowiec[1] = wedrowcy[0][1];
    for(int i = 0; i<N; i++){
        if(f(wedrowcy[i][0], wedrowcy[i][1])<f(min_wedrowiec[0], min_wedrowiec[1])){
            min_wedrowiec[0] = wedrowcy[i][0];
            min_wedrowiec[1] = wedrowcy[i][1];

        } 
    }
    printf("Znalezione minimum (%g, %g), dla ktorego f(x_min, y_min) = %g\n", min_wedrowiec[0], min_wedrowiec[1],f(min_wedrowiec[0], min_wedrowiec[1]));
    fclose(f1);
    fclose(f2);
    
    return 0;
}