#include <stdio.h>
#include <stdlib.h>

int* inputFunc(int* n,int* m, FILE* input);
void outputFunc(int* values,int n, int m, FILE* output);

int main() {
    int* values;
    int swap;
    int n=0, m=0;
    FILE *input  = fopen("input.txt",  "r");
    FILE *output = fopen("output.txt", "w+");

    values=inputFunc(&n, &m , input);

    for (int i = 0; i < n*m; i++)
    {
        for (int j = 0; j < n*m-1; j++)
        {
            if (values[j]>values[j+1])
            {
                swap=values[j];
                values[j]=values[j+1];
                values[j+1]=swap;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if ((i%2))
        for (int j = 0; j < (m/2); j++)
        {
            swap=values[i*m+j];
            values[i*m+j]=values[i*m+(m-1-j)];
            values[i*m+(m-1-j)]=swap;
        }
    }

    outputFunc(values,n,m,output);
	
	fclose(input);
	fclose(output);
	free(values);
    return 0;
}

int* inputFunc(int* n,int* m, FILE* input)
{
    int* values=NULL;
    int i=0,scan;
    while (!feof(input))
    {
        fscanf(input, "%d", &scan);
        if ((*n) == 0) (*m)++;
        if (fgetc(input) == '\n') (*n)++;
        values=realloc(values, sizeof(int)*(i+1));
        values[i]=scan;
        i++;
    }
    (*n)=i/(*m);
    return values;
}

void outputFunc(int* values,int n, int m, FILE* output)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            fprintf(output,"%d ", values[i*m+j]);
        }
        fprintf(output, "\n");
    }
}
