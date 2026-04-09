# Simulador de Escalonamento de CPU

Este projeto implementa dois simuladores de escalonamento de processos para sistemas de tempo real: **Rate Monotonic (rate)** e **Earliest Deadline First (edf)**. O programa lê um arquivo de configuração contendo as tarefas periódicas e gera um log detalhado de execução, perdas de prazo (*deadlines* perdidos) e mortes de processos em um arquivo de saída formatado.

## 💻 Sistema Operacional de Implementação e Suporte

Este projeto foi desenvolvido e primariamente testado no sistema operacional **Ubuntu (Linux)**, executado através do **WSL 2 (Windows Subsystem for Linux)**. 

O código foi escrito em C padrão e é totalmente compatível e executável nativamente em ambientes **Linux, Unix e macOS**.

## 📂 Descrição dos Arquivos Utilizados

O projeto adota uma arquitetura modular, separando os códigos-fonte na pasta `source` e os binários gerados na pasta `objects`.

* **`source/tasks.h`**: Arquivo de cabeçalho. Define as constantes do sistema, a estrutura de dados `Task` (com seus atributos estáticos e dinâmicos para a simulação) e declara as variáveis globais.
* **`source/tasks.c`**: Responsável pela manipulação de I/O de entrada. Contém a lógica de leitura do arquivo `.txt`, validação de integridade e alocação das tarefas na memória.
* **`source/main.c`**: Arquivo principal para gerar o executável `rate`. Implementa a máquina de estados e o laço de tempo do algoritmo **Rate Monotonic** (prioridade estática baseada no menor período), além de gerar o arquivo de saída `rate_chccp.out`.
* **`source/edf.c`**: Arquivo principal para gerar o executável `edf`. Implementa o algoritmo **Earliest Deadline First** (prioridade dinâmica baseada no deadline mais próximo), gerando o arquivo de saída `edf_chccp.out`.
* **`makefile`**: Script para automação da compilação. Gerencia as dependências entre os arquivos `.c` e `.h` e gera os executáveis na raiz do projeto.

## ⚙️ Como Compilar

Certifique-se de ter o compilador `gcc` e a ferramenta `make` instalados no seu sistema. Na raiz do projeto, utilize os seguintes comandos:

**Para compilar ambos os algoritmos (rate e edf) simultaneamente:**
```
make
```

## Para compilar os algoritmos individualmente:
```
make rate
   ou
make edf
```

## Para limpar os arquivos objetos e executáveis antigos:

```
make clean
```

# ▶️ Como Executar

A execução deve ser feita via linha de comando, passando o arquivo de texto com a lista das tarefas como argumento (Obs: input.txt é um arquivo de exemplo)

## Para executar o Rate Monotonic:

```
./rate input.txt
```

## Para executar o Earliest Deadline First:

```
./edf input.txt
```

# 🧪 Como Testar o Programa

1 - Crie um arquivo .txt na raiz do projeto com a seguinte formatação (O primeiro número é o tempo total, seguido pelas tarefas com Nome, Período e Tempo de CPU):

## Exemplo:
```
165
T1 50 25
T2 80 35
```

2 - Compile o projeto executando `make`.

3 - Rode o comando `./rate input.txt`.

4 - O programa não exibirá nada no terminal, mas criará um arquivo chamado `rate_chccp.out` na mesma pasta.

5 - Abra o arquivo .out gerado para validar se a simulação registrou corretamente os estados de execução (F - Finalizou, H - Pausou, L - Perdeu Deadline, K - Morta).
