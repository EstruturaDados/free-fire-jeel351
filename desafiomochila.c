#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================================
// 1. DEFINIÇÃO DAS STRUCTS
// ==========================================

// Item (Carga útil de dados)
typedef struct {
    char nome[30];
    char tipo[20]; // ex: "Pocao", "Arma", "Chave"
    int quantidade;
} Item;

// Nó (Para a Lista Encadeada)
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Constante para tamanho máximo do vetor
#define MAX_VETOR 50

// ==========================================
// 2. FUNÇÕES - MOCHILA COM VETOR
// ==========================================

// Variáveis globais para controlar o vetor
Item mochilaVetor[MAX_VETOR];
int qtdVetor = 0; // Quantidade atual de itens no vetor

void inserirItemVetor() {
    if (qtdVetor >= MAX_VETOR) {
        printf("[Erro] Mochila (Vetor) cheia!\n");
        return;
    }
    
    Item novo;
    printf("Nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    
    mochilaVetor[qtdVetor] = novo;
    qtdVetor++;
    printf("[Sucesso] Item adicionado ao vetor.\n");
}

void removerItemVetor(char* nomeAlvo) {
    int i, j;
    int encontrou = 0;
    
    for (i = 0; i < qtdVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeAlvo) == 0) {
            // Remove deslocando os itens à esquerda (Shift Left)
            for (j = i; j < qtdVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j+1];
            }
            qtdVetor--;
            encontrou = 1;
            printf("[Sucesso] Item '%s' removido do vetor.\n", nomeAlvo);
            break; // Remove apenas o primeiro encontrado
        }
    }
    if (!encontrou) printf("[Aviso] Item nao encontrado no vetor.\n");
}

void listarVetor() {
    printf("\n--- MOCHILA (VETOR) [%d/%d] ---\n", qtdVetor, MAX_VETOR);
    for (int i = 0; i < qtdVetor; i++) {
        printf("[%d] %s (Tipo: %s | Qtd: %d)\n", 
               i, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

// Algoritmo de Ordenação (Bubble Sort)
void ordenarVetor() {
    Item temp;
    for (int i = 0; i < qtdVetor - 1; i++) {
        for (int j = 0; j < qtdVetor - i - 1; j++) {
            // Se o atual for "maior" alfabeticamente que o próximo, troca
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
        }
    }
    printf("[Sucesso] Vetor ordenado por nome.\n");
}

void buscarSequencialVetor(char* nomeAlvo) {
    int comparacoes = 0;
    int encontrou = 0;
    
    printf("\n--- Busca Sequencial (Vetor) ---\n");
    for (int i = 0; i < qtdVetor; i++) {
        comparacoes++;
        if (strcmp(mochilaVetor[i].nome, nomeAlvo) == 0) {
            printf("Item ENCONTRADO no indice %d: %s\n", i, mochilaVetor[i].nome);
            encontrou = 1;
            break;
        }
    }
    if (!encontrou) printf("Item nao encontrado.\n");
    printf("Numero de comparacoes realizadas: %d\n", comparacoes);
}

void buscarBinariaVetor(char* nomeAlvo) {
    int inicio = 0;
    int fim = qtdVetor - 1;
    int meio;
    int comparacoes = 0;
    int encontrou = 0;

    printf("\n--- Busca Binaria (Vetor) ---\n");
    // Aviso importante: Busca binária só funciona se estiver ordenado
    // Assumimos que o usuário ordenou antes.
    
    while (inicio <= fim) {
        comparacoes++;
        meio = (inicio + fim) / 2;
        int resultado = strcmp(mochilaVetor[meio].nome, nomeAlvo);
        
        if (resultado == 0) {
            printf("Item ENCONTRADO no indice %d: %s\n", meio, mochilaVetor[meio].nome);
            encontrou = 1;
            break;
        } else if (resultado < 0) {
            inicio = meio + 1; // Busca na metade direita
        } else {
            fim = meio - 1;    // Busca na metade esquerda
        }
    }
    
    if (!encontrou) printf("Item nao encontrado.\n");
    printf("Numero de comparacoes realizadas: %d\n", comparacoes);
}

// ==========================================
// 3. FUNÇÕES - MOCHILA COM LISTA ENCADEADA
// ==========================================

// Ponteiro global para o início da lista
No* cabecaLista = NULL;

void inserirItemLista() {
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("[Erro] Memoria insuficiente!\n");
        return;
    }
    
    printf("Nome do item: ");
    scanf(" %[^\n]", novoNo->dados.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novoNo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    
    // Inserção no início (mais rápido e simples O(1))
    novoNo->proximo = cabecaLista;
    cabecaLista = novoNo;
    
    printf("[Sucesso] Item adicionado a lista encadeada.\n");
}

void removerItemLista(char* nomeAlvo) {
    No* atual = cabecaLista;
    No* anterior = NULL;
    
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeAlvo) == 0) {
            // Se for o primeiro da lista
            if (anterior == NULL) {
                cabecaLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            
            free(atual); // Libera memória
            printf("[Sucesso] Item '%s' removido da lista.\n", nomeAlvo);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("[Aviso] Item nao encontrado na lista.\n");
}

void listarLista() {
    No* atual = cabecaLista;
    printf("\n--- MOCHILA (LISTA ENCADEADA) ---\n");
    if (atual == NULL) {
        printf("Mochila vazia.\n");
        return;
    }
    
    while (atual != NULL) {
        printf("-> %s (Tipo: %s | Qtd: %d)\n", 
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("-> NULL\n");
}

void buscarSequencialLista(char* nomeAlvo) {
    int comparacoes = 0;
    int encontrou = 0;
    No* atual = cabecaLista;
    
    printf("\n--- Busca Sequencial (Lista) ---\n");
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nomeAlvo) == 0) {
            printf("Item ENCONTRADO: %s\n", atual->dados.nome);
            encontrou = 1;
            break;
        }
        atual = atual->proximo;
    }
    
    if (!encontrou) printf("Item nao encontrado.\n");
    printf("Numero de comparacoes realizadas: %d\n", comparacoes);
}

// ==========================================
// 4. MAIN E MENU
// ==========================================

int main() {
    int opcao;
    char nomeBusca[30];

    do {
        printf("\n=== GERENCIADOR DE MOCHILA (VETOR vs LISTA) ===\n");
        printf("1. [VETOR] Inserir Item\n");
        printf("2. [VETOR] Listar Itens\n");
        printf("3. [VETOR] Remover Item\n");
        printf("4. [VETOR] Ordenar (Bubble Sort)\n");
        printf("5. [VETOR] Busca Sequencial\n");
        printf("6. [VETOR] Busca Binaria (Requer Ordenacao)\n");
        printf("---------------------------------------------\n");
        printf("7. [LISTA] Inserir Item\n");
        printf("8. [LISTA] Listar Itens\n");
        printf("9. [LISTA] Remover Item\n");
        printf("10.[LISTA] Busca Sequencial\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: inserirItemVetor(); break;
            case 2: listarVetor(); break;
            case 3: 
                printf("Nome para remover: ");
                scanf(" %[^\n]", nomeBusca);
                removerItemVetor(nomeBusca);
                break;
            case 4: ordenarVetor(); break;
            case 5:
                printf("Nome para buscar (Sequencial): ");
                scanf(" %[^\n]", nomeBusca);
                buscarSequencialVetor(nomeBusca);
                break;
            case 6:
                printf("Nome para buscar (Binaria): ");
                scanf(" %[^\n]", nomeBusca);
                buscarBinariaVetor(nomeBusca);
                break;
            
            case 7: inserirItemLista(); break;
            case 8: listarLista(); break;
            case 9:
                printf("Nome para remover: ");
                scanf(" %[^\n]", nomeBusca);
                removerItemLista(nomeBusca);
                break;
            case 10:
                printf("Nome para buscar (Sequencial): ");
                scanf(" %[^\n]", nomeBusca);
                buscarSequencialLista(nomeBusca);
                break;

            case 0: printf("Saindo do sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    // Limpeza de memória da lista antes de sair (Boa prática)
    No* atual = cabecaLista;
    No* temp;
    while (atual != NULL) {
        temp = atual->proximo;
        free(atual);
        atual = temp;
    }

    return 0;
}