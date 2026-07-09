#include <stdio.h>
#include <stdlib.h>

struct No {
    int valor;
    struct No* filhoEsquerdo;
    struct No* filhoDireito;
    int altura;
};

int obterAltura(struct No* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

struct No* criarNovoNo(int novoValor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->valor = novoValor;
    novoNo->filhoEsquerdo = NULL;
    novoNo->filhoDireito = NULL;
    novoNo->altura = 1;
    return novoNo;
}

int pegarMaior(int a, int b) {
    return (a > b) ? a : b;
}

int calcularBalanceamento(struct No* no) {
    if (no == NULL)
        return 0;
    return obterAltura(no->filhoEsquerdo) - obterAltura(no->filhoDireito);
}

struct No* rotacionarParaDireita(struct No* paiDesbalanceado) {
    struct No* novoPai = paiDesbalanceado->filhoEsquerdo;
    struct No* subArvoreTransferida = novoPai->filhoDireito;

    // A mágica da rotação acontece nestas duas linhas:
    novoPai->filhoDireito = paiDesbalanceado;
    paiDesbalanceado->filhoEsquerdo = subArvoreTransferida;

    // Atualiza as alturas (primeiro o antigo pai que desceu, depois o novo que subiu)
    paiDesbalanceado->altura = pegarMaior(obterAltura(paiDesbalanceado->filhoEsquerdo), obterAltura(paiDesbalanceado->filhoDireito)) + 1;
    novoPai->altura = pegarMaior(obterAltura(novoPai->filhoEsquerdo), obterAltura(novoPai->filhoDireito)) + 1;

    return novoPai;
}

struct No* rotacionarParaEsquerda(struct No* paiDesbalanceado) {
    struct No* novoPai = paiDesbalanceado->filhoDireito;
    struct No* subArvoreTransferida = novoPai->filhoEsquerdo;

    // A mágica da rotação:
    novoPai->filhoEsquerdo = paiDesbalanceado;
    paiDesbalanceado->filhoDireito = subArvoreTransferida;

    paiDesbalanceado->altura = pegarMaior(obterAltura(paiDesbalanceado->filhoEsquerdo), obterAltura(paiDesbalanceado->filhoDireito)) + 1;
    novoPai->altura = pegarMaior(obterAltura(novoPai->filhoEsquerdo), obterAltura(novoPai->filhoDireito)) + 1;

    return novoPai;
}

struct No* inserir(struct No* raizAtual, int novoValor) {
    // 1. Passo padrão de Árvore de Busca
    if (raizAtual == NULL)
        return criarNovoNo(novoValor);

    if (novoValor < raizAtual->valor)
        raizAtual->filhoEsquerdo = inserir(raizAtual->filhoEsquerdo, novoValor);
    else if (novoValor > raizAtual->valor)
        raizAtual->filhoDireito = inserir(raizAtual->filhoDireito, novoValor);
    else
        return raizAtual; // Valores iguais não são permitidos

    // 2. Atualiza a altura deste nó
    raizAtual->altura = 1 + pegarMaior(obterAltura(raizAtual->filhoEsquerdo), obterAltura(raizAtual->filhoDireito));

    // 3. Checa se esse nó ficou desbalanceado
    int fatorBalanceamento = calcularBalanceamento(raizAtual);

    // 4. Resolve os desbalanceamentos

    // Caso Esquerda-Esquerda (Pesou pra esquerda direto)
    if (fatorBalanceamento > 1 && novoValor < raizAtual->filhoEsquerdo->valor)
        return rotacionarParaDireita(raizAtual);

    // Caso Direita-Direita (Pesou pra direita direto)
    if (fatorBalanceamento < -1 && novoValor > raizAtual->filhoDireito->valor)
        return rotacionarParaEsquerda(raizAtual);

    // Caso Esquerda-Direita (Zigue-zague pra esquerda e depois direita)
    if (fatorBalanceamento > 1 && novoValor > raizAtual->filhoEsquerdo->valor) {
        raizAtual->filhoEsquerdo = rotacionarParaEsquerda(raizAtual->filhoEsquerdo);
        return rotacionarParaDireita(raizAtual);
    }

    // Caso Direita-Esquerda (Zigue-zague pra direita e depois esquerda)
    if (fatorBalanceamento < -1 && novoValor < raizAtual->filhoDireito->valor) {
        raizAtual->filhoDireito = rotacionarParaDireita(raizAtual->filhoDireito);
        return rotacionarParaEsquerda(raizAtual);
    }

    return raizAtual;
}

void imprimirEmOrdem(struct No* raizAtual) {
    if (raizAtual != NULL) {
        imprimirEmOrdem(raizAtual->filhoEsquerdo);
        printf("%d ", raizAtual->valor);
        imprimirEmOrdem(raizAtual->filhoDireito);
    }
}

int main() {
    struct No* raiz = NULL;

    raiz = inserir(raiz, 1);
    raiz = inserir(raiz, 2);
    raiz = inserir(raiz, 4);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 6);
    raiz = inserir(raiz, 3);

    printf("Impressão da árvore AVL em Ordem: ");
    imprimirEmOrdem(raiz);

    return 0;
}
