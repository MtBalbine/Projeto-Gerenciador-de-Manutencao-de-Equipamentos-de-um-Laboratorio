#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoes.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao = 0;
    int codBusca;
    Chamados* lista  = InicializaListaChamado();

    do
    {
        printf("\n===== GERENCIADOR DE MANUTENCAO =====\n");
        printf("1 - Inserir uma Solicitacao de Manutencao\n");
        printf("2 - Remover uma Solicitacao\n");
        printf("3 - Consultar uma Solicitacao\n");
        printf("4 - Alterar a prioridade e/ou periodo de uma Solicitacao\n");
        printf("5 - Exibir a ordem de realizacao da manutencao\n");
        printf("6 - Exibir todas as solicitacoes\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        printf("Escolha uma opcao:");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
            case 1:
                // Funcao da biblioteca: cadastrar novo chamado
                // Cria um novo registro com codigo, equipamento, prioridade e prazo.
                // Deve chamar a funcao de insercao na lista.
                NovoChamado(lista);
                break;

            case 2:
                // Funcao da biblioteca: listar todos os chamados
                // Exibe os chamados ja cadastrados na estrutura de dados.
                // Pode ordenar por prioridade, codigo ou data de cadastro.
                printf("\n Digite o codigo da solicitacao a remover: ");
                scanf("%d", &codBusca);
                RemoverChamado(lista, codBusca);
                system("pause");
                break;

            case 3:
                // Funcao da biblioteca: buscar chamado
                // Pesquisa um chamado pelo codigo da solicitacao.
                // Deve retornar as informacoes do registro encontrado.
                printf("\n Digite o codigo de solicitacao a consultar: ");
                scanf("%d", &codBusca);
                ConsultarChamado(lista, codBusca);
                system("pause");
                break;

            case 4:
                // Funcao da biblioteca: atualizar chamado
                // Permite alterar prioridade ou prazo.
                // Deve buscar o registro antes de modificar.
                printf("\n Digite o codigo de solicitacao a alterar: ");
                scanf("%d", &codBusca);
               // AlterarChamado(lista, codBusca);
                system("pause");
                break;

            case 5:
                // Funcao da biblioteca: excluir chamado
                // Remove o chamado da lista de manutencao.
                // Pode ser por codigo da solicitacao ou codigo do equipamento.
                //ExibirOrdemManutencao(lista);
                system("pause");
                break;

            case 6:
                //ExibirTodasSolicitacoes(lista);
                system("pause");
                break;

            case 0:

                printf("\n Liberando memoria e encerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                system("pause");
                break;
        }

    }
    while (opcao != 0);

    return 0;
}
