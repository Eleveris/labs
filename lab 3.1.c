#define N 3
#define M 3

#include <stdio.h>


void inputFunc(int* arr[N][M],int n,int m, FILE* input);
void outputFunc(int* arr[N][M],int n, int m, FILE* output);


int main ()
{
    FILE *input  = fopen("input.txt",  "r");
    FILE *output = fopen("output.txt", "w+");
    if (input == NULL) return 2;

    int arr1[N][M],arr2[N][M];
    int swap;
    inputFunc(&arr1 , N , M , input);

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

    outputFunc(&arr2 , N , M , output);
    fclose(input);
    fclose(output);

    return 0;

}

void inputFunc (int *arr[N][M], int n,int m, FILE *input)
{
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) {
            fscanf(input, "%d", &arr[i][j]);
        }
    }
    return;
}


void outputFunc (int *arr[N][M], int n, int m, FILE* output)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fprintf(output, "%d " , arr[i][j]);
        }
        fprintf(output , "\n");
    }
    return;
}
