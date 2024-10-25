#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct{
    char unome[50], uuser[50], uemail[50], usenha[50];
}Usuario;

int main(){
    setlocale(LC_ALL,"portuguese");

    FILE *file0; //Ponteiro do arquivo de usuários;
    file0=fopen("C:\\Users\\01\\Documents\\Projetos\\AED-UNIII\\usuarios.txt", "a+");
    if(file0==NULL){
        perror("[ERRO]");
        exit (1);
    }

//Inicio da captura de dados e inicialização da estrutura de usuários:

    long int capacidade=10, usuarios=0;

    Usuario *usuario=(Usuario*)malloc(capacidade*sizeof(Usuario));
    if(usuario==NULL){
        perror("[ERRO]");
        exit (1);
    }

    while(fscanf(file0, "%[^\n.]. %s %s %s\n",
    (usuario)[usuarios].unome, (usuario)[usuarios].uuser, (usuario)[usuarios].uemail, (usuario)[usuarios].usenha)!=EOF){

        if(usuarios==(capacidade-1)){ //Aumento da capacidade do vetor dinâmico, caso chegue ao seu limite;
            capacidade=capacidade*2;

            usuario=(Usuario*)realloc(usuario, capacidade*sizeof(Usuario));
            if(usuario==NULL){
                perror("[ERRO]");
                exit (1);
            }
        }

        usuarios++;
    }

//Fim da captura de dados e inicialização da estrutura de usuários;

    short int opcao; //Variável para as opções dos menus;
    char nome[50], user[50], email[50], senha[50];

//Primeiro menu:
    do{
        puts("[SISTEMA]\n1 - Entrar\n2 - Cadastrar-se\n0 - Sair");
        scanf("%hi", &opcao);
        switch(opcao){
            case 1:
            break;
            case 2:
            break;
            case 0:
            break;
        }
    }while(opcao!=0);

    free(usuario);
    fclose(file0);
    return 0;
}
/*
typedef struct usuario{
    char unome[50], uuser[50], uemail[50], usenha[50];
    struct usuario *proximo;
}usuario;

void exibirlista(usuario *topo);
void inserirusuario(usuario **topo, char s1[], char s2[], char s3[], char s4[]);
void liberarlista(usuario *topo);

int main(){
    setlocale(LC_ALL,"");
    FILE *file0; //Ponteiro de arquivos do texto de usuários;
    file0=fopen("C:\\Users\\01\\Documents\\Projetos\\AED-UNIII\\usuarios.txt","a+");

    usuario *topo=NULL;
    char nome[50], user[50], email[50], senha[50];

    while(fscanf(file0, "%[^\n.]. %s %s %s\n", nome, user, email, senha)!=EOF){
        inserirusuario(&topo, nome, user, email, senha);
    }
    puts("[LISTA DE USUÁRIOS]");
    exibirlista(topo);
    liberarlista(topo);
    fclose(file0);
    return 0;
}

void exibirlista(usuario *topo){
    usuario *atual=topo;
    while(atual!=NULL){
        printf("Nome: %s / Usuário: %s / E-mail: %s / Senha: %s\n",
        (*atual).unome, (*atual).uuser, (*atual).uemail, (*atual).usenha);
        atual=(*atual).proximo;
    }
}

void liberarlista(usuario *topo){
    usuario *atual=topo, *tmprr;
    while(atual!=NULL){
        tmprr=atual;
        atual=(*atual).proximo;
        free(tmprr);
    }
}

usuario* criarusuario(char s1[], char s2[], char s3[], char s4[]){
    usuario *u=(usuario*)malloc(sizeof(usuario));
    if(u==NULL){
        perror("[ERRO]");
        return NULL;
    }else{
        strcpy((*u).unome, s1); strcpy((*u).uuser, s2);
        strcpy((*u).uemail, s3); strcpy((*u).usenha, s4);
        (*u).proximo=NULL;
        return u;
    }
}

void inserirusuario(usuario **topo, char s1[], char s2[], char s3[], char s4[]){
    usuario *novousuario=criarusuario(s1, s2, s3, s4);
    if(novousuario!=NULL){
        (*novousuario).proximo=*topo;
        *topo=novousuario;
    }
}
*/