#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include <ctype.h> // Biblioteca para funções de manipulação de caracteres
#include <string.h> // Biblioteca para funções de manipulação de strings

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



// Cria uma lista vazia de chamados.
Chamados* InicializaListaChamado()
{
    Chamados *aux = (Chamados*)malloc(sizeof(Chamados));
    aux->inicio = NULL;
    return aux;
}

// Conta os dígitos de um código positivo de solicitação.
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

//Verifica Vazio
int verificaVazia(Chamados *l)
{
    if (l->inicio== NULL)
    {
        return 1;
    }
    return 0;
}


// Lê a linha inteira, validando três letras e três números e convertendo as letras para maiúsculas.
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


// Aloca e preenche um nó, apontando-o para o próximo nó informado.
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

// Verifica se o código da solicitação já está cadastrado na lista.
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

// Insere o chamado diretamente na posição crescente do código de solicitação.
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

    int CodSOlic;
    printf("\nDigite o codigo da solicitacao que deseja consultar: ");
    scanf("%d", &CodSOlic);

    Dados *atual = lista->inicio;
    while(atual != NULL)
    {
        if(atual->codigoSolicitacao == CodSOlic) {
            printf("\n-- Detalhes da Solicitacao --\n");
            printf("Codigo da Solicitacao: %d\n", atual->codigoSolicitacao);
            printf("Equipamento: %s (%s)\n", atual->nomeEquipamento, atual->codigoEquipamento);
            printf("Prioridade: %d | Periodo: %d dias\n", atual->prioridade, atual->periodo);
            system("pause");
            return;
        }
        atual = atual->prox;
    }
    printf("\nSolicitacao nao encontrada.\n");
    system("pause");
}

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

#endif // FUNCOES_H_INCLUDED
