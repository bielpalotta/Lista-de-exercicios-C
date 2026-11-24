#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int dado;
    struct No *proximo;
} No;

No *criarNo(int valor)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Erro: memoria insuficiente.\n");
        exit(1);
    }
    novo->dado = valor;
    novo->proximo = NULL;
    return novo;
}

void exibir(No *inicio)
{
    if (inicio == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }
    for (No *p = inicio; p != NULL; p = p->proximo)
    {
        printf("%d", p->dado);
        if (p->proximo != NULL)
            printf(" -> ");
    }
    printf(" -> NULL\n");
}

void liberarLista(No **inicio)
{
    No *atual = *inicio;
    while (atual != NULL)
    {
        No *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    *inicio = NULL;
}

void inserirInicio(No **inicio, int valor)
{
    No *novo = criarNo(valor);
    novo->proximo = *inicio;
    *inicio = novo;
    printf("Inserido %d no inicio: ", valor);
    exibir(*inicio);
}

void inserirFinal(No **inicio, int valor)
{
    No *novo = criarNo(valor);
    if (*inicio == NULL)
    {
        *inicio = novo;
    }
    else
    {
        No *p = *inicio;
        while (p->proximo != NULL)
            p = p->proximo;
        p->proximo = novo;
    }
    printf("Inserido %d no final: ", valor);
    exibir(*inicio);
}

No *buscar(No *inicio, int valor, int *posicao)
{
    int i = 0;
    for (No *p = inicio; p != NULL; p = p->proximo, i++)
    {
        if (p->dado == valor)
        {
            *posicao = i;
            return p;
        }
    }
    return NULL;
}

void testarBusca(No *inicio, int valor)
{
    int pos;
    No *achado = buscar(inicio, valor, &pos);
    if (achado != NULL)
        printf("Valor %d encontrado no endereco %p, posicao %d (indice) / %da posicao.\n",
               valor, (void *)achado, pos, pos + 1);
    else
        printf("Valor %d nao existe na lista (retornou NULL).\n", valor);
}

void removerInicio(No **inicio)
{
    if (*inicio == NULL)
    {
        printf("Lista vazia, nada a remover.\n");
        return;
    }
    No *remover = *inicio;
    *inicio = remover->proximo;
    free(remover);
    printf("Removido o primeiro elemento: ");
    exibir(*inicio);
}

void removerFinal(No **inicio)
{
    if (*inicio == NULL)
    {
        printf("Lista vazia, nada a remover.\n");
        return;
    }
    if ((*inicio)->proximo == NULL)
    {
        free(*inicio);
        *inicio = NULL;
    }
    else
    {
        No *p = *inicio;
        while (p->proximo->proximo != NULL)
            p = p->proximo;
        free(p->proximo);
        p->proximo = NULL;
    }
    printf("Removido o ultimo elemento: ");
    exibir(*inicio);
}

void removerValor(No **inicio, int valor)
{
    No *anterior = NULL;
    No *atual = *inicio;

    while (atual != NULL && atual->dado != valor)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("Valor %d nao encontrado.\n", valor);
        return;
    }

    if (anterior == NULL)
        *inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("Removido o valor %d: ", valor);
    exibir(*inicio);
}

typedef struct
{
    int quantidade;
    int maior;
    int menor;
    int soma;
    double media;
} Estatisticas;

int calcularEstatisticas(No *inicio, Estatisticas *e)
{
    if (inicio == NULL)
        return 0;

    e->quantidade = 0;
    e->soma = 0;
    e->maior = inicio->dado;
    e->menor = inicio->dado;

    for (No *p = inicio; p != NULL; p = p->proximo)
    {
        e->quantidade++;
        e->soma += p->dado;
        if (p->dado > e->maior)
            e->maior = p->dado;
        if (p->dado < e->menor)
            e->menor = p->dado;
    }
    e->media = (double)e->soma / e->quantidade;
    return 1;
}

void exibirEstatisticas(No *inicio)
{
    Estatisticas e;
    if (!calcularEstatisticas(inicio, &e))
    {
        printf("Lista vazia: sem estatisticas.\n");
        return;
    }
    printf("Quantidade: %d | Maior: %d | Menor: %d | Soma: %d | Media: %.2f\n",
           e.quantidade, e.maior, e.menor, e.soma, e.media);
}

void inserirOrdenado(No **inicio, int valor)
{
    No *novo = criarNo(valor);

    if (*inicio == NULL || valor < (*inicio)->dado)
    {
        novo->proximo = *inicio;
        *inicio = novo;
    }
    else
    {
        No *p = *inicio;
        while (p->proximo != NULL && p->proximo->dado <= valor)
            p = p->proximo;
        novo->proximo = p->proximo;
        p->proximo = novo;
    }
    printf("Inserido %d (ordenado): ", valor);
    exibir(*inicio);
}

void unirListas(No **lista1, No *lista2)
{
    if (*lista1 == NULL)
    {
        *lista1 = lista2;
        return;
    }
    No *p = *lista1;
    while (p->proximo != NULL)
        p = p->proximo;
    p->proximo = lista2;
}

int main(void)
{
    No *lista = NULL;

    printf("=== Ex. 2: insercao no inicio ===\n");
    inserirInicio(&lista, 30);
    inserirInicio(&lista, 20);
    inserirInicio(&lista, 10);
    liberarLista(&lista);

    printf("\n=== Ex. 3: insercao no final ===\n");
    inserirFinal(&lista, 10);
    inserirFinal(&lista, 20);
    inserirFinal(&lista, 30);
    inserirFinal(&lista, 40);

    printf("\n=== Ex. 4: busca ===\n");
    testarBusca(lista, 30);
    testarBusca(lista, 99);

    printf("\n=== Ex. 5: remocao ===\n");
    removerInicio(&lista);
    removerFinal(&lista);
    removerValor(&lista, 20);
    removerValor(&lista, 99);
    liberarLista(&lista);

    printf("\n=== Ex. 6: estatisticas ===\n");
    inserirFinal(&lista, 8);
    inserirFinal(&lista, 3);
    inserirFinal(&lista, 15);
    inserirFinal(&lista, 4);
    exibirEstatisticas(lista);
    liberarLista(&lista);

    printf("\n=== Ex. 7: lista ordenada ===\n");
    inserirOrdenado(&lista, 30);
    inserirOrdenado(&lista, 10);
    inserirOrdenado(&lista, 20);
    inserirOrdenado(&lista, 5);
    inserirOrdenado(&lista, 25);
    liberarLista(&lista);

    printf("\n=== Ex. 9: uniao de listas ===\n");
    No *l1 = NULL, *l2 = NULL;
    inserirFinal(&l1, 10);
    inserirFinal(&l1, 20);
    inserirFinal(&l1, 30);
    inserirFinal(&l2, 40);
    inserirFinal(&l2, 50);
    inserirFinal(&l2, 60);
    unirListas(&l1, l2);
    printf("Resultado da uniao: ");
    exibir(l1);
    liberarLista(&l1);

    return 0;
}
