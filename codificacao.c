#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TADLista.h"
#include "TADArvore.h"
#include "TADFloresta.h"

void separarTexto(Lista **lista)
{
    FILE *arq = fopen("texto.txt", "r");
    int pos = 0;
    Registro reg;
    char palavra[20];
    char letra;
    letra = getc(arq);
    while (!feof(arq))
    {
        if (letra == ' ')
        {
            palavra[pos] = '\0';
            strcpy(reg.palavra, strupr(palavra));
            adicionarLista(&*lista, reg);
            palavra[0] = ' ';
            palavra[1] = '\0';
            strcpy(reg.palavra, palavra);
            adicionarLista(&*lista, reg);
            pos = 0;
        }
        else
            palavra[pos++] = letra;
        letra = getc(arq);
    }
    palavra[pos] = '\0';
    strcpy(reg.palavra, strupr(palavra));
    adicionarLista(&*lista, reg);
    fclose(arq);
}

void registrarFrequencias(Lista *l)
{
    Lista *aux, *primeiro = l;
    char palavra[20];
    int freq;
    while (l != NULL)
    {
        strcpy(palavra, l->registro.palavra);
        freq = 0;
        aux = l;
        l = primeiro;
        while (l != NULL)
        {
            if (strcmp(l->registro.palavra, palavra) == 0)
                freq++;

            l = l->prox;
        }
        l = aux;
        l->registro.frequencia = freq;
        l = l->prox;
    }
}

int buscarPalavra(Lista *lista, char palavra[])
{
    while (lista != NULL && strcmp(palavra, lista->registro.palavra) != 0)
        lista = lista->prox;
    if (lista == NULL)
        return 0;
    return 1;
}

void preencherListaOrd(Lista **lista, Lista *palavras)
{
    int simbolo = 0;
    while (palavras != NULL)
    {
        if (!buscarPalavra(*lista, palavras->registro.palavra))
        {
            palavras->registro.simbolo = simbolo++;
            adicionarLista(&*lista, palavras->registro);
        }

        palavras = palavras->prox;
    }
}

Floresta *criarFloresta(Lista *lista, Tree **raiz)
{
    Tree *no = NULL;
    Floresta *floresta;
    initFloresta(&floresta);
    while (lista != NULL)
    {
        no = novoNoArv(lista->registro.simbolo, lista->registro.frequencia);
        adicionarF(&floresta, no);
        lista = lista->prox;
    }
    return floresta;
}

void criarArvore(Lista *lista, Tree **raiz)
{
    Floresta *floresta;
    Tree *raiz1, *raiz2, *no = NULL;
    initArv(&raiz1);
    initArv(&raiz2);
    initFloresta(&floresta);
    floresta = criarFloresta(lista, &*raiz);
    while (tamanhoF(floresta) > 1)
    {
        removerF(&floresta, &raiz1);
        removerF(&floresta, &raiz2);
        no = novoNoArv(-1, raiz1->frequencia + raiz2->frequencia);
        no->esq = raiz1;
        no->dir = raiz2;
        adicionarF(&floresta, no);
    }
    *raiz = floresta->raiz;
}

void codificarPalavras(Tree *raiz, Lista *lista, char d[], int *t)
{
    Lista *aux;
    if (raiz != NULL)
    {
        if (raiz->esq == NULL && raiz->dir == NULL)
        {
            d[(*t) + 1] = '\0';
            aux = buscarLista(lista, raiz->simbolo);
            if (aux != NULL)
                strcpy(aux->registro.codigo, d);
        }

        else
        {
            (*t)++;
            d[*t] = '0';
            codificarPalavras(raiz->esq, lista, d, &*t);
            d[*t] = '1';
            codificarPalavras(raiz->dir, lista, d, &*t);
            (*t)--;
        }
    }
}

int main()
{
    Lista *palavras, *lista, *aux;
    int n, t;
    char d[256];
    Tree *raiz;
    initLista(&palavras);
    initLista(&lista);
    initArv(&raiz);
    separarTexto(&palavras);
    registrarFrequencias(palavras);
    preencherListaOrd(&lista, palavras);
    criarArvore(lista, &raiz);
    t = -1;
    codificarPalavras(raiz, lista, d, &t);
    aux = lista;
    printf("\t\t\tTABELA DE REGISTROS\n");
    while (aux != NULL)
    {
        printf("[%-15s] SIMBOLO: %-4d   FREQUENCIA: %-5d   CODIGO: %s\n", aux->registro.palavra, aux->registro.simbolo, aux->registro.frequencia, aux->registro.codigo);
        aux = aux->prox;
    }
    printf("\n\n\t\t\tARVORE\n");
    n = -1;
    exibeArv(raiz, &n);

    return 0;
}
