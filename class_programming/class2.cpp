#include <stdio.h>
#include <string.h>

int main(){
    char s[1001];
    while(fgets(s, sizeof(s), stdin)){
        if(s[0] == '0') break;
        s[strcspn(s, "\n")] = '\0';
        int sum = 0;
        for(int i=0; i<strlen(s); i++){
            if(i%2 == 0) sum += s[i]-'0';
            else sum -= s[i]-'0';
        }
        printf ("%s", s);
        if(sum%11==0) printf (" is a multiple of 11.\n");
        else printf (" is not a multiple of 11.\n");
    }
}