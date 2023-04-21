#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
//#include "csv.h"
#include "Handle.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

// constante repesenta o tamanho da tabela
#define M 20000

// estrutura Pessoa com nome e uma matrícula

// nossa tabela hash do tipo Pessoa
DadosRating tabelaHash[M];

// inicializa nossa tabela com o valor de codigo -1
void inicializarTabela()
{
    int i;
    for(i = 0; i < M; i++)
    {
        tabelaHash[i].sofifa_id = -1;
        tabelaHash[i].id_user = 0;
        tabelaHash[i].notaMedia = 0;
        tabelaHash[i].notaUserJog = 0;
        tabelaHash[i].quantAval = 0;

    }
}

// função de espalhamento (resto da divisão da chave por M)
int gerarCodigoHash(int chave)
{
    return chave % M;
}

// inserir uma pessoa na tabela
void inserir(int idJog, int idUser, float nota)
{
    //DadosRating pes = lerPessoa();

    int indice = gerarCodigoHash(idJog);

    //  while(tabelaHash[indice].sofifa_id != -1)
    //   indice = gerarCodigoHash(indice + 1);

    tabelaHash[indice].sofifa_id = idJog;
    tabelaHash[indice].id_user = idUser;
    tabelaHash[indice].quantAval++;
    tabelaHash[indice].notaUserJog += nota;
    tabelaHash[indice].notaMedia = (tabelaHash[indice].notaMedia + tabelaHash[indice].notaUserJog) / tabelaHash[indice].quantAval;

}

void buscar(int chave)
{
    int indice = gerarCodigoHash(chave);


        cout << "indice: " << indice << endl;
        cout << "quant aval: "<<tabelaHash[indice].quantAval<< endl;
        cout << "sofica: " << tabelaHash[indice].sofifa_id << endl;
        cout <<  "nota media: "<<tabelaHash[indice].notaMedia<< endl <<endl;

}

void imprimir()
{
    int i;
    printf("\n------------------------TABELA---------------------------\n");
    for(i = 0; i < M; i++)
    {
        if(tabelaHash[i].sofifa_id != -1){
            printf(" indice %d quant aval: %3d \t nota media %f, id fifa: %d", i, tabelaHash[i].quantAval, tabelaHash[i].notaMedia, tabelaHash[i].sofifa_id);
            cout << endl << endl;
        }
    }
    printf("\n----------------------------------------------------------\n");
}

Jogadores pegaDados(int idJog)
{
    Jogadores infor;

    infor.notaMedia = tabelaHash[gerarCodigoHash(idJog)].notaMedia;
    infor.quantAval = tabelaHash[gerarCodigoHash(idJog)].quantAval;

    return infor;
}
