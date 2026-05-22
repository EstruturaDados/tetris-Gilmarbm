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

// Inserir na fila
void enqueue(Fila *f, Peca p) {

    f->itens[f->fim] = p;

    f->fim = (f->fim + 1) % TAMANHO_FILA;

    f->total++;
}

// Remover da fila
Peca dequeue(Fila *f) {

    Peca removida = f->itens[f->inicio];

    f->inicio = (f->inicio + 1) % TAMANHO_FILA;

    f->total--;

    return removida;
}

// Inserir na pilha
void push(Pilha *p, Peca peca) {

    p->topo++;

    p->itens[p->topo] = peca;
}

// Remover da pilha
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

    printf("    Pilha de reserva ");

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

// Trocar peça da frente da fila com topo da pilha
void trocarAtual(Fila *f, Pilha *p) {

    if (pilhaVazia(p)) {

        printf("Pilha vazia!");
        return;
    }

    Peca temp;

    temp = f->itens[f->inicio];

    f->itens[f->inicio] = p->itens[p->topo];

    p->itens[p->topo] = temp;

    printf("Troca realizada com sucesso!");
}

// Trocar os 3 primeiros da fila com os 3 da pilha
void trocaMultipla(Fila *f, Pilha *p) {

    if (p->topo < 2) {

        printf("A pilha precisa ter 3 peças!");
        return;
    }

    int indiceFila = f->inicio;

    for (int i = 0; i < 3; i++) {

        Peca temp;

        temp = f->itens[indiceFila];

        f->itens[indiceFila] = p->itens[p->topo - i];

        p->itens[p->topo - i] = temp;

        indiceFila = (indiceFila + 1) % TAMANHO_FILA;
    }

    printf("Troca múltipla realizada!");
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

        printf("\n=========== ESTADO ATUAL ===========\n" );

        mostrarFila(&fila);
        mostrarPilha(&reserva);

        printf("\n1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para pilha\n");
        printf("3 - Usar peça da pilha\n");
        printf("4 - Trocar peça atual com topo da pilha\n");
        printf("5 - Troca múltipla entre fila e pilha\n");
        printf("0 - Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1: {

                Peca jogada = dequeue(&fila);

                printf("Peça jogada: [%c %d]",
                       jogada.nome,
                       jogada.id);

                enqueue(&fila, gerarPeca(contadorID));

                contadorID++;

                break;
            }

            case 2: {

                if (pilhaCheia(&reserva)) {

                    printf("Pilha cheia!");
                    break;
                }

                Peca reservada = dequeue(&fila);

                push(&reserva, reservada);

                printf("Peça reservada: [%c %d]",
                       reservada.nome,
                       reservada.id);

                enqueue(&fila, gerarPeca(contadorID));

                contadorID++;

                break;
            }

            case 3: {

                if (pilhaVazia(&reserva)) {

                    printf("Pilha vazia!");
                    break;
                }

                Peca usada = pop(&reserva);

                printf("Peça usada: [%c %d]",
                       usada.nome,
                       usada.id);

                break;
            }

            case 4:
                trocarAtual(&fila, &reserva);
                break;

            case 5:
                trocaMultipla(&fila, &reserva);
                break;

            case 0:
                printf("Encerrando programa...");
                break;

            default:
                printf("Opção inválida!");
        }

    } while(opcao != 0);

    return 0;
}
