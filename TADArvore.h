struct tree
{
    int simbolo;
    int frequencia;
    struct tree *esq;
    struct tree *dir;
};
typedef struct tree Tree;

void initArv(Tree **raiz)
{
    *raiz = NULL;
}

Tree * novoNoArv(int cod, int freq)
{
    Tree *novo = (Tree *)malloc(sizeof(Tree));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->simbolo = cod;
    novo->frequencia = freq;   
    return novo;
}

void exibeArv(Tree *raiz, int *n)
{
    int i;
    if(raiz!=NULL)
    {
        (*n)++;
        exibeArv(raiz->dir, &*n);
        for(i=0; i<(*n)*5; i++)
            printf(" ");
        printf("(%d, %d)\n", raiz->simbolo, raiz->frequencia);
        exibeArv(raiz->esq, &*n);
        (*n)--;
    }
}