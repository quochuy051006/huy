#include <stdio.h>

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int a, b;
        scanf("%d%d", &a, &b);
        int sum = 0;
        if(a%2 ==  0) a+=1;
        for(int i=a; i<=b; i+=2) sum+=i;
        printf ("%d\n", sum);
    }
}