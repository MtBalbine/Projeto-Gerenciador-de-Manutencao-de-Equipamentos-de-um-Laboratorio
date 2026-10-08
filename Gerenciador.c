#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoes.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao = 0;

    do
    {
        printf("\n===== GERENCIADOR DE MANUTENCAO =====\n");
        printf("1 - Novo chamado\n");
        printf("2 - Listar chamados\n");
        printf("3 - Buscar chamado\n");
        printf("4 - Atualizar chamado\n");
        printf("5 - Excluir chamado\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
            case 1:
                // Funcao da biblioteca: cadastrar novo chamado
                // Cria um novo registro com codigo, equipamento, prioridade e prazo.
                // Deve chamar a funcao de insercao na lista.
                break;

            case 2:
                // Funcao da biblioteca: listar todos os chamados
                // Exibe os chamados ja cadastrados na estrutura de dados.
                // Pode ordenar por prioridade, codigo ou data de cadastro.
                break;

            case 3:
                // Funcao da biblioteca: buscar chamado
                // Pesquisa um chamado pelo codigo do equipamento ou codigo da solicitacao.
                // Deve retornar as informacoes do registro encontrado.
                break;

            case 4:
                // Funcao da biblioteca: atualizar chamado
                // Permite alterar prioridade, prazo, nome do equipamento ou status.
                // Deve buscar o registro antes de modificar.
                break;

            case 5:
                // Funcao da biblioteca: excluir chamado
                // Remove o chamado da lista de manutencao.
                // Pode ser por codigo da solicitacao ou codigo do equipamento.
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    
    system("pause");
    return 0;
}