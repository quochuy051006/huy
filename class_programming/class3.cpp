#include <stdio.h>
#include <string.h>

int main(){
    char s[1001];
    while(fgets(s, sizeof(s), stdin)){
        if(s[0] == '0') break;
        s[strcspn(s, "\n")] = '\0';
        int sum = 0;
        for(int i=0; i<strlen(s); i++) sum+= s[i]-'0';
        if(sum%9 != 0) printf ("%s is not a multiple of 9.\n", s);
        else{
            int cnt = 0;
            int k = sum;
            while(k!=9){
                int numSum = 0;
                while(k>0){
                    numSum += (k%10);
                    k/=10;
                }
                cnt++;
                k = numSum;
            }
            printf("%s is a multiple of 9 and has 9-degree %d.\n", s, cnt+1);
        }
    }
}