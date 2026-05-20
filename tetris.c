#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

// Estrutura da peça
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura da fila
typedef struct {
    Peca itens[TAMANHO_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// Estrutura da pilha
typedef struct {
    Peca itens[TAMANHO_PILHA];
    int topo;
} Pilha;

// Inicializar fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Inicializar pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Verificar fila cheia
int filaCheia(Fila *f) {
    return f->total == TAMANHO_FILA;
}

// Verificar fila vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Verificar pilha cheia
int pilhaCheia(Pilha *p) {
    return p->topo == TAMANHO_PILHA - 1;
}

// Verificar pilha vazia
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Gerar peça automática
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
        return;
    }

    f->itens[f->fim] = p;

    f->fim = (f->fim + 1) % TAMANHO_FILA;

    f->total++;
}

// Remover peça da fila
Peca dequeue(Fila *f) {

    Peca removida = f->itens[f->inicio];

    f->inicio = (f->inicio + 1) % TAMANHO_FILA;

    f->total--;

    return removida;
}

// Inserir peça na pilha
void push(Pilha *p, Peca peca) {

    if (pilhaCheia(p)) {
        printf("Pilha cheia!");
        return;
    }

    p->topo++;

    p->itens[p->topo] = peca;
}

// Remover peça da pilha
Peca pop(Pilha *p) {

    Peca removida = p->itens[p->topo];

    p->topo--;

    return removida;
}

// Mostrar fila
void mostrarFila(Fila *f) {

    printf("Fila de peças");

    int indice = f->inicio;

    for (int i = 0; i < f->total; i++) {

        printf("[%c %d] ",
               f->itens[indice].nome,
               f->itens[indice].id);

        indice = (indice + 1) % TAMANHO_FILA;
    }

    printf("");
}

// Mostrar pilha
void mostrarPilha(Pilha *p) {

    printf("Pilha de reserva: ");

    if (pilhaVazia(p)) {
        printf("Vazia");
        return;
    }

    printf("(Topo -> Base): ");

    for (int i = p->topo; i >= 0; i--) {

        printf("[%c %d] ",
               p->itens[i].nome,
               p->itens[i].id);
    }

    printf("");
}

int main() {

    srand(time(NULL));

    Fila fila;
    Pilha reserva;

    inicializarFila(&fila);
    inicializarPilha(&reserva);

    int contadorID = 0;

    // Preenche fila inicial
    for (int i = 0; i < TAMANHO_FILA; i++) {

        enqueue(&fila, gerarPeca(contadorID));

        contadorID++;
    }

    int opcao;

    do {

        printf("=========== ESTADO ATUAL ===========\n" );

        mostrarFila(&fila);
        printf("\n");
        mostrarPilha(&reserva);

        printf("\nMenu: \n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1: {

                Peca jogada = dequeue(&fila);

                printf("Peça jogada: [%c %d]\n",
                       jogada.nome,
                       jogada.id);

                enqueue(&fila, gerarPeca(contadorID));

                contadorID++;

                break;
            }

            case 2: {

                if (pilhaCheia(&reserva)) {

                    printf("Pilha de reserva cheia!\n");
                    break;
                }

                Peca reservada = dequeue(&fila);

                push(&reserva, reservada);

                printf("Peça reservada: [%c %d]\n",
                       reservada.nome,
                       reservada.id);

                enqueue(&fila, gerarPeca(contadorID));

                contadorID++;

                break;
            }

            case 3: {

                if (pilhaVazia(&reserva)) {

                    printf("Nenhuma peça reservada!\n");
                    break;
                }

                Peca usada = pop(&reserva);

                printf("Peça usada da reserva: [%c %d]\n",
                       usada.nome,
                       usada.id);

                break;
            }

            case 0:
                printf("Encerrando programa...");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}


   

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


