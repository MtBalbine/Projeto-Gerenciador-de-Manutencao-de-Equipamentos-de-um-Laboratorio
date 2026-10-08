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

// Cria e retorna outra lista vazia de chamados.
Chamados* ListaChamados()
{
    Chamados *aux;
    aux=(Chamados*)malloc(sizeof(Chamados));
    aux->inicio=NULL;
    return aux;
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

/* ===== ORDEM DE MANUTENCAO (por urgencia) ===== */

// Compara dois nós pela urgencia: prioridade, depois periodo, depois codigo.
// Retorna <0 se 'a' vem antes de 'b', >0 se depois, 0 se iguais.
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

    while (atual != NULL && CompararUrgencia(atual, novo) <= 0)
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
void exibirOrdemManutencao(Chamados *lista)
{
    // 1) Cria lista auxiliar vazia
    Chamados *aux = InicializaListaChamado();

    // 2) Percorre a principal e insere copias na auxiliar de forma ordenada
    Dados *atual = lista->inicio;
    while (atual != NULL)
    {
        Dados *novo = (Dados*)malloc(sizeof(Dados));
        novo->codigoSolicitacao = atual->codigoSolicitacao;
        strcpy(novo->codigoEquipamento, atual->codigoEquipamento);
        strcpy(novo->nomeEquipamento, atual->nomeEquipamento);
        novo->prioridade = atual->prioridade;
        novo->periodo    = atual->periodo;
        novo->prox       = NULL;

        InsereOrdenadoUrgencia(aux, novo);

        atual = atual->prox;
    }

    // 3) Exibe a auxiliar
    printf("\n===== ORDEM DE MANUTENCAO (URGENCIA) =====\n");
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

    printf("\nPressione ENTER para voltar ao menu...");
    getchar();

    // 4) Libera a auxiliar (NAO a principal)
    LimparListaChamados(aux);
}

#endif // FUNCOES_H_INCLUDED
