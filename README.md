# Projeto: Gerenciador de Manutenção de Equipamentos de um Laboratório

Sistema desenvolvido em linguagem C para administrar dinamicamente as solicitações de manutenção corretiva e preventiva de equipamentos de um laboratório de sistemas embarcados e automação.

O programa permite cadastrar, consultar, listar, atualizar e excluir chamados relacionados a falhas ou demandas de manutenção, organizando-os por prioridade e período para facilitar a execução das ações de manutenção.

## Funcionalidades

- Cadastro de chamados de manutenção;
- Validação de código da solicitação e do equipamento;
- Consulta de chamados por código;
- Listagem geral dos chamados cadastrados;
- Ordenação por urgência (prioridade, prazo e código);
- Atualização de prioridade e período do chamado;
- Exclusão de chamados da lista;
- Organização da fila de manutenção com prioridade de execução.

## Estrutura do projeto

- `Gerenciador.c` — menu principal e fluxo do programa;
- `funcoes.h` — estrutura de dados, funções de cadastro, consulta, ordenação e exclusão;

## Requisitos

- Compilador C compatível com o padrão C99;
- Ambiente Windows para a versão atual, pois o código utiliza `windows.h`;
- Terminal/Prompt de comando.

## Como compilar

No Windows, com GCC/MinGW instalado, execute:

```bash
gcc Gerenciador.c -o Gerenciador
```

Em seguida, execute:

```bash
Gerenciador.exe
```

## Como usar

Ao iniciar o programa, o usuário visualiza um menu principal com as seguintes opções:

1. Novo chamado
2. Menu de listagem
3. Consultar chamado
4. Atualizar prioridade do chamado
5. Excluir chamado
0. Sair

### Cadastro de chamado

- Informe o código da solicitação (4 dígitos);
- Digite o código do equipamento no formato `ABC123`;
- Insira o nome do equipamento;
- Defina a prioridade (1, 2 ou 3);
- Informe o período de indisponibilidade em dias, respeitando o limite da prioridade.

### Listagem

A aplicação oferece:

- listagem geral dos chamados;
- ordem de realização da manutenção por urgência.

### Consulta e atualização

O sistema permite buscar um chamado por código e também alterar a prioridade e o prazo da manutenção.

### Exclusão

É possível excluir um chamado informado diretamente por código, com confirmação antes da remoção.

## Observações

- A prioridade 1 representa maior urgência;
- O período máximo varia conforme a prioridade:
  - 1: até 7 dias;
  - 2: até 15 dias;
  - 3: até 20 dias;
- O programa mantém os chamados em uma lista encadeada, ordenada conforme regras internas de cadastro e urgência.

## Licença

Este projeto é destinado ao uso acadêmico e de estudo, sendo livre para adaptação e melhoria conforme necessidade do usuário ou da instituição.

## Contribuição

Sinta-se à vontade para abrir melhorias, corrigir bugs ou adaptar o sistema para novas regras de manutenção e gestão de laboratórios.
