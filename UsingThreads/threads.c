/*                                                          .............OUTPUTS DO EXPERIMENTO.............
Quantas threads deseja usar? 2

USANDO 2 threads:
Valor 64 encontrado na posicao 509261
Tempo gasto 0.000190 segundos

SEM USO DE THREADS
Valor 64 encontrado na posicao 509261
Tempo gasto 0.001782 segundos

......................................................................

Quantas threads deseja usar? 1

USANDO 1 threads:
Valor 64 encontrado na posicao 509261
Tempo gasto 0.000070 segundos

SEM USO DE THREADS
Valor 64 encontrado na posicao 509261
Tempo gasto 0.001815 segundos

......................................................................

Quantas threads deseja usar? 4  A máquina possui 4 cores, fiz com esse valor para saber se ia melhorar o desempenho

USANDO 4 threads:
Valor 64 encontrado na posicao 509261
Tempo gasto 0.000200 segundos

SEM USO DE THREADS
Valor 64 encontrado na posicao 509261
Tempo gasto 0.001891 segundos
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define TAM 1000000

int array[TAM];

typedef struct {
    int begin;
    int final;
    int valor;
} BuscaLinearArgs;

void buscaLinear(int begin, int final, int valor) {
    for (int i = begin; i < final; i++) {
        if (array[i] == valor) {
            printf("Valor %d encontrado na posicao %d\n", valor, i);
        }
    }
}

void *buscaLinearWrapper(void *args) {
    BuscaLinearArgs *params = (BuscaLinearArgs *)args; //type-casting
    buscaLinear(params->begin, params->final, params->valor); //Acessando os valores da struct de argumentos 
    return NULL;
}

int main() {
    int n = 64;
    int i = 0;
    int num_t;
    
    printf("Quantas threads deseja usar? ");
    scanf("%d", &num_t);

    pthread_t tid[num_t];
    BuscaLinearArgs args[num_t];
    int div = TAM / num_t;


    // Leitura dos números do arquivo
    FILE *file = fopen("arquivo.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    while (fscanf(file, "%d", &array[i]) != EOF && i < TAM) { // Atribui os valores do arquivo desejado dentro do vetor
        i++;
    }
    fclose(file);

    for (int k = 0; k < num_t; k++) //Recebe os argumentos 
{
    args[k].begin = k * div; 
    /*  
    Se for a última thread, verifica até o final do array.
    É para caso o array não seja divisível pelo número de threads, daí na ultima Késima thread pegamos todos os elementos restantes
    */ 
    if (k == num_t - 1)
        args[k].final = TAM;
    else
        args[k].final = (k+1) * div;
        
    args[k].valor = n;
}

    printf("\nUSANDO %d threads:\n", num_t);
    
    clock_t start = clock();
    for (int j = 0; j < num_t; j++) // Create 
    {
        pthread_create(&tid[j], NULL, buscaLinearWrapper, &args[j]); 
    }

    for (int l = 0; l < num_t; l++) // join para rodarem em paralelo
    {
        pthread_join(tid[l], NULL);
    }
    clock_t end = clock();

    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Tempo gasto %f segundos\n", time_taken);

    printf("\nSEM USO DE THREADS\n");

    clock_t start2 = clock();
    buscaLinear(0, TAM, n);
    clock_t end2 = clock();

    double time_taken2 = ((double)end2 - start2) / CLOCKS_PER_SEC;
    printf("Tempo gasto %f segundos\n", time_taken2);

    return 0;
}


               
                  
