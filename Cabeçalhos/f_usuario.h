typedef struct Usuario{
    char nome[50], user[50], email[50], senha[50];
    struct Usuario *prox;
}Usuario;

void limpar_buffer();
void inserirusuario(Usuario **topo, char s1[], char s2[], char s3[], char s4[]);
short int validarsenha(Usuario *topo, char c[], short int si);
short int validarusuario(Usuario *topo, char c[]);
short int validaremail(Usuario *topo, char c[]);
void exibirusuarios(Usuario *topo);
void liberarusuarios(Usuario *topo);