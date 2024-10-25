#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"cabecalhos\f_usuario.c"

void menuinterno();

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

    }

    short int opcao;

    do{
        puts("[SISTEMA]\n1. Entrar\n2. Cadastre-se\n3. Exibir usuários\n0. Sair");
        scanf("%hi", &opcao); limpar_buffer();

        switch(opcao){
            case 1: //Entrar;

            printf("[ENTRAR]\n1.1. Usuário: ");
            scanf("%49s", user); limpar_buffer();

            if(validarusuario(topo, user)!=1){

                puts("===================================\n[ERRO] Nome de usuário Não encontrado.\n===================================");
                break;

            }

            printf("1.2. Senha: ");
            scanf("%49s", senha); limpar_buffer();

            if(validarsenha(topo, senha, opcao)==0){

                puts("===================================\n[ERRO] Senha inválida.\n===================================");
                break;

            }

            liberarusuarios(topo);
            fclose(file0);

            printf("===================================\nBem vindo %s!\n===================================\n", usuariologado);

            menuinterno();

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

            case 3:

                puts("[EXIBIR USUÁRIOS]");
                exibirusuarios(topo);

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

typedef struct Produto{
    char nome[50];
    float preco;
    int ID; //A variável ID identifica se o produto está em promoção (1) ou não (0);
}Produto;

void menuinterno(){

    FILE *file1; //Ponteiro para o arquivo de texto dos produtos;
    file1=fopen("C:\\Users\\01\\Documents\\Projetos\\AED-UNIII\\Arquivos\\produtos.txt", "r+");

    int indice=0,capacidade=10;

    Produto *produto=(Produto*)malloc(capacidade*sizeof(Produto));

    while(fscanf(file1, "%49[^\n.]. %f %i\n", produto[indice].nome, &produto[indice].preco, &produto[indice].ID)!=EOF){

        printf("%s / %.2f / %i\n", produto[indice].nome, produto[indice].preco, produto[indice].ID);

        if(indice==(capacidade-1)){

            capacidade=capacidade+10;
            produto=(Produto*)realloc(produto, capacidade*sizeof(Produto));

        }

        indice++;
    }

    short int opcao;
    char nome[50]; float preco;

    do{

        printf("[SISTEMA]\n1. Cadastrar novo produto\n");
        printf("2. Editar produto (NOME)\n3. Editar produto (PREÇO)\n");
        printf("4. Exibir produtos (PREÇO CRESCENTE)\n5. Exibir produtos (PREÇO DECRESCENTE)\n");
        printf("6. Cadastrar produto para promoção\n7. Exibir produtos em promoção\n8. Remover produto da promoção\n");
        printf("0. Sair\n");
        scanf("%hi", &opcao); limpar_buffer();

        switch(opcao){
            case 1:

            puts("[CADASTRO DE NOVO PRODUTO]\n1.1. Digite o nome do produto:");
            scanf("%49[^\n]", nome); limpar_buffer();

            puts("1.2. Digite o preço do produto:");
            scanf("%f", &preco); limpar_buffer();

            break;

            case 2: break;
            case 3: break;
            case 4:
            
            puts("[LISTA DE PRODUTOS]\nPreço crescente:\n");

            for(int i=0; i<indice; i++){

                printf("%i. Nome do produto: %s / Preço: R$%.2f\n", i+1, produto[i].nome, produto[i].preco);

            }

            break;

            case 5:
            
            puts("[LISTA DE PRODUTOS]\nPreço decrescente:\n");

            for(int i=(indice-1), j=1; i>=0; i--){
                printf("%i. Nome: %s / Preço: %.2f\n", j, produto[i].nome, produto[i].preco);
            }

            break;
            case 6: break;
            case 7:
            
            puts("[LISTA DE PRODUTOS EM PROMOÇÃO]\n");

            for(int i=0, j=1; i<indice; i++){
                if(produto[i].ID==1){
                    printf("%i. Nome: %s / Preço: %.2f\n", j, produto[i].nome, produto[i].preco);
                    j++;
                }
            }
            
            break;
            case 8: break;
            case 0:

            puts("[SAINDO]");
            
            break;
        }

    }while(opcao!=0);

    free(produto);
    fclose(file1);
}