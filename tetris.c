#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// ---------------------------
// Estrutura da peça
// ---------------------------
typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;     // Identificador único
} Peca;

// ---------------------------
// Estrutura da fila circular
// ---------------------------
typedef struct {
    Peca pecas[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// ---------------------------
// Estrutura da pilha
// ---------------------------
typedef struct {
    Peca pecas[TAM_PILHA];
    int topo;
} Pilha;

// ---------------------------
// Protótipos das funções
// ---------------------------
void inicializarFila(Fila *fila);
void inicializarPilha(Pilha *pilha);
int filaCheia(Fila *fila);
int filaVazia(Fila *fila);
int pilhaCheia(Pilha *pilha);
int pilhaVazia(Pilha *pilha);
Peca gerarPeca(int id);
void inserirPeca(Fila *fila, Peca p);
Peca removerPecaFila(Fila *fila);
void empilhar(Pilha *pilha, Peca p);
Peca desempilhar(Pilha *pilha);
void exibirEstado(Fila *fila, Pilha *pilha);
void trocarTopo(Fila *fila, Pilha *pilha);
void trocarMultiplas(Fila *fila, Pilha *pilha);

// ---------------------------
// Implementações
// ---------------------------

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;
}

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int filaCheia(Fila *fila) {
    return fila->quantidade == TAM_FILA;
}

int filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

int pilhaCheia(Pilha *pilha) {
    return pilha->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

// Gera uma nova peça aleatória
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Insere uma peça no final da fila (enqueue)
void inserirPeca(Fila *fila, Peca p) {
    if (filaCheia(fila)) return;
    fila->pecas[fila->fim] = p;
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->quantidade++;
}

// Remove uma peça da frente da fila (dequeue)
Peca removerPecaFila(Fila *fila) {
    Peca removida = {'-', -1};
    if (filaVazia(fila)) return removida;
    removida = fila->pecas[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->quantidade--;
    return removida;
}

// Empilha uma peça (push)
void empilhar(Pilha *pilha, Peca p) {
    if (pilhaCheia(pilha)) {
        printf("\nPilha cheia! Não é possível reservar mais peças.\n");
        return;
    }
    pilha->topo++;
    pilha->pecas[pilha->topo] = p;
}

// Desempilha uma peça (pop)
Peca desempilhar(Pilha *pilha) {
    Peca removida = {'-', -1};
    if (pilhaVazia(pilha)) {
        printf("\nPilha vazia! Nenhuma peça reservada disponível.\n");
        return removida;
    }
    removida = pilha->pecas[pilha->topo];
    pilha->topo--;
    return removida;
}

// Exibe o estado atual da fila e da pilha
void exibirEstado(Fila *fila, Pilha *pilha) {
    printf("\n==============================");
    printf("\nESTADO ATUAL DAS ESTRUTURAS\n");

    printf("\nFila de peças:\n");
    if (filaVazia(fila)) {
        printf("(vazia)\n");
    } else {
        for (int i = 0; i < fila->quantidade; i++) {
            int index = (fila->inicio + i) % TAM_FILA;
            printf("[%c %d] ", fila->pecas[index].nome, fila->pecas[index].id);
        }
        printf("\n");
    }

    printf("\nPilha de reserva (Topo -> Base):\n");
    if (pilhaVazia(pilha)) {
        printf("(vazia)\n");
    } else {
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->pecas[i].nome, pilha->pecas[i].id);
        }
        printf("\n");
    }
    printf("==============================\n");
}

// Troca a peça da frente da fila com o topo da pilha
void trocarTopo(Fila *fila, Pilha *pilha) {
    if (filaVazia(fila) || pilhaVazia(pilha)) {
        printf("\nNão há peças suficientes para trocar.\n");
        return;
    }

    int index = fila->inicio;
    Peca temp = fila->pecas[index];
    fila->pecas[index] = pilha->pecas[pilha->topo];
    pilha->pecas[pilha->topo] = temp;

    printf("\nTroca simples realizada entre a frente da fila e o topo da pilha.\n");
}

// Troca múltipla entre as 3 primeiras da fila e as 3 da pilha
void trocarMultiplas(Fila *fila, Pilha *pilha) {
    if (fila->quantidade < 3 || pilha->topo < 2) {
        printf("\nTroca múltipla não possível (quantidade insuficiente).\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int index = (fila->inicio + i) % TAM_FILA;
        Peca temp = fila->pecas[index];
        fila->pecas[index] = pilha->pecas[pilha->topo - i];
        pilha->pecas[pilha->topo - i] = temp;
    }

    printf("\nTroca múltipla realizada entre as 3 primeiras peças da fila e da pilha.\n");
}

// ---------------------------
// Função principal
// ---------------------------
int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int opcao, contadorID = 0;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        inserirPeca(&fila, gerarPeca(contadorID++));
    }

    do {
        exibirEstado(&fila, &pilha);

        printf("\nOpções disponíveis:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para a pilha de reserva\n");
        printf("3 - Usar peça da pilha de reserva\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar as 3 primeiras da fila com as 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Jogar peça
                Peca jogada = removerPecaFila(&fila);
                if (jogada.id != -1)
                    printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);

                // Gera nova peça para manter fila cheia
                if (!filaCheia(&fila))
                    inserirPeca(&fila, gerarPeca(contadorID++));
                break;
            }

            case 2: { // Enviar da fila para pilha
                if (!pilhaCheia(&pilha)) {
                    Peca reservada = removerPecaFila(&fila);
                    if (reservada.id != -1) {
                        empilhar(&pilha, reservada);
                        printf("\nPeça [%c %d] reservada com sucesso!\n", reservada.nome, reservada.id);
                    }

                    if (!filaCheia(&fila))
                        inserirPeca(&fila, gerarPeca(contadorID++));
                } else {
                    printf("\nPilha cheia! Não é possível reservar mais peças.\n");
                }
                break;
            }

            case 3: { // Usar peça da pilha
                Peca usada = desempilhar(&pilha);
                if (usada.id != -1)
                    printf("\nPeça usada: [%c %d]\n", usada.nome, usada.id);
                break;
            }

            case 4: // Trocar topo
                trocarTopo(&fila, &pilha);
                break;

            case 5: // Troca múltipla
                trocarMultiplas(&fila, &pilha);
                break;

            case 0:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
