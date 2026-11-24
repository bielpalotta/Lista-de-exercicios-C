#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contato
{
    char nome[50];
    char telefone[20];

    struct Contato *proximo;
} Contato;

void lerTexto(const char *rotulo, char *destino, int tamanho)
{
    printf("%s", rotulo);
    if (fgets(destino, tamanho, stdin) != NULL)
        destino[strcspn(destino, "\n")] = '\0';
}

void cadastrar(Contato **inicio)
{
    Contato *novo = (Contato *)malloc(sizeof(Contato));
    if (novo == NULL)
    {
        printf("Erro de memoria.\n");
        return;
    }
    lerTexto("Nome: ", novo->nome, sizeof(novo->nome));
    lerTexto("Telefone: ", novo->telefone, sizeof(novo->telefone));

    novo->proximo = *inicio;
    *inicio = novo;
    printf("Contato cadastrado.\n");
}

Contato *buscarPorNome(Contato *inicio, const char *nome)
{
    for (Contato *p = inicio; p != NULL; p = p->proximo)
        if (strcmp(p->nome, nome) == 0)
            return p;
    return NULL;
}

void buscar(Contato *inicio)
{
    char nome[50];
    lerTexto("Nome a buscar: ", nome, sizeof(nome));
    Contato *c = buscarPorNome(inicio, nome);
    if (c != NULL)
        printf("Encontrado: %s - %s\n", c->nome, c->telefone);
    else
        printf("Contato nao encontrado.\n");
}

void remover(Contato **inicio)
{
    char nome[50];
    lerTexto("Nome a remover: ", nome, sizeof(nome));

    Contato *anterior = NULL, *atual = *inicio;
    while (atual != NULL && strcmp(atual->nome, nome) != 0)
    {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL)
    {
        printf("Contato nao encontrado.\n");
        return;
    }
    if (anterior == NULL)
        *inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;
    free(atual);
    printf("Contato removido.\n");
}

void listar(Contato *inicio)
{
    if (inicio == NULL)
    {
        printf("Agenda vazia.\n");
        return;
    }
    int i = 1;
    for (Contato *p = inicio; p != NULL; p = p->proximo)
        printf("%d. %s - %s\n", i++, p->nome, p->telefone);
}

void liberarAgenda(Contato **inicio)
{
    while (*inicio != NULL)
    {
        Contato *prox = (*inicio)->proximo;
        free(*inicio);
        *inicio = prox;
    }
}

int main(void)
{
    Contato *agenda = NULL;
    int opcao;
    char buf[16];

    do
    {
        printf("\n--- AGENDA ---\n1. Cadastrar\n2. Buscar\n3. Remover\n4. Listar\n0. Sair\nOpcao: ");
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            break;
        opcao = atoi(buf);

        switch (opcao)
        {
        case 1: cadastrar(&agenda); break;
        case 2: buscar(agenda); break;
        case 3: remover(&agenda); break;
        case 4: listar(agenda); break;
        case 0: printf("Encerrando...\n"); break;
        default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberarAgenda(&agenda);
    return 0;
}
