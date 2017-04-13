#define N 10
#include <stdio.h>
char str[100];

int input(int n);
void output(int n);

int main(){
    int count=0;
    if (input(N)) return 1;
    output(N);
    for (int i=0; i<N; i++){
        if (    (str[i] == '.') ||
                (str[i] == ',') ||
                (str[i] == ':') ||
                (str[i] == ';') ||
                (str[i] == '-')    ) count++;
    }
    printf("\n%d", count);
    return 0;
}

int input(int n){
    printf("\n");
    for (int i=0; i<n; i++){
        scanf("%c",&str[i]);
    }
    return 0;
}
void output(int n){
    printf("\n");
    for (int i=0; i<n; i++){
        printf("%c",str[i]);
    }
    return;
}