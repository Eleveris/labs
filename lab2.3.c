#define N 2
#define M 5

#include <stdio.h>


void input(int* arr[N][M],int n,int m);
void output(int* arr[N][M],int n, int m);

int main (){
    int arr1[N][M],arr2[N][M];
    int swap;
    input(&arr1[0][0],N,M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            arr2[i][j] = arr1[i][j];
        }
    }

    for (int i = 1; i < M; i++){
        for (int j = 0; j < (M-i); j++){
            if (arr2[0][j] > arr2[0][j+1]) {
                for (int l = 0; l < N; l++){
                    swap = arr2[l][j];
                    arr2[l][j] = arr2[l][j+1];
                    arr2[l][j+1] = swap;
                }
            }
        }
    }

    output(&arr2[0][0],N,M);
    return 0;

}

void input (int *arr[N][M], int n,int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    return;
}

void output (int *arr[N][M], int n, int m){
    printf("\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) {
            printf("%d ", arr[i][j]);
        }
    }
}