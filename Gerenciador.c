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
        printf("1 - Novo chamado\n"); // matheus finalizar -                   1 - Inserir uma Solicita��o de Manuten��o
        printf("2 - Menu de listagem\n"); // lele -                             5 e 6 - Exibir a ordem da realiza��o da manuten��o e Exibir lista
        printf("3 - Consultar chamado\n"); // ju -                             3 - Consultar uma Solicita��o
        printf("4 - Atualizar chamado\n"); //matheus                           4 -  Alterar a prioridade e/ou per�odo de uma Solicita��o
        printf("5 - Excluir chamado\n"); // so -                               2 - Remover uma solicita��o
        printf("0 - Sair\n"); // so -                                          0 - Finaliza
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        system ("cls");

        switch (opcao)
        {
            case 1:
                // Funcao da biblioteca: cadastrar novo chamado
                // Cria um novo registro com codigo, equipamento, prioridade e prazo.
                // Deve chamar a funcao de insercao na lista.
                NovoChamado(lista);
                break;

            case 2:
            {
                // Funcao da biblioteca: listar todos os chamados
                // Exibe os chamados ja cadastrados na estrutura de dados.
                // Um sub menu para qual tipo de listagem o usuario deseja ver.
                int subOpcao;
                do
                {
                    system ("cls");
                    printf("\n===== MENU DE LISTAGEM =====\n");
                    printf("1 - Exibir todas as solicitacoes cadastradas \n");
                    printf("2 - Exibir ordem de realizacao da manutencao (por urgencia)\n");
                    printf("0 - Voltar ao menu principal\n");
                    printf("Escolha uma opcao: ");

                    scanf("%d", &subOpcao);
                    getchar(); // Limpa o enter do buffer

                    if (subOpcao == 1)
                    {
                        ExibirListaGeral(lista, "===== LISTA GERAL DE SOLICITACOES =====");
                    }
                    else if (subOpcao == 2)
                    {
                        exibirOrdemManutencao(lista);
                    }
                }while (subOpcao != 0);
            break;
            }

            case 3:
                // Funcao da biblioteca: buscar chamado
                // Pesquisa um chamado pelo codigo do equipamento ou codigo da solicitacao.
                // Deve retornar as informacoes do registro encontrado.
                ConsultarChamado(lista);
                break;

            case 4:
                // Funcao da biblioteca: atualizar chamado
                //Dado o c�digo de solicita��o o usu�rio pode alterar a prioridade e o per�odo dela,
                //respeitando os limites do per�odo associado a nova prioridade.
                // EXTRA: Permite alterar prioridade, prazo, nome do equipamento ou status.
                AlterarPrioridade(lista);
                system("pause");
                break;

            case 5:
                // Funcao da biblioteca: excluir chamado
                // Remove o chamado da lista de manutencao.
                // Pode ser por codigo da solicitacao.
                int excluir;
                do
                {
                     if(verificaVazia(lista))
                {
                    printf("\n Lista vazia, impossivel prosseguir!\n");
                    system("pause");
                    break;
                }
                    ExcluirChamado(lista);
                    system ("cls");
                    printf("\n Deseja excluir mais algum chamado?\n 1 - SIM \n 2 - NAO \n Resposta:");
                    scanf("%d", &excluir);
                }while(excluir==1);
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
