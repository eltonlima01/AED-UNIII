#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"f_usuario.h"

Usuario* novousuario(char s1[], char s2[], char s3[], char s4[]){
    Usuario *u=(Usuario*)malloc(sizeof(Usuario));

    strcpy((*u).nome, s1); strcpy((*u).user, s2);
    strcpy((*u).email, s3); strcpy((*u).senha, s4);
    (*u).prox=NULL;

    return u;
}

int indiceusuario; char usuariologado[50];

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

short int validarsenha(Usuario *topo, char c[], short int si){
    Usuario *atual=topo;
    int posicao=0;

    if(si!=1){

    while(atual!=NULL){
        if(strcmp((*atual).senha, c)==0){

            return 1; //Retorna 1 caso encontre senhas iguais;
        }

        atual=(*atual).prox;
    }

    return 0; //Retorna 0 caso contrário;

    }else{

        while((atual!=NULL) && (posicao<indiceusuario)){

            atual=(*atual).prox;
            posicao++;

        }

        if((atual!=NULL) && (strcmp((*atual).senha, c)==0)){

            strcpy(usuariologado, (*atual).nome);

            return 1; //Validação bem sucedida de senha;
        }

        return 0; //Caso contrário;
   
    }


}

void exibirusuarios(Usuario *topo){

    Usuario *atual=topo;

    while(atual!=NULL){

        printf("Nome: %s / E-mail: %s\n", (*atual).nome, (*atual).email);
        atual=(*atual).prox;

    }
}

void limpar_buffer(){
    int c;
    while((c=getchar())!='\n'&&c!=EOF);
}