#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarefa
{
    int id;
    char descricao[100];
    int concluida;

    struct Tarefa *proximo;
} Tarefa;

static int proximoId = 1;

void cadastrar(Tarefa **inicio)
{
    Tarefa *nova = (Tarefa *)malloc(sizeof(Tarefa));
    if (nova == NULL)
    {
        printf("Erro de memoria.\n");
        return;
    }
    nova->id = proximoId++;
    nova->concluida = 0;
    nova->proximo = NULL;

    printf("Descricao: ");
    fgets(nova->descricao, sizeof(nova->descricao), stdin);
    nova->descricao[strcspn(nova->descricao, "\n")] = '\0';

    if (*inicio == NULL)
        *inicio = nova;
    else
    {
        Tarefa *p = *inicio;
        while (p->proximo != NULL)
            p = p->proximo;
        p->proximo = nova;
    }
    printf("Tarefa %d cadastrada.\n", nova->id);
}

void listar(Tarefa *inicio)
{
    if (inicio == NULL)
    {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }
    for (Tarefa *p = inicio; p != NULL; p = p->proximo)
        printf("[%c] #%d - %s\n", p->concluida ? 'X' : ' ', p->id, p->descricao);
}

Tarefa *localizar(Tarefa *inicio, int id)
{
    for (Tarefa *p = inicio; p != NULL; p = p->proximo)
        if (p->id == id)
            return p;
    return NULL;
}

int lerInteiro(const char *rotulo)
{
    char buf[32];
    printf("%s", rotulo);
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return -1;
    return atoi(buf);
}

void localizarTarefa(Tarefa *inicio)
{
    int id = lerInteiro("ID: ");
    Tarefa *t = localizar(inicio, id);
    if (t != NULL)
        printf("[%c] #%d - %s\n", t->concluida ? 'X' : ' ', t->id, t->descricao);
    else
        printf("Tarefa nao encontrada.\n");
}

void concluir(Tarefa *inicio)
{
    int id = lerInteiro("ID a concluir: ");
    Tarefa *t = localizar(inicio, id);
    if (t != NULL)
    {
        t->concluida = 1;
        printf("Tarefa %d marcada como concluida.\n", id);
    }
    else
        printf("Tarefa nao encontrada.\n");
}

void remover(Tarefa **inicio)
{
    int id = lerInteiro("ID a remover: ");
    Tarefa *anterior = NULL, *atual = *inicio;

    while (atual != NULL && atual->id != id)
    {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL)
    {
        printf("Tarefa nao encontrada.\n");
        return;
    }
    if (anterior == NULL)
        *inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;
    free(atual);
    printf("Tarefa %d removida.\n", id);
}

void liberarTudo(Tarefa **inicio)
{
    while (*inicio != NULL)
    {
        Tarefa *prox = (*inicio)->proximo;
        free(*inicio);
        *inicio = prox;
    }
}

int main(void)
{
    Tarefa *lista = NULL;
    int opcao;

    do
    {
        printf("\n--- TAREFAS ---\n1. Cadastrar\n2. Listar\n3. Localizar por ID\n4. Concluir\n5. Remover\n0. Sair\n");
        opcao = lerInteiro("Opcao: ");

        switch (opcao)
        {
        case 1: cadastrar(&lista); break;
        case 2: listar(lista); break;
        case 3: localizarTarefa(lista); break;
        case 4: concluir(lista); break;
        case 5: remover(&lista); break;
        case 0: printf("Encerrando...\n"); break;
        default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberarTudo(&lista);
    return 0;
}
