#ifndef TASKS_H
#define TASKS_H

#define MAX_TASKS 10
#define MAX_NAME_LEN 5

typedef struct Task {
    char nome[MAX_NAME_LEN];
    int periodo;
    int cpu_burst;

    int tempo_restante;  
    int proximo_deadline;   

    int concluidas;
    int perdidas;
    int mortas;
} Task;

extern int tempo_total;
extern Task tasks[MAX_TASKS];
extern int total_tarefas;

void ler_arquivo(const char *filename);

#endif