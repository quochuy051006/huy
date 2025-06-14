#include <stdio.h>

int main(){
    int k;
    while(scanf ("%d", &k) != EOF){
        int sum = 1;
        int i = 1;
        while(k > sum){
            i++;
            sum+=i;
        }
        printf ("TERM %d IS ", k);
        if(i%2==0) printf ("%d/%d\n", i - sum + k, sum-k+1);
        else printf ("%d/%d\n", sum-k+1, i-sum+k);
    }
}