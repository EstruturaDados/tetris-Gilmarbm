#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 5

// Estrutura da peça
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura da fila
typedef struct {
    Peca itens[TAMANHO];
    int inicio;
    int fim;
    int total;
} Fila;

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == TAMANHO;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Gera peça automática
Peca gerarPeca(int id) {

    Peca nova;

    char tipos[] = {'I', 'O', 'T', 'L'};

    int sorteio = rand() % 4;

    nova.nome = tipos[sorteio];
    nova.id = id;

    return nova;
}

// Inserir peça na fila
void enqueue(Fila *f, Peca p) {

    if (filaCheia(f)) {
        printf("Fila cheia!\n");
        return;
    }

    f->itens[f->fim] = p;

    f->fim = (f->fim + 1) % TAMANHO;

    f->total++;

    printf("Nova peça inserida: [%c %d]\n", p.nome, p.id);
}

// Remover peça da fila
void dequeue(Fila *f) {

    if (filaVazia(f)) {
        printf("Fila vazia!");
        return;
    }

    Peca removida = f->itens[f->inicio];

    printf("Peça jogada: [%c %d]\n", removida.nome, removida.id);

    f->inicio = (f->inicio + 1) % TAMANHO;

    f->total--;
}

// Mostrar fila
void mostrarFila(Fila *f) {

    printf("Fila de peças: ");

    if (filaVazia(f)) {
        printf("Fila vazia!!!");
        return;
    }

    int indice = f->inicio;

    for (int i = 0; i < f->total; i++) {

        printf("[%c %d] ",
               f->itens[indice].nome,
               f->itens[indice].id);

        indice = (indice + 1) % TAMANHO;
    }

    printf("");
}

int main() {

    srand(time(NULL));

    Fila fila;

    inicializarFila(&fila);

    int contadorID = 0;

    // Preenche fila inicial
    for (int i = 0; i < TAMANHO; i++) {

        enqueue(&fila, gerarPeca(contadorID));

        contadorID++;
    }

    int opcao;

    do {

        mostrarFila(&fila);

        printf("\n1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                dequeue(&fila);
                break;

            case 2:
                enqueue(&fila, gerarPeca(contadorID));
                contadorID++;
                break;

            case 0:
                printf("Encerrando programa...");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}

    



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


