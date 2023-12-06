
/*  MODELO DE TAREFAS : 
        Periódicas dependentes
        Deadline = Periodo
        Tempo de Computação Constante
        Tempo de chaveamento nulo
*/

#include<stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    char nome[20];
    int priority; //Prioridade
    int J; // Release Jitter
    int C; // Tempo de Computação
    int P; // Período
    int D; // Deadline
} Task;

void executeTask(Task task) {
    printf("Executando tarefa: %s com prioridade %d\n", task.nome, task.priority);
}

int trocaDeContexto(void) {
    struct timespec start, end;
    double time_taken;

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Troca de contexto forçada, por exemplo, com sleep ou yield
    sleep(1);

    clock_gettime(CLOCK_MONOTONIC, &end);

    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    return time_taken;
}

int schedulingTest (Task tasks)
{
    int Somatorio = 0;
    int m = 4; // Número de Processadores a serem utilizados
    for(int i = 0; i < MAX_TASKS; i++)
    {
        float U[i] = tasks.C[i] / tasks.P[i];
    }

    for (int j = 0; j < MAX_TASKS; j++)
    {
        Somatorio = Somatorio + U[i];    
    }

    if (m >= Somatorio)
    return 0;

    else return 1;
}

int main()
{
    Task tasks[MAX_TASKS] = {
        {"Task 1", 0, 0, 20, 100, 100};
        {"Task 2", 0, 0, 40, 150, 150};
    }

    printf("%d", time_taken);

}