#include <stdio.h>
#include <string.h>
#include "autenticacao.h"
#include "logs.h"


void registrarUsuario()
{
    FILE *arquivo = fopen("../dados/usuarios.csv", "a");

    if(!arquivo)
    {
        printf("Erro ao abrir usuarios.csv\n");
        return;
    }

    Usuario u;

    printf("Crie um login: ");
    fgets(u.login, 20, stdin);
    u.login[strcspn(u.login, "\r\n")] = 0;

    printf("Crie uma senha: ");
    fgets(u.senha, 20, stdin);
    u.senha[strcspn(u.senha, "\r\n")] = 0;

    fprintf(arquivo, "%s;%s\n", u.login, u.senha);
    fclose(arquivo);

    printf("Usuario registrado com sucesso!\n");
}

int autenticarUsuario(char login[], char senha[])
{
    FILE *arquivo = fopen("../dados/usuarios.csv", "r");

    if(!arquivo)
        return 0;

    Usuario u;

    while(fscanf(arquivo, " %19[^;];%19[^\n\r]", u.login, u.senha) == 2)
    {
        u.login[strcspn(u.login, "\r\n")] = 0;
        u.senha[strcspn(u.senha, "\r\n")] = 0;
        if(strcmp(u.login, login) == 0 &&
           strcmp(u.senha, senha) == 0)
        {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}