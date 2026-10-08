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

    // Codigo do equipamento
    printf("\n Formato do codigo do equipamento: 3 letras e 3 digitos (ex: ABC123)");
    printf("\n Codigo do equipamento: ");
    scanf("%s", codEquip);
    int tamanhoCodigo = 0;
    while (codEquip[tamanhoCodigo] != '\0')
    {
        tamanhoCodigo++;
    }
    while(tamanhoCodigo!=6)
    {
        printf("\n Formato de codigo incorreto! Digite novamente o código;");
        scanf("%s", codEquip);
        tamanhoCodigo = 0;
        while (codEquip[tamanhoCodigo] != '\0')
        {
            tamanhoCodigo++;
        }
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

    /*Prioridade
     Prioridade 1 → período entre 1 e 7 dias
     Prioridade 2 → período entre 1 e 15 dias
     Prioridade 3 → período entre 1 e 20 dias. */
    do
    {
        printf("\n Formato do prazo: entre 1 e 20 dias");
        printf("\n quantos dias o equipamento fica parado: ");
        scanf("%d", &prazo);
    }
    while(prazo < 1 || prazo > 20);

    // Verifica a prioridade com base no prazo informado
    if(prazo>=1 && prazo<=7) 
    {
        prioridade=1;
    }
    if(prazo>=8 && prazo<=15)
    {
        prioridade=2;
    }
    if(prazo>=16 && prazo<=20)
    {
        prioridade=3;
    }
    

    //Ao final da verificação, o programa utiliza a função de Criar o chamado
    anterior->inicio = CriaChamado(anterior->inicio, codSolic, codEquip, nomeEquip, prioridade, prazo);
    
    printf("\n Chamado cadastrado com sucesso!\n");
    printf("\n Codigo do chamado: %d", codSolic);
    printf("\n Codigo do equipamento: %s", codEquip);
    printf("\n Nome do equipamento: %s", nomeEquip);
    printf("\n Prioridade do equipamento: %d", prioridade);
    printf("\n Prazo do equipamento: %d", prazo);
    printf("\n\n");
    system("pause");

}


#endif // FUNCOES_H_INCLUDED
