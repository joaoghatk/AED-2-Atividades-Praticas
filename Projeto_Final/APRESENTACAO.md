# Sistema de Gestão de Autopeças

IMPORTANTE!!!:
INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO > Para que os caminhos (../dados/) que utilizamos no código e os casos de teste funcionem corretamente, o projeto deve ser compilado e executado obrigatoriamente de dentro da pasta implementacao/.
cd implementacao; g++ *.cpp -o programa; Get-Content "../testes/CT0009.txt" -Raw | ./programa.exe

## 1. Introdução

Este projeto consiste no desenvolvimento de um Sistema de Informação para uma Loja de Autopeças, elaborado como Trabalho Prático da disciplina de Algoritmos e Estruturas de Dados II.

O sistema foi implementado na linguagem C, utilizando boas práticas de organização modular, persistência em arquivos CSV e controle de acesso por autenticação de usuários, conforme os requisitos definidos no enunciado da disciplina.

---

## 2. Contexto do Projeto

O sistema foi desenvolvido para auxiliar no controle de estoque de uma loja de autopeças, permitindo o gerenciamento eficiente das peças disponíveis para venda.

A aplicação possibilita:

- Controle de entrada de novos produtos
- Consulta ao estoque
- Atualização de informações
- Exclusão de itens obsoletos
- Registro de auditoria das operações realizadas

---

## 3. Entidade Modelada

A entidade principal do sistema é:

### Peça Automotiva

Cada registro contém os seguintes atributos:

- **ID** (inteiro) – Chave primária e identificador único da peça
- **Nome** (string) – Nome da peça
- **Quantidade** (inteiro) – Quantidade disponível em estoque
- **Preço** (float) – Valor unitário da peça

O campo ID é único e utilizado como chave para pesquisa, edição e exclusão.

---

## 4. Funcionalidades Implementadas (Requisitos Funcionais)

O sistema atende aos seguintes requisitos funcionais:

### RF0001 – Autenticação de Usuário
O sistema solicita login e senha ao iniciar. O acesso ao menu principal só é permitido após autenticação bem-sucedida.

### RF0002 – Menu Principal
Após login válido, o sistema apresenta as opções:

1. Cadastrar novo item
2. Listar registros
3. Pesquisar registro
4. Editar registro
5. Excluir registro
6. Encerrar o programa

### RF0003 – Cadastro de Item
Permite cadastrar uma nova peça no sistema. O ID é validado para evitar duplicidade.

### RF0004 – Listagem de Itens
Exibe todos os registros armazenados, com contador numérico. Também gera uma cópia da listagem no arquivo `saida.csv`.

### RF0005 – Pesquisa por ID
Permite buscar uma peça específica utilizando o ID como chave.

### RF0006 – Edição de Registro
Permite alterar os dados de uma peça existente.

### RF0007 – Exclusão de Registro
Remove permanentemente uma peça do sistema utilizando sua chave (ID).

### RF0008 – Encerramento
Permite ao usuário finalizar o programa, registrando essa ação no arquivo de log.

---

## 5. Requisitos Não Funcionais Atendidos

O sistema atende aos seguintes requisitos técnicos:

- Desenvolvido exclusivamente em linguagem C
- Persistência de dados em arquivos `.csv`
- Estrutura modular utilizando TADs
- Separação em arquivos `.h` e `.cpp`
- Execução via redirecionamento de entrada (`< arquivo.txt`)
- Registro obrigatório de todas as operações no arquivo de logs

---

## 6. Persistência de Dados

Os dados são armazenados nos seguintes arquivos:

- `usuarios.csv` → Armazena login e senha
- `base.csv` → Armazena os registros da entidade
- `logs.csv` → Armazena histórico de operações
- `saida.csv` → Armazena resultados de listagem e pesquisa

Todos os arquivos utilizam o formato CSV com separador `;`.

---

## 7. Auditoria e Controle de Acesso

Todas as ações realizadas no sistema são registradas em `logs.csv`, contendo:

- Identificação do usuário
- Descrição da ação realizada

Isso garante rastreabilidade e conformidade com o requisito de auditoria definido no enunciado.

---

## 8. Estrutura do Projeto

O sistema foi organizado da seguinte forma:

### Implementação

- `programa.cpp` → Arquivo principal
- `dados.h` / `dados.cpp` → Manipulação da entidade e persistência
- `autenticacao.h` / `autenticacao.cpp` → Controle de login
- `logs.h` / `logs.cpp` → Registro de auditoria

### Diretórios

- `dados/` → Arquivos CSV
- `saida/` → Arquivo de saída
- `testes/` → Casos de teste

---

## 9. Casos de Teste

Foram implementados os seguintes testes:

- CT0001 – Login incorreto
- CT0002 – Login correto
- CT0003 – Cadastro válido
- CT0004 – Cadastro com ID duplicado
- CT0005 – Listagem com base preenchida
- CT0006 – Listagem com base vazia
- CT0007 – Pesquisa válida
- CT0008 – Pesquisa inválida
- CT0009 – Exclusão inválida
- CT0010 – Exclusão válida

Os testes foram desenvolvidos de forma a validar todos os requisitos funcionais definidos no enunciado.

---

## 10. Considerações Finais

O sistema implementa integralmente as funcionalidades exigidas, utilizando organização modular, persistência adequada e controle de acesso por autenticação.

A aplicação atende aos critérios de desenvolvimento estabelecidos, garantindo:

- Correção funcional
- Organização estrutural
- Conformidade com os requisitos
- Rastreabilidade das operações

O projeto demonstra a aplicação prática dos conceitos estudados na disciplina de Algoritmos e Estruturas de Dados II.