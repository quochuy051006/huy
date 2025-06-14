#include <stdio.h>
#include <math.h>

int main(){
    FILE *f1 = fopen("input.txt", "r");
    FILE *f2 =fopen("output.txt", "w");
    int d;
    while(fscanf(f1, "%d", &d) != EOF){
        int lim = pow(10, d);
        int base = pow(10, d/2);
        for(int i=0; i<lim; i++){
            int a = i/base;
            int b = i%base;
            if((a+b) * (a+b) == i) fprintf(f2, "%0*d\n", d, i);
        }
    }
    fclose(f1);
    fclose(f2);
}