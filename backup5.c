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

            for(int i=0; nome[i]!='\0'; i++){

                if(nome[i]=='.'){

                    puts("[ERRO] Caractere '.' não permitido.");

                    break;
                }
            }

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

int indiceproduto;

typedef struct Produto{
    char nome[50];
    float preco;
    int ID; //A variável ID identifica se o produto está em promoção (1) ou não (0);
}Produto;

void editarproduto(int indice, Produto *produto, FILE *file1);
void compararproduto(char s[], int indice, Produto *p);

void menuinterno(){

    FILE *file1; //Ponteiro para o arquivo de texto dos produtos;
    file1=fopen("C:\\Users\\01\\Documents\\Projetos\\AED-UNIII\\Arquivos\\produtos.txt", "r+");

    int indice=0,capacidade=10; //Índice de quantidade ativa de produtos, e Capacidade de produtos máximos;

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

        printf("[SISTEMA]\n1. Cadastrar novo produto\n2. Editar produto\n3. Exibir produtos\n4. Excluir produto\n");
        printf("5. Cadastrar produto para promoção\n6. Exibir produtos em promoção\n7. Remover produto da promoção\n");
        printf("0. Sair\n");
        scanf("%hi", &opcao); limpar_buffer();

        switch(opcao){
            case 1:

            puts("[CADASTRO DE NOVO PRODUTO]\n1.1. Digite o nome do produto:");
            scanf("%49[^\n]", nome); limpar_buffer();

            for(int i=0; nome[i]!='\0'; i++){

                if(nome[i]=='.'){

                    puts("[ERRO] Caractere '.' não permitido.");
                    break;

                }
            }

            puts("1.2. Digite o preço do produto:");
            scanf("%f", &preco); limpar_buffer();


            if(indice==(capacidade-1)){

                capacidade=capacidade+10;
                produto=(Produto*)realloc(produto, capacidade*sizeof(Produto));

            }

            strcpy(produto[indice].nome, nome);
            produto[indice].preco=preco;

            indice++;

            fprintf(file1, "%s. %f\n", nome, preco);
            fflush(file1);

            break;

            case 2:
            
            puts("[EDITAR PRODUTO]\n2.1. Digite o nome do produto:");
            scanf("%49[^\n]", nome); limpar_buffer();

            editarproduto(indice, produto, file1);

            break;

            case 3: break;

            case 4:
            
            puts("[LISTA DE PRODUTOS]");

            for(int i=0; i<indice; i++){

                printf("%i. Nome do produto: %s / Preço: R$%.2f\n", i+1, produto[i].nome, produto[i].preco);

            }

            break;

            case 5:
            
            puts("[CADASTRAR PRODUTO PARA PROMOÇÃO]\n5.1. Digite o nome do produto:");
            scanf("%49[^\n]", nome); limpar_buffer();
            
            compararproduto(nome, indice, produto);

            if(indiceproduto==-1){

                puts("[ERRO] Produto não encontrado.");
                break;

            }else{

                produto[indice].ID=1;
                puts("[CONCLÚIDO] Produto cadastrado para promoção!");

            }
            
            break;
            case 6:
            
            puts("[LISTA DE PRODUTOS EM PROMOÇÃO]\n");

            for(int i=0, j=1; i<indice; i++){
                if(produto[i].ID==1){
                    printf("%i. Nome: %s / Preço: %.2f\n", j, produto[i].nome, produto[i].preco);
                    j++;
                }
            }
            
            break;

            case 7:

            puts("[REMOVER PRODUTO DA PROMOÇÃO]\n7.1. Digite o nome do produto:");
            scanf("%49[^\n]", nome); limpar_buffer();

            compararproduto(nome, indice, produto);

            if(indiceproduto==-1){

                puts("[ERRO] Produto não encontrado.");
                break;

            }else{

                produto[indiceproduto].ID=0;
                puts("[CONCLUÍDO] Produto removido da promoção.");
            }
            break;

            case 0:

            puts("[SAINDO]");
            
            break;
        }

    }while(opcao!=0);

    free(produto);
    fclose(file1);
}

void compararproduto(char s[], int indice, Produto *p){

    indiceproduto=0;

    int j;

    for(j=0; j<indice; j++){
        if(strcmp(p[j].nome, s)==0){

            indiceproduto=j; //Essa função iguala indiceproduto ao índice do usuário com o nome desejado;

            break;
        }
    }

    if(j==indice){

        indiceproduto=-1; //indiceproduto é -1 caso não encontre produtos com nomes iguais;

    }
}

void editarproduto(int indice, Produto *produto, FILE *file1){
    char nome[50];
    float preco;

    puts("[EDITAR PRODUTO]\n2.1. Digite o nome do produto:");
    scanf("%49[^\n]", nome); limpar_buffer();


    
    if(indiceproduto==-1) {

        puts("[ERRO] Produto não encontrado.");
        return;

    }

    compararproduto(nome, indice, produto);

    printf("[EDITAR PRODUTO] Produto encontrado: %s / R$%.2f\n", produto[indiceproduto].nome, produto[indiceproduto].preco);

    printf("Digite o novo nome do produto (ou deixe em branco para não alterar):\n");
    fgets(nome, sizeof(nome), stdin); limpar_buffer();

    if(strlen(nome)>1){

        nome[strcspn(nome, "\n")] = '\0';
        strcpy(produto[indiceproduto].nome, nome);

    }

    printf("Digite o novo preço do produto (ou -1 para não alterar):\n");
    scanf("%f", &preco); limpar_buffer();
    if(preco>=0) {
        produto[indiceproduto].preco=preco;
    }

    freopen("C:\\Users\\01\\Documents\\Projetos\\AED-UNIII\\Arquivos\\produtos.txt", "w", file1);

    for(int i=0; i<indice; i++){
        fprintf(file1, "%s. %.2f %i\n", produto[i].nome, produto[i].preco, produto[i].ID);
    }

    fflush(file1);
}
