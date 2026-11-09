struct floresta
{
    Tree *raiz;
    struct floresta *prox;
};
typedef struct floresta Floresta;

void initFloresta(Floresta **floresta)
{
    *floresta = NULL;
}

Floresta *novoNoF(Tree *raiz)
{
    Floresta *novo = (Floresta *)malloc(sizeof(Floresta));
    novo->prox = NULL;
    novo->raiz = raiz;
    return novo;
}

void adicionarF(Floresta **floresta, Tree *raiz)
{
    Floresta *novo = novoNoF(raiz);
    Floresta *aux;
    if (*floresta == NULL)
        *floresta = novo;
    else
    {
        aux = *floresta;
        if (raiz->frequencia < aux->raiz->frequencia)
        {
            novo->prox = aux;
            *floresta = novo;
        }
        else
        {
            while (aux->prox != NULL && raiz->frequencia > aux->prox->raiz->frequencia)
                aux = aux->prox;
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    }
}

void removerF(Floresta **floresta, Tree **raiz)
{
    Floresta *aux;
    if (*floresta != NULL)
    {
        aux = *floresta;
        *floresta = (*floresta)->prox;
        *raiz = aux->raiz;
        free(aux);
    }
}

int tamanhoF(Floresta *floresta)
{
    int tam=0;
    while(floresta!=NULL)
    {
        tam++;
        floresta = floresta->prox;
    }
    return tam;
}