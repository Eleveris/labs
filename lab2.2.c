#define N 20

#include <stdio.h>


void input(char* str,int n);
void output(char* str,int n);

int main (){
    char str1[N],str2[N];
    int n=N;
    int check=0;
    input(&str1[0],N);

    for (int i=0; i < N; i++)
        str2[i]=str1[i];

    for (int i=0; i<n; i++){
        if (str2[i] == '(') {check++; continue;}
        if ((str2[i] == ')') && (check>0)) {check--; continue;}
        if (!check) continue;
        n--;
        for (int j=i; j<n; j++){
            str2[j]=str2[j+1];
        }
        i--;
    }

    output(&str2[0],n);
    return 0;

}

void input (char *str, int n){
    for (int i=0; i<n; i++){
        scanf("%c",&str[i]);
    }
    return;
}

void output (char *str, int n){
    for (int i=0; i<n; i++){
        printf("%c",str[i]);
    }
}