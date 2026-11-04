#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TADLista.h"

void separarTexto(Lista **lista){
    FILE *arq = fopen("texto.txt", "r");
    int pos=0;
    Registro reg;
    char palavra[20];
    char letra;
    letra = getc(arq);
    while(!feof(arq)){
        if(letra == ' '){
            palavra[pos] = '\0';
            strcpy(reg.palavra, strupr(palavra));
            adicionar(&*lista, reg);
            palavra[0] = ' ';
            palavra[1] = '\0';
            strcpy(reg.palavra, palavra);
            adicionar(&*lista, reg);
            pos=0;
        } 
        else
            palavra[pos++] = letra;
        letra = getc(arq);
    }
    fclose(arq);
}

void registrarFrequencias(Lista *l){
    Lista *aux, *primeiro = l;
    char palavra[20];
    int freq;
    while(l!=NULL){
        strcpy(palavra, l->registro.palavra);
        freq = 0;
        aux = l;
        l = primeiro;
        while(l!=NULL){
            if(strcmp(l->registro.palavra, palavra)==0){
                freq++;
            }
            l = l->prox;
        }
        l = aux;
        l->registro.frequencia = freq;
        l = l->prox;
    }
}

int buscarPalavra(Lista *lista, char palavra[])
{
    while(lista!=NULL && strcmp(palavra, lista->registro.palavra)!=0)
        lista = lista->prox;
    if(lista==NULL)
        return 0;
    return 1;
}

void preencherListaOrd(Lista **lista, Lista *palavras){
    int simbolo=0;
    while(palavras!=NULL){
        if(!buscarPalavra(*lista, palavras->registro.palavra))
        {
            palavras->registro.simbolo = simbolo++;
            adicionar(&*lista, palavras->registro);
        }
            
        palavras = palavras->prox;
    }
}

int main(){
    Lista *palavras, *lista;
    init(&palavras); init(&lista);
    separarTexto(&palavras);
    registrarFrequencias(palavras);
    Lista *aux = palavras;
    while(aux!=NULL){
        printf("%s-%d|", aux->registro.palavra, aux->registro.frequencia);
        aux = aux->prox;
    }
    printf("\n\n\n");
    preencherListaOrd(&lista, palavras);
    aux = lista;
    while(aux!=NULL){
        printf("%s-%d-%d\n", aux->registro.palavra, aux->registro.frequencia, aux->registro.simbolo);
        aux = aux->prox;
    }
    return 0;
}
