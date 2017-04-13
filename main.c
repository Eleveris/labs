#include <stdio.h>

int check(int N);

int main() {
    int N;
    scanf("%d",&N);
    check(N)?printf("Divisible, %d",N):printf("Indivisible, %d",N);
    return 0;
}

int check(int N){
    int i=2;
    while (i<=(N / 2)){
        if (!(N % i)) return 1;
        i++;
    }
    return 0;
}