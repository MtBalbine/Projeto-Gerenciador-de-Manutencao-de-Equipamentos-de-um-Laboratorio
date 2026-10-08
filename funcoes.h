#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

/*

    Funções de Manipulação de Lista


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

Chamados* InicializaListaChamado()
{
    Chamados *aux = (Chamados*)malloc(sizeof(Chamados));
    aux->inicio = NULL;
    return aux;
}

int QuantCod(int v) // Função para contar a quantidade de dígitos de um número inteiro
{
    int cont=0;

    while(v>0)
    {
        v=v/10;
        cont++;
    }
    return cont;
}

// Aceita somente três letras seguidas de três números.
int CodigoEquipamentoValido(char codigo[])
{
    int tamanho = 0;
    while (codigo[tamanho] != '\0')
    {
        tamanho++;
    }

    if (tamanho != 6)
    {
        return 0;
    }

    // Os três primeiros caracteres devem ser letras.
    for (int i = 0; i < 3; i++)
    {
        if (!((codigo[i] >= 'A' && codigo[i] <= 'Z') ||
              (codigo[i] >= 'a' && codigo[i] <= 'z')))
        {
            return 0;
        }
    }

    // Os três últimos caracteres devem ser números.
    for (int i = 3; i < 6; i++)
    {
        if (codigo[i] < '0' || codigo[i] > '9')
        {
            return 0;
        }
    }

    return 1;
}

Chamados* ListaChamados()
{
    Chamados *aux;
    aux=(Chamados*)malloc(sizeof(Chamados));
    aux->inicio=NULL;
    return aux;
}

Dados* CriaChamado(Dados* anterior, int soli, char codigoEquipamento[], char nomeEquipamento[], int prioridade, int periodo)
{
    Dados* aux = (Dados*)malloc(sizeof(Dados));
    aux->codigoSolicitacao=soli;
    int i = 0;
    while (codigoEquipamento[i] != '\0')
    {
        aux->codigoEquipamento[i] = codigoEquipamento[i];
        i++;
    }
    aux->codigoEquipamento[i] = '\0';

    i = 0;
    while (nomeEquipamento[i] != '\0')
    {
        aux->nomeEquipamento[i] = nomeEquipamento[i];
        i++;
    }
    aux->nomeEquipamento[i] = '\0';

    aux->prioridade=prioridade;
    aux->periodo=periodo;

    aux->prox=anterior;
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

// Reorganiza os nós da lista em ordem crescente, sem vetor ou ponteiro duplo.
void OrdenaCodigosSolicitacao(Chamados *lista)
{
    Dados *atual = lista->inicio;
    Dados *ordenada = NULL;

    while (atual != NULL)
    {
        Dados *proximo = atual->prox;

        // Insere o nó atual na posição correta da lista já ordenada.
        if (ordenada == NULL || atual->codigoSolicitacao < ordenada->codigoSolicitacao)
        {
            atual->prox = ordenada;
            ordenada = atual;
        }
        else
        {
            Dados *posicao = ordenada;
            while (posicao->prox != NULL &&
                   posicao->prox->codigoSolicitacao < atual->codigoSolicitacao)
            {
                posicao = posicao->prox;
            }

            atual->prox = posicao->prox;
            posicao->prox = atual;
        }

        atual = proximo;
    }

    lista->inicio = ordenada;
}



void NovoChamado(Chamados *anterior) // Função para cadastrar um novo chamado
{
    int codSolic, prioridade, prazo;
    char codEquip[7];
    char nomeEquip[21];

    // Solicita ao usuário o código do chamado e verifica se possui 4 dígitos
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

    // Codigo do equipamento
    printf("\n Formato do codigo do equipamento: 3 letras e 3 digitos (ex: ABC123)");
    printf("\n Codigo do equipamento: ");
    scanf("%6s", codEquip);
    while (!CodigoEquipamentoValido(codEquip))
    {
        printf("\n Codigo invalido! Digite 3 letras seguidas de 3 numeros (ex: ABC123): ");
        scanf("%6s", codEquip);
    }


    // Nome do equipamento, usuario pode digitar menos que 20 caracteres
    printf("\n Formato do nome do equipamento: até 20 caracteres (ex: Microscópio)");
    printf("\n Nome do equipamento: ");
    scanf(" %[^\n]s", nomeEquip);
    int tamanhoNome = 0;
    while (nomeEquip[tamanhoNome] != '\0')
    {
        tamanhoNome++;
    }
    while(tamanhoNome>20)
    {
        printf("\n Formato de nome incorreto! Digite novamente o nome;");
        scanf(" %[^\n]s", nomeEquip);
        tamanhoNome = 0;
        while (nomeEquip[tamanhoNome] != '\0')
        {
            tamanhoNome++;
        }
    }

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
    


    //Ao final da verificação, o programa utiliza a função de Criar o chamado
    anterior->inicio = CriaChamado(anterior->inicio, codSolic, codEquip, nomeEquip, prioridade, prazo);
    OrdenaCodigosSolicitacao(anterior); // Mantém a lista em ordem crescente pelo código.

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

#endif // FUNCOES_H_INCLUDED
