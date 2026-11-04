struct registro
{
    int simbolo;
    char palavra[20];
    int frequencia;
    char codigo;
};
typedef struct registro Registro;

struct lista
{
    Registro registro;
    struct lista *prox;
};
typedef struct lista Lista;

void init(Lista **l)
{
    *l = NULL;
}

Lista *novoNo(Registro reg)
{
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->registro = reg;
    novo->prox = NULL;
    return novo;
}

void adicionar(Lista **l, Registro reg)
{
    Lista *novo = novoNo(reg);
    Lista *aux;
    if (*l == NULL)
        *l = novo;
    else
    {
        aux = *l;
        if (reg.frequencia < aux->registro.frequencia)
        {
            novo->prox = aux;
            *l = novo;
        }
        else
        {
            while (aux->prox != NULL && reg.frequencia > aux->prox->registro.frequencia)
                aux = aux->prox;
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    }
}

int tamanho(Lista *l)
{
    int tam = 0;
    while (l != NULL)
    {
        tam++;
        l = l->prox;
    }
    return tam;
}

void remover(Lista **l)
{
    Lista *aux;
    if (*l != NULL)
    {
        aux = *l;
        *l = (*l)->prox;
        free(aux);
    }
}