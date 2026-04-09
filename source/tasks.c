#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"

int tempo_total = 0;
Task tasks[MAX_TASKS];
int total_tarefas = 0;

void ler_arquivo(const char *filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        fprintf(stderr, "Erro: O arquivo de entrada '%s' nao existe ou nao pode ser aberto.\n", filename);
        exit(1); 
    }
    
    if (fscanf(file, "%d", &tempo_total) != 1) {
        fprintf(stderr, "Erro: Falha ao ler o tempo total do arquivo.\n");
        fclose(file);
        exit(1);
    }

    while (fscanf(file, "%s %d %d", 
                  tasks[total_tarefas].nome, 
                  &tasks[total_tarefas].periodo, 
                  &tasks[total_tarefas].cpu_burst) == 3) {
        total_tarefas++;
        if (total_tarefas >= MAX_TASKS) {
            break; 
        }
    }

    fclose(file);
}