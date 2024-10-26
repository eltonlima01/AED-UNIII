typedef struct Produto{
    char nome[50];
    float preco;
    int ID; //A variável ID identifica se o produto está em promoção (1) ou não (0);
}Produto;

void menuinterno();
void compararproduto(char s[], int indice, Produto *p);
void editarproduto(int indice, Produto *produto, FILE *file1);
void excluirproduto(int *indice, Produto *produto, FILE *file1);