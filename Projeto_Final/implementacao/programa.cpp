#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dados.h"
#include "logs.h"
#include "autenticacao.h"

int main() {

    char login[TAM];
    char senha[TAM];
    int autenticado = 0;

    int opcaoInicial;

    printf("1 - Registrar novo usuario\n");
    printf("2 - Fazer login\n");
    if (scanf("%d", &opcaoInicial) != 1) {
        return 0; 
    }
    while (getchar() != '\n');

    if(opcaoInicial == 1)
    {
        registrarUsuario(); 
    }
    printf("%d\n", opcaoInicial);

    // LOOP DE LOGIN (RF0001)
    do {
        printf("Login: \n");
        fgets(login, 20, stdin) ;
        login[strcspn(login, "\r\n")] = 0;
        printf("%s\n", login);

        printf("Senha: \n");
        fgets(senha, 20, stdin);
        senha[strcspn(senha, "\r\n")] = 0;
        printf("%s\n", senha);

        if (autenticarUsuario(login, senha)) 
        {
            printf("\nLogin realizado com sucesso!\n");

            gerarLog(login,"realizou o login com sucesso");

            autenticado = 1;
        }
        else
        {
            printf("\nLogin ou senha incorretos.\n\n");
            
            gerarLog(login,"falhou ao realizar o login, dados incorretos");
        }

    } while (!autenticado);

    LISTA autopecas;
    REGISTRO item;
    iniciarLista(&autopecas);

    while(true)
    {
        int opcao;

        printf("\n - MENU PRINCIPAL -\n");
        printf("1 - Cadastrar novo item\n");
        printf("2 - Listar registros\n");
        printf("3 - Pesquisar registro\n");
        printf("4 - Editar registro\n");
        printf("5 - Excluir registro\n");
        printf("6 - Encerrar o programa\n");
        printf("Escolha: ");

        scanf("%d", &opcao);
        printf("%d\n", opcao);
        while (getchar() != '\n');

        switch (opcao)
        {
            case 1:
                printf("ID: ");
                scanf("%d", &item.id);
                printf("%d\n", item.id);
                getchar();

                printf("PRODUTO: ");
                scanf("%29[^\n]", item.nome);
                printf("%s\n", item.nome);

                printf("QUANTIDADE: ");
                scanf("%d", &item.quantidade);
                printf("%d\n", item.quantidade);

                printf("PREÇO: ");
                scanf("%f", &item.preco);
                printf("%.2f\n", item.preco);
                getchar();

                cadastrarItem(&autopecas, item, login);
                break;

            case 2:
                listarItem(&autopecas, login);
                break;

            case 3:
                pesquisarItem(login);
                break;

            case 4:
                editarItem(login);
                break;

            case 5:
                excluirPeca(login);
                break;

            case 6:
                printf("Saindo...\n");
                gerarLog(login,"saiu do programa");
                return 0;

            default:
                printf("Opcao invalida.\n");
        }
    }

    return 0;
}