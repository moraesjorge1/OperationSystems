#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

#define MESSAGE "Ola Usuario\n"

void cmd_hello(char command[256]);
void cmd_hello2(char command[256]);
void cmd_hello3(char command[256]);
void cmd_create (char command[256]);
void cmd_open (char command[256]);
void shell (char command[256]);

typedef struct {
    const char* name;
    void (*func)(char[]);
} Command;

Command commands[] = {
    {"fork", shell},
    {"open", cmd_open},
    {"create", cmd_create},
    {"hello3", cmd_hello3},
    {"hello", cmd_hello},
    {"hello2", cmd_hello2},
    {NULL, NULL}  // final
};

int main() {
    char command[256];

    while(1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = 0;

        for (Command* cmd = commands; cmd->name != NULL; cmd++) {
            if (strcmp(command, cmd->name) == 0) {
                clock_t start = clock(); 
                cmd->func(command);
                clock_t end = clock();   
                
                double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
                printf("Tempo gasto na função '%s': %f segundos\n", cmd->name, time_taken);

                break;
            }
        }
    }

    return 0;
}

void cmd_hello(char command[256]) 
{
    printf(MESSAGE);
}

void cmd_hello2(char command[256]) 
{
    write(STDOUT_FILENO, MESSAGE, strlen(MESSAGE));
}

void cmd_hello3(char command[256])
{
    syscall(SYS_write, STDOUT_FILENO, MESSAGE, strlen(MESSAGE));
}

void cmd_create (char command[256])
{
    char name[100];
    fgets(name, sizeof(name), stdin);
    int file = creat(name, 0744);
    if (file < 0)
   {
      fprintf (stderr, "Erro : %s\n", strerror(errno));
      exit(errno); 
   }
   printf ("Arquivo criado\n");
}
void cmd_open (char command[256])
{
    char name[100];
    char cont[1000];
    printf("Digite o nome do arquivo: ");
    fgets(name, sizeof(name), stdin);
    int file = open(name, O_RDWR | O_APPEND, 0744);
     if (file < 0)
   {
      fprintf (stderr, "Erro : %s\n", strerror(errno));
   }
   else
   {
      printf ("Arquivo 1 aberto\n");
   }
   
}
void shell (char command[256])
{
    pid_t pid = fork();
    if (pid < 0) //erro
    {  
        perror("Erro no fork");
        return;
    }
    
    if (pid == 0) //Processo filho
    {
        printf("processo de ID %d, filho do pai de ID %d", getpid(), getppid());
    }

}