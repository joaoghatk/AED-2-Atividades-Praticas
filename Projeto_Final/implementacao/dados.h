#ifndef DADOS_H
#define DADOS_H

#define TAM 20
#define TAM2 100
#define TAM3 30

typedef struct
{
    int id;
    char nome[TAM3];
    int quantidade;
    float preco;
} REGISTRO;

typedef struct
{
    REGISTRO registros[TAM2];
    int qtde;
} LISTA;

typedef struct {
    char login[TAM];
    char senha[TAM];
}Usuario;

void registrarUsuario(Usuario *u);
void iniciarLista(LISTA *l);
void logss(char *usuario, char *acao);
void cadastrarItem(LISTA *l, REGISTRO r, const char* loginUsuario);
void listarItem(LISTA *l, const char* loginUsuario);
void pesquisarItem(const char* loginUsuario);
void editarItem(const char* loginUsuario);
void excluirPeca(const char* loginUsuario);
int autenticar(Usuario u, char login[], char senha[]);

#endif
