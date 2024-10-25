#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct Usuario{
    char nome[50], user[50], email[50], senha[50];
    struct Usuario *prox;
}Usuario;

int indiceusuario;
void limpar_buffer();
void inserirusuario(Usuario **topo, char s1[], char s2[], char s3[], char s4[]);
short int validarusuario(Usuario *topo, char c[]);
short int validaremail(Usuario *topo, char c[]);
void liberarusuarios(Usuario *topo);

int main(){
    setlocale(LC_ALL, "portuguese");

    Usuario *topo=NULL;
    char nome[50], user[50], email[50], senha[50];

    FILE *file0; //Ponteiro para o arquivo de texto dos usuários;
    file0=fopen("C:\\Users\\01\\Documents\\Projetos\\AED-UNIII\\Arquivos\\usuarios.txt", "a+");
    if(file0==NULL){
        perror("[ERRO]");
        exit (1);
    }

    while(fscanf(file0, "%49[^\n.]. %49s %49s %49s\n", nome, user, email, senha)!=EOF){
        inserirusuario(&topo, nome, user, email, senha);
        printf("Nome: %s / Usuário: %s / E-mail: %s / Senha: %s\n", nome, user, email, senha);

    }

    short int opcao;

    do{
        puts("[SISTEMA]\n1. Entrar\n2. Cadastro\n0. Sair");
        scanf("%hi", &opcao); limpar_buffer();

        switch(opcao){
            case 1: //Entrar;

            printf("[ENTRAR]\n1.1. Usuário: ");
            scanf("%49s", user); limpar_buffer();

            printf("[ENTRAR]\n1.2. Senha: ");
            scanf("%49s", senha); limpar_buffer();            

            break;

            case 2: //Cadastro;

            puts("[CADASTRO]\n2.1. Digite o seu nome completo:");
            scanf("%49[^\n]", nome); limpar_buffer();

            puts("2.2. Crie um nome de usuário:");
            scanf("%49s", user); limpar_buffer();

            if(validarusuario(topo, user)==1){

                puts("===================================\n[ERRO] Nome de usuário não disponível.\n===================================");
                break;

            }else if(validarusuario(topo, user)==2){

                puts("===================================\n[ERRO] Nome de usuário muito curto.\n===================================");
                break;

            }

            puts("2.3. Digite o seu endereço de e-mail:");
            scanf("%49s", email); limpar_buffer();

            if(validaremail(topo, email)==1){

                puts("===================================\n[ERRO] Endereço de e-mail não disponível.\n===================================");
                break;

            }else if(validaremail(topo, email)==2){

                puts("===================================\n[ERRO] Ausência de caractere '@'.\n===================================");
                break;

            }

            puts("[CADASTRO]\n2.4. Crie uma senha:");
            scanf("%49s", senha); limpar_buffer();

            fprintf(file0, "%s. %s %s %s\n", nome, user, email, senha);
            inserirusuario(&topo, nome, user, email, senha);
            fflush(file0);

            break;

            case 0:

            puts("[SAINDO]");

            break;
        }

    }while(opcao!=0);


    liberarusuarios(topo);
    fclose(file0);
    return 0;
}

Usuario* novousuario(char s1[], char s2[], char s3[], char s4[]){
    Usuario *u=(Usuario*)malloc(sizeof(Usuario));

    strcpy((*u).nome, s1); strcpy((*u).user, s2);
    strcpy((*u).email, s3); strcpy((*u).senha, s4);
    (*u).prox=NULL;

    return u;
}

void inserirusuario(Usuario **topo, char s1[], char s2[], char s3[], char s4[]){
    Usuario *u=novousuario(s1, s2, s3, s4);

    (*u).prox=*topo;
    *topo=u;

}

void liberarusuarios(Usuario *topo){
    Usuario *atual=topo, *tmprr;

    while(atual!=NULL){
        tmprr=atual;
        atual=(*atual).prox;
        free(tmprr);
    }

}

short int validarusuario(Usuario *topo, char c[]){
    Usuario *atual=topo;
    indiceusuario=0;

    if(c[0]=='\0'||strlen(c)<5){

        return 2; //Retorna 2 caso o nomu de usuário seja muito curto;
    }

    while(atual!=NULL){

        if(strcmp((*atual).user, c)==0){

            return 1; //Retorna 1 caso encontre nomes de usuário iguais;
        }

        indiceusuario++;

        atual=(*atual).prox;
    }
    indiceusuario=-1;

    return 0; //Retorna 0 caso o contrário;

}

short int validaremail(Usuario *topo, char c[]){
    int x=0, y=0;
    while(c[x]!='\0'){
        if(c[x]!='@'){
            y++;
        }
        x++;
    }

    if(x==y){

        return 2; //Retorna 2 caso não haja caractere '@';
    }

    Usuario *atual=topo;

    while(atual!=NULL){
        if(strcmp((*atual).email, c)==0){

            return 1; //Retorna 1 caso encontre endereços de e-mail iguais;
        }

        atual=(*atual).prox;
    }

    return 0; //Retorna 0 caso o contrário;

}

short int validarsenha(Usuario *topo, char c[]){
    Usuario *atual=topo;
    int posicao=0;

    while(atual!=NULL){
        if(strcmp((*atual).senha, c)==0){

            return 1; //Retorna 1 caso encontre senhas iguais;
        }

        atual=(*atual).prox;
    }

    return 0; //Retorna 0 caso o contrário;

}

void limpar_buffer(){
    int c;
    while((c=getchar())!='\n'&&c!=EOF);
}