#include"f_produto.h"

int indiceproduto;

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

void menuinterno(){

    FILE *file1; //Ponteiro para o arquivo de texto dos produtos;
    file1=fopen("Arquivos/produtos.txt", "r+");
    if(file1==NULL){
        perror("[ERRO]");
        exit (1);
    }

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
                    puts("[Digite ENTER para continuar]"); getchar();
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
            produto[indice].ID=0;

            indice++;

            fprintf(file1, "%s. %f\n", nome, preco);
            fflush(file1);

            puts("[CONCLUÍDO] Produto cadastrado!");
            puts("[Digite ENTER para continuar]"); getchar();

            break;

            case 2:
            
            editarproduto(indice, produto, file1);

            break;

            case 3:
            
            puts("[LISTA DE PRODUTOS]");

            for(int i=0; i<indice; i++){

                printf("%i. Nome do produto: %s / Preço: R$%.2f\n", i+1, produto[i].nome, produto[i].preco);

            }
            puts("[Digite ENTER para continuar]"); getchar();
            
            break;

            case 4:

            excluirproduto(&indice, produto, file1);

            break;

            case 5:
            
            puts("[CADASTRAR PRODUTO PARA PROMOÇÃO]\n5.1. Digite o nome do produto:");
            scanf("%49[^\n]", nome); limpar_buffer();
            
            compararproduto(nome, indice, produto);

            if(indiceproduto==-1){

                puts("[ERRO] Produto não encontrado.");
                puts("[Digite ENTER para continuar]"); getchar();
                break;

            }else{

                puts("5.2. Digite o preço desse produto em promoção:");
                scanf("%f", &preco);

                produto[indiceproduto].preco=preco;

                produto[indiceproduto].ID=1;
                puts("[CONCLUIDO] Produto cadastrado para promoção!");
                puts("[Digite ENTER para continuar]"); getchar();

            }
            
            break;

            case 6:
            
            puts("[LISTA DE PRODUTOS EM PROMOÇÃO]");

            for(int i=0, j=1; i<indice; i++){
                if(produto[i].ID==1){
                    printf("%i. Nome: %s / Preço: %.2f\n", j, produto[i].nome, produto[i].preco);
                    j++;
                }
            }
            puts("[Digite ENTER para continuar]"); getchar();
            
            break;

            case 7:

            puts("[REMOVER PRODUTO DA PROMOÇÃO]\n7.1. Digite o nome do produto:");
            scanf("%49[^\n]", nome); limpar_buffer();

            compararproduto(nome, indice, produto);

            if(indiceproduto==-1){

                puts("[ERRO] Produto não encontrado.");
                puts("[Digite ENTER para continuar]"); getchar();
                break;

            }else{

                produto[indiceproduto].ID=0;
                puts("[CONCLUÍDO] Produto removido da promoção.");
                puts("[Digite ENTER para continuar]"); getchar();
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

void editarproduto(int indice, Produto *produto, FILE *file1){
    char nome[50];
    float preco;

    puts("[EDITAR PRODUTO]\n2.1. Digite o nome do produto:");
    scanf("%49[^\n]", nome); limpar_buffer();


    
    if(indiceproduto==-1) {

        puts("[ERRO] Produto não encontrado.");
        puts("[Digite ENTER para continuar]"); getchar();
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

    freopen("Arquivos/produtos.txt", "w", file1);

    for(int i=0; i<indice; i++){
        fprintf(file1, "%s. %.2f %i\n", produto[i].nome, produto[i].preco, produto[i].ID);
    }

    fflush(file1);
}

void excluirproduto(int *indice, Produto *produto, FILE *file1) {
    char nome[50];
    int encontrado = 0;

    printf("[EXCLUIR PRODUTO]\nDigite o nome do produto a ser excluído:\n");
    scanf("%49[^\n]", nome); limpar_buffer();

    for (int i = 0; i < *indice; i++) {
        if (strcmp(produto[i].nome, nome) == 0) {
            encontrado = 1;
            for (int j = i; j < *indice - 1; j++) {
                produto[j] = produto[j + 1];
            }
            (*indice)--;
            break;
        }
    }

    if (!encontrado) {
        printf("[ERRO] Produto '%s' não encontrado.\n", nome);
        return;
    }

    freopen("Arquivos/produtos.txt", "w", file1);
    for (int i = 0; i < *indice; i++) {
        fprintf(file1, "%s. %.2f %i\n", produto[i].nome, produto[i].preco, produto[i].ID);
    }
    fflush(file1);

    printf("[CONCLUÍDO] Produto '%s' excluído com sucesso.\n", nome);
}
