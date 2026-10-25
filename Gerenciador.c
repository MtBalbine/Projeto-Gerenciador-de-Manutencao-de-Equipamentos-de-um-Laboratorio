#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "funcoes.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int opcao = 0;

    Lista* L  = InicializaListaChamado();

    do
    {
        system ("cls");

        printf("\n===== GERENCIADOR DE MANUTENCAO =====\n");
        printf("1 - Novo chamado\n"); //                                 1 - Inserir uma Solicitação de Manutenção
        printf("2 - Menu de listagem\n"); //                             5 e 6 - Exibir a ordem da realizaçao da manutenção e Exibir lista
        printf("3 - Consultar chamado\n"); //                            3 - Consultar uma Solicitação
        printf("4 - Atualizar prioridade do chamado\n"); //              4 -  Alterar a prioridade e/ou período de uma Solicitação
        printf("5 - Excluir chamado\n"); //                              2 - Remover uma solicitação
        printf("0 - Sair\n"); //                                         0 - Finaliza
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        system ("cls");

        switch (opcao)
        {
            case 1:
                // Função da biblioteca: cadastrar novo chamado
                // Cria um novo registro com código, equipamento, prioridade e prazo.
                // Deve chamar a função de inserção na lista.
                NovoChamado(L);
                break;

            case 2:
            {
                // Função da biblioteca: listar todos os chamados
                // Exibe os chamados já cadastrados na estrutura de dados.
                // Um sub menu para qual tipo de listagem o usuário deseja ver.
                int subOpcao;
                do
                {
                    system ("cls");
                    printf("\n===== MENU DE LISTAGEM =====\n");
                    printf("1 - Exibir todas as solicitações cadastradas \n");
                    printf("2 - Exibir ordem de realização da manutenção (por urgência)\n");
                    printf("0 - Voltar ao menu principal\n");
                    printf("Escolha uma opção: ");

                    scanf("%d", &subOpcao);
                    getchar(); // Limpa o enter do buffer

                    if (subOpcao == 1)
                    {
                        ExibirListaGeral(L, "===== LISTA GERAL DE SOLICITAÇÕES =====");
                    }
                    else if (subOpcao == 2)
                    {
                        exibirOrdemManutencao(L);
                    }
                    system("pause");
                }while (subOpcao != 0);
            break;
            }

            case 3:
                // Funcao da biblioteca: buscar chamado
                // Pesquisa um chamado pelo codigo do equipamento ou codigo da solicitacao.
                // Deve retornar as informacoes do registro encontrado.
                ConsultarChamado(L);
                break;

            case 4:
                // Função da biblioteca: atualizar chamado
                //Dado o código de solicitação o usuário pode alterar a prioridade e o período dela,
                //respeitando os limites do período associado a nova prioridade.
                // EXTRA: Permite alterar prioridade, prazo, nome do equipamento ou status.
                AlterarPrioridade(L);
                system("pause");
                break;

            case 5:
                // Função da biblioteca: excluir chamado
                // Remove o chamado da lista de manutenção.
                // Pode ser por código da solicitação.
                int excluir;
                do
                {
                     if(verificaVazia(L))
                {
                    printf("\n Lista vazia, impossível prosseguir!\n");
                    system("pause");
                    break;
                }
                    ExcluirChamado(L);
                    system ("cls");
                    printf("\n Deseja excluir mais algum chamado?\n 1 - SIM \n 2 - NÃO \n Resposta:");
                    scanf("%d", &excluir);
                }while(excluir==1);
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                LimparListaChamados(L);
                break;

            default:
                printf("\n Opção inválida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);


    system("pause");
    return 0;
}
