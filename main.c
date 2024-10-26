#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"cabecalhos\f_usuario.c"
#include"cabecalhos\f_produto.c"

int main(){
    setlocale(LC_ALL, "portuguese");

    Usuario *topo=NULL;
    char nome[50], user[50], email[50], senha[50];

    FILE *file0; //Ponteiro para o arquivo de texto dos usuários;
    file0=fopen("Arquivos/usuarios.txt", "a+");
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
                puts("[Digite ENTER para continuar]"); getchar();
                break;

            }

            printf("1.2. Senha: ");
            scanf("%49s", senha); limpar_buffer();

            if(validarsenha(topo, senha, opcao)==0){

                puts("===================================\n[ERRO] Senha inválida.\n===================================");
                puts("[Digite ENTER para continuar]"); getchar();
                break;

            }

            liberarusuarios(topo);
            fclose(file0);

            printf("===================================\nBem vindo %s!\n===================================\n", usuariologado);

            puts("[Digite ENTER para continuar]"); getchar();

            menuinterno();

            break;

            case 2: //Cadastro;

            puts("[CADASTRO]\n2.1. Digite o seu nome completo:");
            scanf("%49[^\n]", nome); limpar_buffer();

            for(int i=0; nome[i]!='\0'; i++){

                if(nome[i]=='.'){

                    puts("[ERRO] Caractere '.' não permitido.");
                    puts("[Digite ENTER para continuar]"); getchar();

                    break;
                }
            }

            puts("2.2. Crie um nome de usuário:");
            scanf("%49s", user); limpar_buffer();

            if(validarusuario(topo, user)==1){

                puts("===================================\n[ERRO] Nome de usuário não disponível.\n===================================");
                puts("[Digite ENTER para continuar]"); getchar();
                break;

            }else if(validarusuario(topo, user)==2){

                puts("===================================\n[ERRO] Nome de usuário muito curto.\n===================================");
                puts("[Digite ENTER para continuar]"); getchar();
                break;

            }

            puts("2.3. Digite o seu endereço de e-mail:");
            scanf("%49s", email); limpar_buffer();

            if(validaremail(topo, email)==1){

                puts("===================================\n[ERRO] Endereço de e-mail não disponível.\n===================================");
                puts("[Digite ENTER para continuar]"); getchar();
                break;

            }else if(validaremail(topo, email)==2){

                puts("===================================\n[ERRO] Ausência de caractere '@'.\n===================================");
                puts("[Digite ENTER para continuar]"); getchar();
                break;

            }

            puts("[CADASTRO]\n2.4. Crie uma senha:");
            scanf("%49s", senha); limpar_buffer();

            fprintf(file0, "%s. %s %s %s\n", nome, user, email, senha);
            inserirusuario(&topo, nome, user, email, senha);
            fflush(file0);

            puts("[CONCLÚIDO] Usuário cadastrado!");
            puts("[Digite ENTER para continuar]"); getchar();

            break;

            case 3:

                puts("[EXIBIR USUÁRIOS]");
                exibirusuarios(topo);
                puts("[Digite ENTER para continuar]"); getchar();

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