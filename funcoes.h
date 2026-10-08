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
    int cod_s;
    char cod_e[7];// uma casa a mais para "\0"
    char nome[21];// uma casa a mais para "\0"
    int prio;
    int dias;
    struct dados *prox;
}Dados;

typedef struct chamados
{
   No *Inicio;
}Chamados;

Chamado* InicializaListaChamado()
{
<<<<<<< HEAD
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
=======
    return NULL;
>>>>>>> parent of edb338b (Implementa o cadastro de novos itens)
}

Chamados* ListaChamados()
{
    Chamados *aux;
    aux=(Chamados*)malloc(sizeof(Chamados));
    aux->inicio=NULL;
    return aux;
}

Dados* CriaChamado(Dados* anterior, int soli, char cequi[], char nequi[], int pri, int prazo)
{
    Dados* aux;
    aux=(Dados*)malloc(sizeof(Dados));
    //aux->cod_s=soli;
    //aux->cod_e=cequi; corrigir leiura de vetores
    aux->nome=nequi;
    aux->prio=pri;
    aux->dias=prazo;

    aux->prox=anterior;
    return aux;
}
<<<<<<< HEAD

// Confere se o código já existe e bloqueia códigos iguais
int ExisteCodigo(Chamados *lista, int cod)
{
    Dados *atual = lista -> inicio;
    while(atual != NULL)
    {
        if(atual -> codigoSolicitacao == cod)
        {
            return 1;
            atual = atual -> prox;
        }
        return 0;
    }
}

// Insere o chamado ordenado pelo código
void InsereOrdenado(Chamados *lista, int soli, char codEquip[], char nomeEquip[], int prioridade, int periodo)
{
    Dados* novo = (Dados*)malloc(sizeof(Dados));
    novo -> codSolicitacao = soli;

    int i = 0;
    while(codEquip[i] != '\0')
    {
        novo->codigoEquipamento[i] = codEquip[i]; i++;
    }
        novo->codigoEquipamento[i] = '\0';
        i = 0;
        while (nomeEquip[i] != '\0')
        {
            novo->nomeEquipamento[i] = nomeEquip[i]; i++;
        }
        novo->nomeEquipamento[i] = '\0';
    novo->prioridade = prioridade;
    novo->periodo = periodo;
    novo->prox = NULL;

    if (lista->inicio == NULL || lista->inicio->codigoSolicitacao > soli)
        {
        novo->prox = lista->inicio;
        lista->inicio = novo;
        }
    else
        {
            Dados *atual = lista->inicio;
            while (atual->prox != NULL && atual->prox->codigoSolicitacao < soli)
            {
                atual = atual->prox;
            }
            novo->prox = atual->prox;
            atual->prox = novo;
        }

    printf("\n Chamado cadastrado com sucesso!\n");
    printf("\n Codigo do chamado: %d", codSolic);
    printf("\n Codigo do equipamento: %s", codEquip);
    printf("\n Nome do equipamento: %s", nomeEquip);
    printf("\n Prioridade do equipamento: %d", prioridade);
    printf("\n Prazo do equipamento: %d", prazo);
    printf("\n\n");
    system("pause");
=======

void NovoChamado(Chamado *anterior)
{
     int cod;
    printf("\n Codigo do chamado: ");
    scanf("%d", &cod);
    while(QuantCod(cod)!=4)
    {
        printf("\n Formato de codigo incorreto! Digite novamente o código;");
        scanf("%d", &cod);
    }
    
>>>>>>> parent of edb338b (Implementa o cadastro de novos itens)

}


int QuantCod(int v)
{
    int cont=0;

    while(v>0)
    {
        v=v/10;
        cont++;
    }
    return v;
}

#endif // FUNCOES_H_INCLUDED
