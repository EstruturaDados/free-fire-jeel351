#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// 1. Definição da Struct (Requisito: Criação de structs)
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Protótipos das funções
void bubbleSortNome(Componente arr[], int n, long *comparacoes);
void insertionSortTipo(Componente arr[], int n, long *comparacoes);
void selectionSortPrioridade(Componente arr[], int n, long *comparacoes);
int buscaBinariaPorNome(Componente arr[], int n, char chave[]);
void mostrarComponentes(Componente arr[], int n);
void lerString(char *buffer, int tamanho);

// ============================================================================
// FUNÇÕES DE ORDENAÇÃO (Requisito: Opções de ordenação e Contagem)
// ============================================================================

// Ordena por NOME usando BUBBLE SORT
void bubbleSortNome(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    int i, j;
    Componente temp;
    
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            (*comparacoes)++; // Contabiliza a comparação
            if (strcmp(arr[j].nome, arr[j+1].nome) > 0) {
                // Troca
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Ordena por TIPO usando INSERTION SORT
void insertionSortTipo(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    int i, j;
    Componente eleito;
    
    for (i = 1; i < n; i++) {
        eleito = arr[i];
        j = i - 1;
        
        // O loop do insertion realiza comparações enquanto busca a posição
        while (j >= 0) {
            (*comparacoes)++; // Contabiliza comparação do while
            if (strcmp(arr[j].tipo, eleito.tipo) > 0) {
                arr[j + 1] = arr[j];
                j = j - 1;
            } else {
                break; // Parou de mover, sai do while
            }
        }
        arr[j + 1] = eleito;
    }
}

// Ordena por PRIORIDADE usando SELECTION SORT
void selectionSortPrioridade(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    int i, j, min_idx;
    Componente temp;
    
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            (*comparacoes)++; // Contabiliza a comparação
            if (arr[j].prioridade < arr[min_idx].prioridade) {
                min_idx = j;
            }
        }
        // Troca se encontrou um menor
        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

// ============================================================================
// BUSCA BINÁRIA (Requisito: Aplicável após ordenação por nome)
// ============================================================================

int buscaBinariaPorNome(Componente arr[], int n, char chave[]) {
    int inicio = 0;
    int fim = n - 1;
    int meio;
    
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int resultado = strcmp(arr[meio].nome, chave);
        
        if (resultado == 0) {
            return meio; // Encontrou
        } else if (resultado < 0) {
            inicio = meio + 1; // Está na metade direita
        } else {
            fim = meio - 1; // Está na metade esquerda
        }
    }
    return -1; // Não encontrou
}

// ============================================================================
// FUNÇÕES AUXILIARES (Requisito: Interface e I/O)
// ============================================================================

// Função segura para ler strings e remover o \n do fgets
void lerString(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

void mostrarComponentes(Componente arr[], int n) {
    printf("\n%-30s | %-20s | %s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-30s | %-20s | %d\n", arr[i].nome, arr[i].tipo, arr[i].prioridade);
    }
    printf("-------------------------------------------------------------------\n");
}

// Wrapper para medir tempo de execução
// Recebe um ponteiro para a função de ordenação
void executarMedicao(void (*funcaoOrdenacao)(Componente[], int, long*), Componente arr[], int n, char* nomeAlgoritmo) {
    long comparacoes = 0;
    clock_t inicio, fim;
    double tempo_gasto;

    inicio = clock();
    funcaoOrdenacao(arr, n, &comparacoes);
    fim = clock();

    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n[RESULTADOS - %s]\n", nomeAlgoritmo);
    printf("Tempo de execucao: %f segundos\n", tempo_gasto);
    printf("Comparacoes realizadas: %ld\n", comparacoes);
    mostrarComponentes(arr, n);
}

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================

int main() {
    Componente torre[MAX_COMPONENTES];
    int qtd = 0;
    int opcao;
    char busca[30];
    int indiceBusca;
    int ordenadoPorNome = 0; // Flag de segurança

    do {
        printf("\n=== SISTEMA DE MONTAGEM DE TORRE ===\n");
        printf("1. Cadastrar Componente\n");
        printf("2. Ordenar por NOME (Bubble Sort)\n");
        printf("3. Ordenar por TIPO (Insertion Sort)\n");
        printf("4. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5. Buscar Componente (Binaria - Requer Opcao 2)\n");
        printf("6. Listar Componentes\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do teclado

        switch(opcao) {
            case 1:
                if (qtd < MAX_COMPONENTES) {
                    printf("\n--- Novo Componente ---\n");
                    printf("Nome: ");
                    lerString(torre[qtd].nome, 30);
                    printf("Tipo: ");
                    lerString(torre[qtd].tipo, 20);
                    printf("Prioridade (1-10): ");
                    scanf("%d", &torre[qtd].prioridade);
                    qtd++;
                    ordenadoPorNome = 0; // Vetor foi alterado, perde a ordenação
                } else {
                    printf("Limite de componentes atingido!\n");
                }
                break;

            case 2:
                if (qtd > 0) {
                    executarMedicao(bubbleSortNome, torre, qtd, "Bubble Sort (Nome)");
                    ordenadoPorNome = 1; // Agora está seguro para busca binária
                } else printf("Nenhum componente cadastrado.\n");
                break;

            case 3:
                if (qtd > 0) {
                    executarMedicao(insertionSortTipo, torre, qtd, "Insertion Sort (Tipo)");
                    ordenadoPorNome = 0;
                } else printf("Nenhum componente cadastrado.\n");
                break;

            case 4:
                if (qtd > 0) {
                    executarMedicao(selectionSortPrioridade, torre, qtd, "Selection Sort (Prioridade)");
                    ordenadoPorNome = 0;
                } else printf("Nenhum componente cadastrado.\n");
                break;

            case 5:
                if (!ordenadoPorNome) {
                    printf("\n[ERRO] A Busca Binaria exige que a lista esteja ordenada por NOME.\n");
                    printf("Execute a opcao 2 primeiro.\n");
                } else {
                    printf("Digite o nome do componente-chave: ");
                    lerString(busca, 30);
                    indiceBusca = buscaBinariaPorNome(torre, qtd, busca);
                    
                    if (indiceBusca != -1) {
                        printf("\n[SUCESSO] Componente-chave encontrado na posicao %d!\n", indiceBusca);
                        printf("Dados: %s | %s | Prioridade: %d\n", 
                               torre[indiceBusca].nome, 
                               torre[indiceBusca].tipo, 
                               torre[indiceBusca].prioridade);
                    } else {
                        printf("\n[FALHA] Componente nao encontrado.\n");
                    }
                }
                break;

            case 6:
                mostrarComponentes(torre, qtd);
                break;

            case 0:
                printf("Encerrando sistema...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}