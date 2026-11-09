#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TADArvore.h"
#include "TADLIsta.h"

struct bits
{
    unsigned char b7 : 1;
    unsigned char b6 : 1;
    unsigned char b5 : 1;
    unsigned char b4 : 1;
    unsigned char b3 : 1;
    unsigned char b2 : 1;
    unsigned char b1 : 1;
    unsigned char b0 : 1;
};

void gerarLista(Lista **lista)
{
    FILE *arq = fopen("lista.dat", "rb");
    Registro reg;
    if (arq != NULL)
    {
        fread(&reg, sizeof(Registro), 1, arq);
        while (!feof(arq))
        {
            adicionarListaOrd(&*lista, reg);
            fread(&reg, sizeof(Registro), 1, arq);
        }
    }

    fclose(arq);
}

void gerarArvore(Lista *lista, Tree **raiz)
{
    Tree *aux = *raiz = novoNoArv(-1, 0);
    int pos;
    char codigo[256];
    while (lista != NULL)
    {
        pos = 0;
        aux = *raiz;
        strcpy(codigo, lista->registro.codigo);
        while (pos < strlen(codigo))
        {
            if (codigo[pos] == '1')
            {
                if (aux->dir == NULL)
                    aux->dir = novoNoArv(-1, 0);

                aux = aux->dir;
            }
            else
            {
                if (aux->esq == NULL)
                    aux->esq = novoNoArv(-1, 0);
                aux = aux->esq;
            }
            pos++;
        }
        aux->simbolo = lista->registro.simbolo;
        lista = lista->prox;
    }
}

int gerarBinario(int codBinario[])
{
    FILE *arq = fopen("binario.dat", "rb");
    int i;
    struct bits b;
    fread(&b, sizeof(struct bits), 1, arq);
    i = 0;
    while (!feof(arq))
    {
        codBinario[i++] = b.b0;
        codBinario[i++] = b.b1;
        codBinario[i++] = b.b2;
        codBinario[i++] = b.b3;
        codBinario[i++] = b.b4;
        codBinario[i++] = b.b5;
        codBinario[i++] = b.b6;
        codBinario[i++] = b.b7;
        fread(&b, sizeof(struct bits), 1, arq);
    }
    fclose(arq);
    return i;
}

Registro buscarPalavra(int simbolo)
{
    FILE *arq = fopen("lista.dat", "rb");
    Registro reg;

    fread(&reg, sizeof(Registro), 1, arq);
    while (!feof(arq) && reg.simbolo != simbolo)
        fread(&reg, sizeof(Registro), 1, arq);
    
    fclose(arq);
    return reg;
}

void decodificarPalavras(Tree *raiz, Lista *lista, int codBinario[], int tl, char frase[])
{
    int i = 0;
    int pos = 0, j;
    char palavra[20];
    Tree *aux = raiz;
    Registro reg;
    while (i < tl)
    {
        if (folha(aux))
        {
            reg = buscarPalavra(aux->simbolo);
            strcpy(palavra, reg.palavra);
            j = 0;
            while (j < strlen(palavra))
            {
                frase[pos++] = palavra[j];
                j++;
            }
            frase[pos++] = ' ';
            aux = raiz;
        }
        else
        {
            if (codBinario[i] == 1)
                aux = aux->dir;
            else
                aux = aux->esq;
        }
        i++;
    }
}

int main()
{
    Lista *lista;
    Tree *raiz;
    int tl;
    int codBinario[1000];
    char frase[1000];
    initLista(&lista);
    initArv(&raiz);

    gerarLista(&lista);
    gerarArvore(lista, &raiz);
    tl = gerarBinario(codBinario);
    decodificarPalavras(raiz, lista, codBinario, tl, frase);
    printf("%s", frase);
    return 0;
}