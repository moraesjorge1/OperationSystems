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
    BuscaLinearArgs *params = (BuscaLinearArgs *)args;
    buscaLinear(params->begin, params->final, params->valor);
    return NULL;
}

int main() {
    pthread_t tid[2];
    BuscaLinearArgs args[2];

    // Leitura dos números do arquivo
    FILE *file = fopen("arquivo.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int i = 0;
    while (fscanf(file, "%d", &array[i]) != EOF && i < TAM) {
        i++;
    }
    fclose(file);

    int n = 68;

    args[0].begin = 0;  
    args[0].final = TAM / 2;  
    args[0].valor = n; 
    clock_t start = clock();
    pthread_create(&tid[0], NULL, buscaLinearWrapper, &args[0]);

    args[1].begin = TAM / 2;
    args[1].final = TAM;
    args[1].valor = n;
    pthread_create(&tid[1], NULL, buscaLinearWrapper, &args[1]);
    clock_t end = clock();

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Tempo gasto %f segundos\n", time_taken);

    return 0;
}

               
                  
