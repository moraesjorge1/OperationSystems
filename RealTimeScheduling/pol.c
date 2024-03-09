
//Algoritmo de escalonamento de tarefas de tempo real. Ordenação e implementação de teste de escalonabilidade



#include <stdio.h>
#include <stdbool.h>
#include <math.h>


//Sempre que houver um servidor, se o número de tarefas é n, então n = n + 1
#define MAX_TASKS 11
#define AP_MAX 4

typedef struct {
    int id;
    int Ci; // Tempo de Computação
    int Ti; // Período
    int Di; // Deadline
    int priority; // Prioridade
    bool isServer;
} Task;

typedef struct {
    int id;
    int Ci;
    int Di; // Deadline
    int priority; // Prioridade
    bool isReady; // Verifica status de execução     
} AperiodicTask;

typedef struct {
    int id;
    int Ci;
    int Ti;
    int Di;
    int priority;
} Server;

void criaServer(AperiodicTask *aperiodicTasks, Server *server) {
    int SC = 0;
    int SD = 0;

    for (int i = 0; i < AP_MAX; i++) {
        if (aperiodicTasks[i].isReady) {
            SC += aperiodicTasks[i].Ci;
            SD += aperiodicTasks[i].Di;
        }
    }

    server->Ci = SC;
    server->Di = SD;
    server->id = 19;
}

void encontraPeriodo(Task *tasks, Server *server)
{
    int maior = 0;
    //Acha maior período nas tasks
    for (int i = 0; i < MAX_TASKS; i++)
    {
        if (tasks[i].Ti > maior)
        maior = tasks[i].Ti;
    }

    server->Ti = maior / 4;
    int periodo_minimo = 5; // Definido conforme a necessidade do sistema
    if (server->Ti < periodo_minimo) {
        server->Ti = periodo_minimo;
    }
}

int schedulingTest(Task *tasks, int numTasks) {
    float U = 0;
    for (int i = 0; i < numTasks; i++) {
        U += (float) tasks[i].Ci / tasks[i].Di;
    }

    double rhs = numTasks * (pow(2, 1.0 / numTasks) - 1);

    if (U <= rhs)
        return 1;
    else 
        return -1;
}

int definePrioridade(Task *tasks, int numTasks) {
    // Ordenar as tarefas por deadline usando bubble sort
    for (int i = 0; i < numTasks - 1; i++) {
        for (int j = 0; j < numTasks - i - 1; j++) {
            if (tasks[j].Di > tasks[j + 1].Di) {
                Task aux = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = aux;
            }
        }
    }

    // Definir prioridades
    for (int i = 0; i < numTasks; i++) {
        tasks[i].priority = i + 1;
    }

    return 0;
}

int main() {
    Task tasks[MAX_TASKS] = {
        
    };

    AperiodicTask aperiodicTasks[AP_MAX] = {
        
    };

    Server server;

    if (AP_MAX >= 1)
    {
        criaServer(aperiodicTasks, &server);
        encontraPeriodo(tasks, &server);
    }
        tasks[MAX_TASKS - 1].id = server.id;
        tasks[MAX_TASKS - 1].Ci = server.Ci;
        tasks[MAX_TASKS - 1].Ti = server.Ti;
        tasks[MAX_TASKS - 1].Di = server.Di;
        tasks[MAX_TASKS - 1].priority = 0; // Será definido posteriormente
        tasks[MAX_TASKS - 1].isServer = true;


        if (schedulingTest(tasks) == 1){
            definePrioridade(tasks, MAX_TASKS);

        // Impressão para verificação
        
            for (int i = 0; i < MAX_TASKS; i++) {
                printf("Task %d: Ci: %d, Ti: %d, Di: %d, Priority: %d\n", tasks[i].id, tasks[i].Ci, tasks[i].Ti, tasks[i].Di, tasks[i].priority);
            }
            for (int i = 0; i < AP_MAX; i++) {
               printf("Aperiodic Task %d: Ci: %d, Di: %d, Priority: %d\n", aperiodicTasks[i].id, aperiodicTasks[i].Ci, aperiodicTasks[i].Di, aperiodicTasks[i].priority);
            }
        }
        else printf("A instancia nao passou no teste de escalonabilidade");
    

    return 0;
}
