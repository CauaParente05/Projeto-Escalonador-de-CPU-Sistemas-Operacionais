#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Erro: Numero incorreto de argumentos.\n");
        return 1;
    }
    
    ler_arquivo(argv[1]); 

    for(int i = 0; i < total_tarefas; i++) {
        tasks[i].tempo_restante = tasks[i].cpu_burst;
        tasks[i].proximo_deadline = tasks[i].periodo;
        tasks[i].concluidas = 0;
        tasks[i].perdidas = 0;
        tasks[i].mortas = 0;
    }

    FILE *arquivo_saida = fopen("rate_chccp.out", "w");
    if (arquivo_saida == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo de saida.\n");
        return 1;
    }

    fprintf(arquivo_saida, "\nEXECUTION BY RATE\n\n");

    int id_executando = -1; 
    int tempo_acumulado = 0;

    for (int t = 0; t < tempo_total; t++) {

        if (id_executando != -1 && tasks[id_executando].tempo_restante == 0) {
            fprintf(arquivo_saida, "[%s] for %d units - F\n", tasks[id_executando].nome, tempo_acumulado);
            tasks[id_executando].concluidas++;
            id_executando = -1;
            tempo_acumulado = 0;
        }

        if (t > 0) {
            for (int i = 0; i < total_tarefas; i++) {
                if (t % tasks[i].periodo == 0) {
                    if (tasks[i].tempo_restante > 0) {
                        tasks[i].perdidas++; 
                        if (id_executando == i) {
                            fprintf(arquivo_saida, "[%s] for %d units - L\n", tasks[i].nome, tempo_acumulado);
                            id_executando = -1;
                            tempo_acumulado = 0;
                        }
                    }
                    tasks[i].tempo_restante = tasks[i].cpu_burst; 
                }
            }
        }

        int proxima_tarefa = -1;
        int menor_periodo = 999999;

        for (int i = 0; i < total_tarefas; i++) {
            if (tasks[i].tempo_restante > 0 && tasks[i].periodo < menor_periodo) {
                proxima_tarefa = i;
                menor_periodo = tasks[i].periodo;
            }
        }

        if (proxima_tarefa != id_executando) {
            if (tempo_acumulado > 0) {
                if (id_executando == -1) {
                    fprintf(arquivo_saida,"idle for %d units\n", tempo_acumulado);
                } else {
                    fprintf(arquivo_saida,"[%s] for %d units - H\n", tasks[id_executando].nome, tempo_acumulado);
                }
            }
            id_executando = proxima_tarefa;
            tempo_acumulado = 0;
        }

        if (id_executando != -1) {
            tasks[id_executando].tempo_restante--;
        }
        tempo_acumulado++;
    }

    if (tempo_acumulado > 0) {
        if (id_executando == -1) {
            fprintf(arquivo_saida,"idle for %d units\n", tempo_acumulado);
        } else {
            if (tasks[id_executando].tempo_restante == 0) {
                fprintf(arquivo_saida,"[%s] for %d units - F\n", tasks[id_executando].nome, tempo_acumulado);
                tasks[id_executando].concluidas++;
            } else {
                fprintf(arquivo_saida,"[%s] for %d units - K\n", tasks[id_executando].nome, tempo_acumulado);
                tasks[id_executando].mortas++;
            }
        }
    }

    for(int i = 0; i < total_tarefas; i++) {
        if (i != id_executando && tasks[i].tempo_restante > 0 && tasks[i].tempo_restante < tasks[i].cpu_burst) {
            tasks[i].mortas++;
        }
    }

    fprintf(arquivo_saida, "\nLOST DEADLINES\n");
    for(int i=0; i < total_tarefas; i++) fprintf(arquivo_saida,"[%s] %d\n", tasks[i].nome, tasks[i].perdidas);
    
    fprintf(arquivo_saida,"\nEXECUCOES COMPLETAS\n");
    for(int i=0; i < total_tarefas; i++) fprintf(arquivo_saida,"[%s] %d\n", tasks[i].nome, tasks[i].concluidas);
    
    fprintf(arquivo_saida,"\nMORTAS\n");
    for(int i=0; i < total_tarefas; i++) fprintf(arquivo_saida,"[%s] %d\n", tasks[i].nome, tasks[i].mortas);

    fclose(arquivo_saida);

    return 0;
}