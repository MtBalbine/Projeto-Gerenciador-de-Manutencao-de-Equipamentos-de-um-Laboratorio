#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

//Funções de Manipulação de Lista

typedef struct      // Struct que guarda os dados do equipamento
{
    int codSolicitacao;     // 4 dígitos 
    char codEquipamento[7];     // 3 dígitos + '\0'
    char nome[21];      // máx 20 caracteres + '\0'
    int prioridade;      // 1, 2 e 3
    int periodo;         // em dias
}Equipamento;

typedef struct No       // Nó da lista encadeada
{
    Equipamento dados;
    struct No *prox;
} No;

typedef struct chamados
{
    No *inicio;     // aponta para o nó cabeça
}Chamados;

// Prototypes (avisa ao compilador que as funções existem) 
Chamados* criarLista(void);     
void      liberarLista(Chamados *anterior);
int       QuantCod(int v);
int       validarCodEquipamento(const char *s);
int       codigoExiste(Chamados *anterior, int cod);
void      inserirOrdenado(Chamados *anterior, Equipamento eq);
void      NovoChamado(Chamados *anterior);
void      removerChamado(Chamados *anterior);
void      consultarChamado(Chamados *anterior);
void      alterarChamado(Chamados *anterior);
void      exibirOrdemManutencao(Chamados *anterior);
void      exibirTodas(Chamados *anterior);

Chamados* InicializaListaChamado()
{
    return NULL;
}

Chamados* ListaChamados()
{
    Chamados *aux;
    aux=(Chamados*)malloc(sizeof(Chamados));
    aux->inicio=NULL;
    return aux;
}

Equipamento* CriaChamado(Equipamento* anterior, int soli, char cequi[], char nequi[], int pri, int prazo)
{
    Equipamento* aux;
    aux=(Equipamento*)malloc(sizeof(Equipamento));
    aux->codSolicitacao=soli;
    aux->codEquipamento=cequi; corrigir leiura de vetores
    strcpy(aux->nome, nequi);
    aux->prioridade=pri;
    aux->periodo=prazo;

    aux->prox=anterior;
    return aux;
}

void NovoChamado(Chamados *anterior)
{
    int cod;
    printf("\n Codigo do chamado: ");
    scanf("%d", &cod);
    while(QuantCod(cod)!=4)
    {
        printf("\n Formato de codigo incorreto! Digite novamente o código;");
        scanf("%d", &cod);
    }

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
