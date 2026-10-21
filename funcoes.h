#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include <ctype.h> // Biblioteca para funções de manipulação de caracteres
#include <string.h> // Biblioteca para funções de manipulação de strings
#include <stdio.h>
#include <stdlib.h>

/*
    Funções de Manipulação de Lista:
    - InicializaListaChamado        alocam uma lista vazia.
    - CriaChamado                   aloca e preenche um nó.
    - CodigoSolicitacaoExiste       percorre a lista para localizar um código.
    - InsereChamadoOrdenado         insere o novo nó na posição correta pelo código.
    - NovoChamado                   coleta e valida os dados antes de inserir.

    Funções auxiliares do cadastro:
    - QuantCod                      conta os dígitos do código da solicitação.
    - LerCodigoEquipamento          valida o formato do código do equipamento.
*/
    typedef struct dados
{

     /*
        Codigo da solicitação: (int 4 caracteres)

        Código do Equipamento: (string 3 caracteres; 3 numeros)

        Nome do equipamento: (string - 20 caracteres (MAX))

        Prioridade: (int de 1 a 3)

        Período: (int)

        */
    int codigoSolicitacao;
    char codigoEquipamento[7];// uma casa a mais para "\0"
    char nomeEquipamento[21];// uma casa a mais para "\0"
    int prioridade;
    int periodo;
    struct dados *prox;
}Dados;

typedef struct chamados
{
   Dados *inicio;
}Chamados;



/*
    Descrição: Cria e inicializa uma lista vazia de chamados.
    Entrada: Nenhuma.
    Saída: Ponteiro para a lista vazia criada.
*/
Chamados* InicializaListaChamado()
{
    Chamados *aux = (Chamados*)malloc(sizeof(Chamados));
    aux->inicio = NULL;
    return aux;
}

/*
    Descrição: Conta a quantidade de dígitos de um código de solicitação.
    Entrada: Número inteiro representando o código da solicitação.
    Saída: Quantidade de dígitos do valor informado.
*/
int QuantCod(int v)
{
    int cont=0;

    while(v>0)
    {
        v=v/10;
        cont++;
    }
    return cont;
}

/*
    Descrição: Verifica se a lista de chamados está vazia.
    Entrada: Ponteiro para a lista de chamados.
    Saída: Retorna 1 se a lista estiver vazia e 0 se não estiver.
*/
int verificaVazia(Chamados *l)
{
    if (l->inicio== NULL)
    {
        return 1;
    }
    return 0;
}


//Case 1 - Cria chamado

/*
    Descrição: Valida e lê o código do equipamento no formato de 3 letras e 3 números.
    Entrada: Vetor de caracteres que receberá o código do equipamento.
    Saída: Retorna 1 se o código for válido e 0 se for inválido.
*/
int LerCodigoEquipamento(char codigo[])
{
    int caractere = getchar();
    int tamanho = 0;
    int valido = 1;

    // Se o primeiro caractere lido for uma nova linha, lê o próximo caractere.
    if (caractere == '\n')
    {
        caractere = getchar();
    }

    // Lê os caracteres até encontrar EOF ou uma nova linha.
    while (caractere != EOF && caractere != '\n')
    {
        if (tamanho < 6) // Verifica se ainda não atingiu o tamanho máximo do código (6 caracteres)
        {
            if (tamanho < 3) // Para os três primeiros caracteres, espera-se letras
            {
                if (isalpha((unsigned char)caractere))
                {
                    codigo[tamanho] = (char)toupper((unsigned char)caractere); // unsigned char = positivo, toupper = converte para maiúscula,
                }
                else
                {
                    codigo[tamanho] = (char)caractere; // char = converte para caractere, caso não seja letra, mantém o caractere original
                    valido = 0;
                }
            }
            else
            {
                codigo[tamanho] = (char)caractere; // Para os três últimos caracteres, espera-se números
                if (!isdigit((unsigned char)caractere)) // unsigned char = positivo, isdigit = verifica se é dígito
                {
                    valido = 0;
                }
            }
        }
        else
        {
            valido = 0;
        }

        tamanho++;
        caractere = getchar();
    }

    codigo[6] = '\0';
    return valido && tamanho == 6;
}


/*
    Descrição: Cria e preenche um novo nó da lista de chamados com os dados informados.
    Entrada: Ponteiro para o próximo nó, código da solicitação, código do equipamento, nome do equipamento, prioridade e período.
    Saída: Ponteiro para o novo nó criado.
*/
Dados* CriaChamado(Dados* proximo, int soli, char codigoEquipamento[], char nomeEquipamento[], int prioridade, int periodo)
{
    Dados* aux = (Dados*)malloc(sizeof(Dados));
    aux->codigoSolicitacao=soli;
    // Copia o código do equipamento para o novo nó, incluindo o terminador da string.
    int i = 0;
    while (codigoEquipamento[i] != '\0')
    {
        aux->codigoEquipamento[i] = codigoEquipamento[i];
        i++;
    }
    aux->codigoEquipamento[i] = '\0';

    // Copia o nome do equipamento para o novo nó, incluindo o terminador da string.
    i = 0;
    while (nomeEquipamento[i] != '\0')
    {
        aux->nomeEquipamento[i] = nomeEquipamento[i];
        i++;
    }
    aux->nomeEquipamento[i] = '\0';

    aux->prioridade=prioridade;
    aux->periodo=periodo;

    aux->prox=proximo;
    return aux;
}

/*
    Descrição: Verifica se um código de solicitação já existe na lista.
    Entrada: Ponteiro para a lista de chamados e código a ser pesquisado.
    Saída: Retorna 1 se o código existir e 0 se não existir.
*/
int CodigoSolicitacaoExiste(Chamados *lista, int codigo)
{
    Dados *atual = lista->inicio;

    while (atual != NULL)
    {
        if (atual->codigoSolicitacao == codigo)
        {
            return 1;
        }
        atual = atual->prox;
    }

    return 0;
}

/*
    Descrição: Insere um novo chamado na lista em ordem crescente de código de solicitação.
    Entrada: Ponteiro para a lista, código da solicitação, código do equipamento, nome, prioridade e período.
    Saída: Nenhuma.
*/
void InsereChamadoOrdenado(Chamados *lista, int soli, char codigoEquipamento[], char nomeEquipamento[], int prioridade, int periodo)
{
    Dados *anterior = NULL;
    Dados *atual = lista->inicio;

    while (atual != NULL && atual->codigoSolicitacao < soli)
    {
        anterior = atual;
        atual = atual->prox;
    }

    Dados *novo = CriaChamado(atual, soli, codigoEquipamento, nomeEquipamento, prioridade, periodo);
    if (anterior == NULL)
    {
        lista->inicio = novo;
    }
    else
    {
        anterior->prox = novo;
    }
}



/*
    Descrição: Coleta e valida os dados de um novo chamado e o insere na lista.
    Entrada: Ponteiro para a lista de chamados.
    Saída: Nenhuma, porém exibe mensagens ao usuário e cadastra o chamado.
*/
void NovoChamado(Chamados *anterior) // Função para cadastrar um novo chamado
{
    int codSolic, prioridade, prazo;
    char codEquip[7];
    char nomeEquip[21];

    // Solicita o código da solicitação e exige que ele tenha quatro dígitos.
    printf("\n Formato do codigo do chamado: 4 digitos (ex: 1234)");
    printf("\n Codigo do chamado: ");
    scanf("%d", &codSolic);
    while(QuantCod(codSolic)!=4)
    {
        printf("\n Formato de codigo incorreto! Digite novamente o código;");
        scanf("%d", &codSolic);
    }

    // Solicita outro código enquanto já existir uma solicitação com esse número.
    while (CodigoSolicitacaoExiste(anterior, codSolic))
    {
        printf("\n Esse codigo de solicitacao ja existe. Digite outro codigo: ");
        scanf("%d", &codSolic);
        while(QuantCod(codSolic)!=4)
        {
            printf("\n Formato de codigo incorreto! Digite novamente o código;");
            scanf("%d", &codSolic);
        }
    }

    // Solicita o código do equipamento e repete a leitura até validar o formato.
    printf("\n Formato do codigo do equipamento: 3 letras e 3 digitos (ex: ABC123)");
    printf("\n Codigo do equipamento: ");
    while (!LerCodigoEquipamento(codEquip)) // Lê o código do equipamento e valida o formato
    {
        printf("\n Codigo invalido! Digite 3 letras seguidas de 3 numeros (ex: ABC123): ");
    }


    // Lê o nome com limite de tamanho para não ultrapassar o vetor.
    printf("\n Formato do nome do equipamento: até 20 caracteres (ex: Microscópio)");
    int tamanhoNome;
    do
    {
        printf("\n Nome do equipamento: ");
        if (fgets(nomeEquip, sizeof(nomeEquip), stdin) == NULL) // fgets= le nome equipe, sizeof= tamanho do nome, stdin= entrada padrão
        {
            return;
        }

        // Mede o nome para validar o limite de 20 caracteres.
        tamanhoNome = (int)strlen(nomeEquip);

        // Remove a quebra de linha; se exceder o campo, descarta o restante da linha.
        if (tamanhoNome > 0 && nomeEquip[tamanhoNome - 1] == '\n')
        {
            nomeEquip[--tamanhoNome] = '\0';
        }
        else if (tamanhoNome == 20)
        {
            int caractere = getchar();
            if (caractere != '\n' && caractere != EOF)
            {
                while (caractere != '\n' && caractere != EOF)
                {
                    caractere = getchar();
                }
                tamanhoNome++;
            }
        }

        if (tamanhoNome == 0 || tamanhoNome > 20)
        {
            printf("\n Formato de nome incorreto! Digite novamente o nome (ate 20 caracteres).\n");
        }
    }
    while (tamanhoNome == 0 || tamanhoNome > 20);

    // Solicita e valida o nível de prioridade escolhido pelo usuário.
    do
    {
        printf("\n Prioridade (1, 2 ou 3): ");
        scanf("%d", &prioridade);
    }
    while (prioridade < 1 || prioridade > 3);

    // Solicita o prazo até que ele esteja dentro do período da prioridade escolhida.
    do
    {
        if (prioridade == 1)
        {
            printf("\n Prazo para prioridade 1: de 1 a 7 dias");
        }
        if (prioridade == 2)
        {
            printf("\n Prazo para prioridade 2: de 1 a 15 dias");
        }
        if (prioridade == 3)
        {
            printf("\n Prazo para prioridade 3: de 1 a 20 dias");
        }
        printf("\n Quantos dias o equipamento fica parado: ");
        scanf("%d", &prazo);
    }
    while (prazo < 1 ||
           (prioridade == 1 && prazo > 7) ||
           (prioridade == 2 && prazo > 15) ||
           (prioridade == 3 && prazo > 20));



     // Insere o chamado diretamente na posição correta pelo código.
    InsereChamadoOrdenado(anterior, codSolic, codEquip, nomeEquip, prioridade, prazo);

    printf("\n Chamado cadastrado com sucesso!\n");
    printf("\n Codigo do chamado: %d", codSolic);
    printf("\n Codigo do equipamento: %s", codEquip);
    printf("\n Nome do equipamento: %s", nomeEquip);
    printf("\n Prioridade do equipamento: %d", prioridade);
    printf("\n Prazo do equipamento: %d", prazo);
    printf("\n\n");
    system("pause");

}
//FIM CASE 1

// CASE 3 - BUSCAR CHAMADO
////Procura o chamado na lista de chamado já feita apartir de um codigo digitado pelo usuario,
////imprime na tela se não achar o chamado e se existir mostra o nome do equipamento, o codigo do chamado,
////a prioridade e o periodo do equipamento.
void ConsultarChamado(Chamados *lista)
{
    if (verificaVazia(lista)) {
        printf("\nLista Vazia.\n");
        system("pause");
        return;
    }

    int CodSolic;
    int continuar;

    do
    {
        system("cls");
        printf("\n--- Consultar Chamado ---\n");

        printf("Digite o codigo do chamado que deseja consultar (4 digitos): ");
        scanf("%d", &CodSolic);
        while(QuantCod(CodSolic) != 4)
        {
            printf("Formato incorreto! Digite novamente um codigo que possua 4 digitos: ");
            scanf("%d", &CodSolic);
        }

        Dados *atual = lista -> inicio;
        int encontrou = 0;

        while(atual != NULL)
        {
            if(atual -> codigoSolicitacao == CodSolic)
            {
                printf("\n-- Detalhes do Chamado --\n");
                printf("Codigo do Chamado: %d\n", atual->codigoSolicitacao);
                printf("Equipamento: %s (%s)\n", atual->nomeEquipamento, atual->codigoEquipamento);
                printf("Prioridade: %d | Periodo: %d dias\n", atual->prioridade, atual->periodo);

                encontrou = 1; // Marca que encontrou
                break; // Para de procurar na lista
            }
            atual = atual -> prox;
        }
        if (encontrou == 0) {
            printf("\nChamado nao encontrado.\n");
    }
    do {
            printf("\nDeseja procurar outro codigo? (1 - Sim / 0 - Voltar ao Menu): ");
            scanf("%d", &continuar);

            if (continuar != 0 && continuar != 1) {
                printf("Opcao invalida! Digite apenas 1 ou 0.\n");
            }
        } while (continuar != 0 && continuar != 1);

    } while (continuar == 1);
}
// FIM CASE 3

//CASE 4 - ATUALIZA O CHAMADO
////Dado o código de solicitação o usuário pode alterar a prioridade e o período dela,
//respeitando os limites do período associado a nova prioridade.
// EXTRA: Permite alterar prioridade, prazo, nome do equipamento ou status.

// Print da lista o [codigoSolictacao ; prioridade] - Nome do equipamento
// Retorna a posicao que deseja alterar
Dados* MenuAtualizarChamado(Chamados *lista)
{
    if (lista == NULL || verificaVazia(lista))
    {
        printf("\n Lista Vazia\n");
        return NULL;
    }

    Dados *aux = lista->inicio;
    int codigoSelecionado;
    int validade = 0;

    printf("\n Chamados cadastrados:");
    while (aux != NULL)
    {
        printf("\n\t [%d ; %d] - %s", aux->codigoSolicitacao, aux->prioridade, aux->nomeEquipamento);
        aux = aux->prox;
    }

    do
    {
        printf("\n Selecione o codigo da solicitacao: ");
        scanf("%d", &codigoSelecionado);

        aux = lista->inicio;
        while (aux != NULL && aux->codigoSolicitacao != codigoSelecionado)
        {
            aux = aux->prox;
        }

        if (aux == NULL)
        {
            printf("\n Codigo nao encontrado. Tente novamente.\n");
            validade = 0;
        }
        else
        {
            validade = 1;
        }
    }
    while (validade == 0);

    return aux;

}

Chamados *AlterarPrioridade (Chamados *lista)
{
    // Verificar vazio
    if(verificaVazia(lista))
    {
        printf("\n Lista Vazia\n");
        return lista;
    }

    //Menu com a lista de todos os chamados
    Dados *aux = MenuAtualizarChamado(lista);
    if (aux == NULL) // Caso o usuário cancele a operação ou não selecione um chamado válido
    {
        return lista;
    }

    int prioridadeNova;
    int periodoNovo;
    int periodoMaximo;

    printf("\n Prioridade atual: %d", aux->prioridade);
    printf("\n Quantidade de dias atual: %d dias", aux->periodo);

    do
    {
        printf("\n Alterar prioridade para (1, 2 ou 3): ");
        scanf("%d", &prioridadeNova);
        if (prioridadeNova < 1 || prioridadeNova > 3)
        {
            printf("\n Prioridade invalida. Digite 1, 2 ou 3.\n");
        }
    }
    while (prioridadeNova < 1 || prioridadeNova > 3); // Loop para garantir que a prioridade seja válida (1, 2 ou 3)

    if (prioridadeNova == 1)
    {
        periodoMaximo = 7;
    }
    if (prioridadeNova == 2)
    {
        periodoMaximo = 15;
    }
    else
    {
        periodoMaximo = 20;
    }

    do
    {
        printf("\n Alterar periodo para (1 a %d dias): ", periodoMaximo);
        scanf("%d", &periodoNovo);
        if (periodoNovo < 1 || periodoNovo > periodoMaximo)
        {
            printf("\n Periodo invalido para essa prioridade.\n");
        }
    }
    while (periodoNovo < 1 || periodoNovo > periodoMaximo);

    aux->prioridade = prioridadeNova;
    aux->periodo = periodoNovo;

    printf("\n Prioridade e periodo atualizados com sucesso.\n");
    return lista;
}
// FIM DE CASE 4


// CASE 0 - SAIR DO PROGRAMA
//Descrição: Função de exclusão de lista de chamados.
//Ações: apaga lista e finaliza o programa.
//Saída: valor NULL.

Chamados *LimparListaChamados(Chamados *listachamados)
{
    if(listachamados!=NULL)
    {
        Dados *aux;
        while(listachamados->inicio!=NULL)
        {
            aux=listachamados->inicio;
            listachamados->inicio=aux->prox;
            free(aux);
        }
    }
    free(listachamados);
    return NULL;
}

//case 2 listagem da ordem de mautenção
// Compara dois nós pela urgencia: prioridade, depois periodo, depois codigo.
// Retorna <0 se 'a' vem antes de 'b', >0 se depois, 0 se iguais.
// Exibe todas as solicitações cadastradas na ordem da lista principal (por código de solicitação)
void ExibirListaGeral(Chamados *lista)
{
    if (lista == NULL || verificaVazia(lista))
    {
        printf("\nNenhuma solicitacao cadastrada.\n");
        system("pause");
        return;
    }

    printf("\n===== LISTA GERAL DE SOLICITACOES (POR CODIGO) =====\n");
    Dados *atual = lista->inicio;
    while (atual != NULL)
    {
        printf("Cod Solicitacao: %d | Equip: %s | Nome: %s | Prio: %d | Periodo: %d dias\n",
               atual->codigoSolicitacao,
               atual->codigoEquipamento,
               atual->nomeEquipamento,
               atual->prioridade,
               atual->periodo);
        atual = atual->prox;
    }
    printf("==================================================\n\n");
    system("pause");
}

int CompararUrgencia(Dados *a, Dados *b)
{
    // 1) Prioridade (menor numero = mais urgente)
    if (a->prioridade != b->prioridade)
        return a->prioridade - b->prioridade;

    // 2) Periodo (menor periodo = mais urgente)
    if (a->periodo != b->periodo)
        return a->periodo - b->periodo;

    // 3) Codigo de solicitacao (desempate)
        return a->codigoSolicitacao - b->codigoSolicitacao;
}

// Insere um no ja criado na lista auxiliar, mantendo-a ordenada por urgencia.
void InsereOrdenadoUrgencia(Chamados *lista, Dados *novo)
{
    Dados *anterior = NULL;
    Dados *atual = lista->inicio;

    while (atual != NULL && CompararUrgencia(atual, novo) < 0)
    {
        anterior = atual;
        atual = atual->prox;
    }

    novo->prox = atual;
    if (anterior == NULL)
        lista->inicio = novo;
    else
        anterior->prox = novo;
}

// Exibe a ordem de manutencao SEM alterar a lista principal.
// Exibe a ordem de manutencao SEM alterar a lista principal.
void exibirOrdemManutencao(Chamados *lista)
{
    // 1) Cria lista auxiliar vazia
    Chamados *aux = InicializaListaChamado();

    // 2) Percorre a principal e insere copias na auxiliar de forma ordenada
    Dados *atual = lista->inicio;
    while (atual != NULL)
    {
        Dados *novo = (Dados*)malloc(sizeof(Dados));
        if (novo == NULL) return; // Verificação de alocação de memória

        novo->codigoSolicitacao = atual->codigoSolicitacao;
        int i = 0;
        while (atual->codigoEquipamento[i] != '\0')
        {
            novo->codigoEquipamento[i] = atual->codigoEquipamento[i];
            i++;
        }
        novo->codigoEquipamento[i] = '\0';
        i = 0;
        while (atual->nomeEquipamento[i] != '\0')
        {
            novo->nomeEquipamento[i] = atual->nomeEquipamento[i];
            i++;
        }
        novo->nomeEquipamento[i] = '\0';

        novo->prioridade = atual->prioridade;
        novo->periodo    = atual->periodo;
        novo->prox       = NULL;

        InsereOrdenadoUrgencia(aux, novo);

        atual = atual->prox;
    }

    // 3) Exibe a auxiliar
    printf("\n===== ORDEM DE MANUTENCAO (POR URGENCIA) =====\n");
    Dados *p = aux->inicio;
    if (p == NULL)
    {
        printf("Nenhuma solicitacao cadastrada.\n");
    }
    else
    {
        while (p != NULL)
        {
            printf("Cod: %d | Equip: %s | Nome: %s | Prio: %d | Periodo: %d dias\n",
                   p->codigoSolicitacao,
                   p->codigoEquipamento,
                   p->nomeEquipamento,
                   p->prioridade,
                   p->periodo);
            p = p->prox;
        }
    }
    printf("==========================================================================\n\n");

    // 4) Libera a auxiliar
    LimparListaChamados(aux);
    system("pause");
}

// CASE 5 - EXCLUIR CHAMADO
/*
Entrada: lista.
Funções:
    ExcluirChamado: tem a entrada de uma lista, solicita o código do chamado a ser excluido,
    verifica se o codigo existe chmando a função CodigoSolicitacaoExiste e por fim, se existir,
    procura o chamado na lista e o exclui.
Saida: Lista nova com o chamado solicitado excluido.
*/

Chamados* ExcluirChamado(Chamados *lista)
{
    if(verificaVazia(lista))
    {
        printf("\n Lista Vazia, impossivel realizar a operacao.");
        return lista;
    }
    int op,cod;
    printf("\n Deseja digitar o codigo de solicitacao direto ou visualizar a lista de chamar? \n 1 - Visualizar lista de chamados. \n 2 - Digitar diretamente o codigo.\n");
    printf("/n Digite a opcao: ");
    scanf("%d", &op);

    if(op==1)
    {
        ExibirListaGeral(lista);
    }
    printf("\n Digite o codigo de solicitacao do chamado que deseja excluir: ");
    scanf("%d", &cod);
    if(CodigoSolicitacaoExiste(lista,cod))
    {
        Dados *aux1=lista->inicio;
        Dados *aux2=lista->inicio;
        while(aux1->codigoSolicitacao!=cod)
        {
            aux2=aux1;
            aux1=aux1->prox;
        }
        int conf;
        printf("\n Confirme se este eh o chamado que deseja excluir:\n \n Cod Solicitacao: %d | Equip: %s | Nome: %s | Prio: %d | Periodo: %d dias \n",
               aux1->codigoSolicitacao,
               aux1->codigoEquipamento,
               aux1->nomeEquipamento,
               aux1->prioridade,
               aux1->periodo);
               printf("\n 1 - SIM \n 2 - NAO \n Resposta:");
               scanf("%d", &conf);
         if(conf==1)
             {
            if(aux1 == lista->inicio)
            {
                lista->inicio = aux1->prox;
            }
            else
            {
            aux2->prox=aux1->prox;
            }
            free(aux1);
            printf("\n Chamado excluido com sucesso! \n");

         }
         else
        {
            printf("\n Operacao cancelada.\n");
         }
        system("pause");
        return lista;

    }
    printf("\n Codigo nao existe na lista. \n");
        system("pause");
        return lista;

}
// FIM DO CASE 5


#endif // FUNCOES_H_INCLUDED
