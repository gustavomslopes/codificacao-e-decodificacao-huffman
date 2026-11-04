struct tree
{
    int codigo;
    struct tree *esq;
    struct tree *dir;
};
typedef struct tree Tree;

void init(Tree **raiz)
{
    *raiz = NULL;
}

void 