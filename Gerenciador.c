#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoes.h"

int main()
{
    setlocale(LC_ALL, "portuguese");

    int opcao = 0;

    Chamados* lista  = InicializaListaChamado();

    do
    {
        system ("cls");

        printf("\n===== GERENCIADOR DE MANUTENCAO =====\n");
        printf("1 - Novo chamado\n"); // matheus finalizar -                   1 - Inserir uma Solicitação de Manutenção
        printf("2 - Listar chamados\n"); // lele -                             5 e 6 - Exibir a ordem da realização da manutenção e Exibir lista
        printf("3 - Consultar chamado\n"); // ju -                             3 - Consultar uma Solicitação
        printf("4 - Atualizar chamado\n"); //matheus                           4 -  Alterar a prioridade e/ou período de uma Solicitação
        printf("5 - Excluir chamado\n"); // so -                               2 - Remover uma solicitação
        printf("0 - Sair\n"); // so -                                          0 - Finaliza
        printf("Escolha uma opcao: ");
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
                break;

            case 3:
                // Funcao da biblioteca: buscar chamado
                // Pesquisa um chamado pelo codigo do equipamento ou codigo da solicitacao.
                // Deve retornar as informacoes do registro encontrado.
                break;


            case 4:
                // Funcao da biblioteca: atualizar chamado
                //Dado o código de solicitação o usuário pode alterar a prioridade e o período dela,
                //respeitando os limites do período associado a nova prioridade.
                // EXTRA: Permite alterar prioridade, prazo, nome do equipamento ou status.
                break;

            case 6:
                // Funcao da biblioteca: excluir chamado
                // Remove o chamado da lista de manutencao.
                // Pode ser por codigo da solicitacao ou codigo do equipamento.
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                LimparListaChamados(lista);
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);


    system("pause");
    return 0;
}
