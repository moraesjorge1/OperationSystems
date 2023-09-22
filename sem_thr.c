/*
Nome: 

Com thread
Valor 68 encontrado na posicao 484
Valor 68 encontrado na posicao 577
Valor 68 encontrado na posicao 652
Tempo gasto 0.000153 segundos

Sem thread
Valor 68 encontrado na posicao 484
Valor 68 encontrado na posicao 577
Valor 68 encontrado na posicao 652
Tempo gasto 0.000073 segundos

A sem thread, é uma chamada de uma função de busca linear básica, sem dividir o vetor na metade
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define TAM 1000000

int array[TAM];



void buscaLinear(int begin, int final, int valor) {
    for (int i = begin; i < final; i++) {
        if (array[i] == valor) {
            printf("Valor %d encontrado na posicao %d\n", valor, i);
        }
    }
}



int main() {



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


    clock_t start = clock();
    buscaLinear(0, TAM, n);
    clock_t end = clock();


    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
                printf("Tempo gasto %f segundos\n", time_taken);

    return 0;
}




               
                  
