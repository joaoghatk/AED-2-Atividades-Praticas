#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "dados.h"
#include "logs.h"

void iniciarLista(LISTA *l)
{
    l->qtde = 0;
}

void cadastrarItem(LISTA *l, REGISTRO r, const char* loginUsuario)
{
    FILE *verifica = fopen("../dados/base.csv", "r");

    if(verifica != NULL)
    {
        int idExistente;
        char nomeTemp[30];
        int qTemp;
        float pTemp;

        while(fscanf(verifica,"%d;%[^;];%d;%f\n",
              &idExistente,nomeTemp,&qTemp,&pTemp)==4)
        {
            if(idExistente == r.id)
            {
                printf("Erro: ID ja esta em uso.\n");

                gerarLog(loginUsuario,"Tentou inserir ID duplicado");

                fclose(verifica);
                return; // NÃO INSERE
            }
        }
        fclose(verifica);
    }

    FILE *cadastro = fopen("../dados/base.csv", "a");

    if(cadastro == NULL)
    {
        printf("Nenhum arquivo encontrado ou nenhum arquivo existente!\n");
        return;
    }

    if(l->qtde < TAM2)
    {
        l->registros[l->qtde] = r;
        l->qtde++;

        fprintf(cadastro, "%d;%s;%d;%.2f\n",
                r.id, r.nome, r.quantidade, r.preco);

        char mensagemitem[100];
        sprintf(mensagemitem, " inseriu o novo item: %s", r.nome);
        gerarLog(loginUsuario, mensagemitem);

        printf("Registrado!\n\n");

        fclose(cadastro);
        return;
    }
    else
    {
        printf("Lista cheia!\n");
        fclose(cadastro);
        return;
    }
}
void listarItem(LISTA *l, const char* loginUsuario)
{
    FILE *arquivo = fopen("../dados/base.csv", "r");
    FILE *saida = fopen("../saida/saida.csv", "w");

    if(!arquivo)
    {
        printf("Erro ao abrir base.csv\n");
        return;
    }

    if(!saida)
    {
        printf("Erro ao abrir saida.csv\n");
        fclose(arquivo);
        return;
    }

    int contador = 1;
    REGISTRO r;

    while(fscanf(arquivo,"%d;%[^;];%d;%f\n",
                 &r.id,r.nome,&r.quantidade,&r.preco) == 4)
    {
        printf("%d - [%d] %s (%d) R$ %.2f\n",
               contador, r.id, r.nome,
               r.quantidade, r.preco);

        fprintf(saida,"%d;%s;%d;%.2f\n",
                r.id,r.nome,r.quantidade,r.preco);

        contador++;
    }

    if(contador == 1)
    {
        printf("Nenhum registro encontrado.\n");
    }

    gerarLog(loginUsuario,"Listou os registros");

    fclose(arquivo);
    fclose(saida);
}

void pesquisarItem(const char* loginUsuario)
{
    FILE *arquivo = fopen("../dados/base.csv", "r");
    FILE *saida = fopen("../saida/saida.csv", "w");

    if(!arquivo)
    {
        printf("Erro ao abrir base.csv\n");
        return;
    }

    int idBusca;
    int id, quantidade;
    char nome[30];
    float preco;
    int encontrado = 0;

    printf("Digite o ID para pesquisar: ");
    scanf("%d", &idBusca);

    while(fscanf(arquivo,"%d;%[^;];%d;%f\n",
                 &id,nome,&quantidade,&preco)==4)
    {
        if(id == idBusca)
        {
            printf("Encontrado: %s (%d) R$ %.2f\n",
                    nome, quantidade, preco);

            fprintf(saida,"%d;%s;%d;%.2f\n",
                    id,nome,quantidade,preco);

            encontrado = 1;
        }
    }

    if(!encontrado)
        printf("Registro nao encontrado.\n");

    char mensagem[100];
    sprintf(mensagem,"Pesquisou o ID %d", idBusca);
    gerarLog(loginUsuario,mensagem);

    fclose(arquivo);
    fclose(saida);
}

void editarItem(const char* loginUsuario)
{
    FILE *arquivo = fopen("../dados/base.csv", "r");
    FILE *temp = fopen("../dados/temp.csv", "w");

    if(!arquivo || !temp){
        
        printf("Erro ao abrir arquivos.\n");
        return;    
    }

    int idEditar;
    printf("Digite o ID para editar: ");
    scanf("%d",&idEditar);
    getchar();

    int id, quantidade;
    char nome[30];
    float preco;
    int encontrou = 0;

    while(fscanf(arquivo,"%d;%[^;];%d;%f\n",
                 &id,nome,&quantidade,&preco)==4)
    {
        if(id == idEditar)
        {
            encontrou = 1;

            printf("Novo nome: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome,"\n")] = 0;

            printf("Nova quantidade: ");
            scanf("%d",&quantidade);

            printf("Novo preco: ");
            scanf("%f",&preco);
            getchar();

            char mensagem[100];
            sprintf(mensagem,"Editou o ID %d",idEditar);
            gerarLog(loginUsuario,mensagem);
        }

        fprintf(temp,"%d;%s;%d;%.2f\n",
                id,nome,quantidade,preco);
    }

    fclose(arquivo);
    fclose(temp);

  if(encontrou)
    {
        remove("../dados/base.csv");
        rename("../dados/temp.csv","../dados/base.csv");
        printf("Registro editado com sucesso.\n");
    }
    else
    {
        remove("../dados/temp.csv");
        printf("Registro nao encontrado.\n");

        char mensagem[100];
        sprintf(mensagem,"Tentou editar ID inexistente %d", idEditar);
        gerarLog(loginUsuario, mensagem);
    }
}

void excluirPeca(const char* loginUsuario) {
    FILE *arquivo = fopen("../dados/base.csv", "r");
    if (!arquivo) {
        printf("Arquivo base.csv nao foi encontrado\n");
        return; 
    }

    FILE *temporario = fopen("../dados/temporario.csv", "w");
    if (!temporario) {
        printf("Arquivo temporario nao foi criado\n");
        fclose(arquivo);
        return;
    }

    int codigoexcluir, codigoencontrado, quantidadeencontrada;
    char nomeencontrado[30];
    float precoencontrado;
    int encontrou = 0;

    printf("\nDigite o codigo para excluir a peca: \n");
    scanf("%d", &codigoexcluir);

    while (fscanf(arquivo, "%d;%[^;];%d;%f\n", &codigoencontrado, nomeencontrado, &quantidadeencontrada, &precoencontrado) == 4) { 
        if (codigoencontrado == codigoexcluir) {
            encontrou = 1;
            printf("Sucesso: Peca '%s' removida!\n", nomeencontrado);
            char mensagem[100];
            sprintf(mensagem, "Excluiu a peca codigo %d : %s", codigoexcluir,nomeencontrado);
            gerarLog(loginUsuario, mensagem); 
        } else {
            fprintf(temporario, "%d;%s;%d;%.2f\n", codigoencontrado, nomeencontrado,quantidadeencontrada, precoencontrado);
        }
    }

    fclose(arquivo);
    fclose(temporario);

    remove("../dados/base.csv");
    rename("../dados/temporario.csv", "../dados/base.csv");

    if (!encontrou) {
        printf("Codigo %d nao encontrado.\n", codigoexcluir);
    }
}