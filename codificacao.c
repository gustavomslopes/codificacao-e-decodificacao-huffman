#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TADLista.h"
#include "TADArvore.h"
#include "TADFloresta.h"

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
            adicionarListaOrd(&*lista, reg);
            palavra[0] = ' ';
            palavra[1] = '\0';
            strcpy(reg.palavra, palavra);
            adicionarListaOrd(&*lista, reg);
            pos = 0;
        }
        else
            palavra[pos++] = letra;
        letra = getc(arq);
    }
    palavra[pos] = '\0';
    strcpy(reg.palavra, strupr(palavra));
    adicionarListaOrd(&*lista, reg);
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

Lista *buscarPalavra(Lista *lista, char palavra[])
{
    while (lista != NULL && strcmp(palavra, lista->registro.palavra) != 0)
        lista = lista->prox;
    if (lista == NULL)
        return NULL;
    return lista;
}

void preencherListaOrd(Lista **lista, Lista *palavras)
{
    int simbolo = 0;
    while (palavras != NULL)
    {
        if (!buscarPalavra(*lista, palavras->registro.palavra))
        {
            palavras->registro.simbolo = simbolo++;
            adicionarListaOrd(&*lista, palavras->registro);
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

void separarFrase(Lista **lista, char frase[])
{
    int pos = 0, i = 0;
    Registro reg;
    char palavra[20];

    while (i < strlen(frase))
    {
        if (frase[i] == ' ')
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
            palavra[pos++] = frase[i];
        i++;
    }
    palavra[pos] = '\0';
    strcpy(reg.palavra, strupr(palavra));
    adicionarLista(&*lista, reg);
}

void gravarBinario(char frase[], Lista *lista)
{
    FILE *arq = fopen("binario.dat", "wb+");
    Lista *aux, *palavra;
    struct bits b;
    char codigo[256], carac;
    char codigoFinal[1000];
    int pos=0, i, dif;
    initLista(&aux);
    separarFrase(&aux, frase);
    while (aux != NULL)
    {
        palavra = buscarPalavra(lista, aux->registro.palavra);
        strcpy(codigo, palavra->registro.codigo);
        for(i=0; i<strlen(codigo); i++)
            codigoFinal[pos++] = codigo[i];
        aux = aux->prox;
    }
    codigoFinal[pos] = '\0';
    
    if(strlen(codigoFinal)%8!=0)
    {
        dif = 8 - strlen(codigoFinal)%8;
        pos = strlen(codigoFinal);
        for(i=0; i<dif; i++)
            codigoFinal[pos++] = '0';
    }
    printf("%s", codigoFinal);
    pos=0;
    while(pos<strlen(codigoFinal))
    {
        b.b0 = codigoFinal[pos++];
        b.b1 = codigoFinal[pos++]; 
        b.b2 = codigoFinal[pos++];
        b.b3 = codigoFinal[pos++];
        b.b4 = codigoFinal[pos++];
        b.b5 = codigoFinal[pos++];
        b.b6 = codigoFinal[pos++];
        b.b7 = codigoFinal[pos++];
        fwrite(&b, sizeof(struct bits), 1, arq);

    }
    rewind(arq);
    fread(&carac, sizeof(char), 1, arq);
    while (!feof(arq))
        fread(&carac, sizeof(char), 1, arq);

    fclose(arq);
}

int main()
{
    Lista *palavras, *lista, *aux;
    int n, t;
    char d[256], frase[] = "amar e viver e amar Cada um tera um tempo para crescer";
    Tree *raiz;
    initLista(&palavras); initLista(&lista); initArv(&raiz);
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
    gravarBinario(frase, lista);

    return 0;
}
