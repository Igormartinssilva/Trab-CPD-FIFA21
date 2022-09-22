
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
#include "csv.h"
#include "Handle.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
Lista *Tabela[CAPACITY]; ///tabela HASH, variavel global para facilitar
///--------------------------------------------------------FUNÇOES DA TABLEA HASH-------------------------------------------------

///essa função faz aumentar a chance de colisão, ela calcula o valor ASCII da string
unsigned long hash_function(int str)  ///unsigned long é uma variavel que so aramazena 32 bits positivos
{
    unsigned long i = 0;
    int j;
    int tam = str;

    ///i vai receber a soma dos valores ascii da string
    for(j=0; j<tam; j++)
    {
        i += str * (j + 1); ///somatorio ascii vezes a posição
    }

    return i % CAPACITY;
}

///inicializa a tabela, faz com que a tabela receba tudo NULL
void inicializar()
{
    int i;
    for(i=0; i<CAPACITY; i++)
    {
        Tabela[i] = criarLista();
    }
}

///aloca espaço para o item a ser inserido
Ht_item* create_item(int indice, int idUser, int idJog, char* key, int notaMed,int quantAval, int notUsua)
{
    ///cria um ponteiro para o novo intem da tabela hash
    Ht_item* item = (Ht_item*) malloc(sizeof(Ht_item));

    item->nomeJogador = (char*) malloc (strlen(key) + 1);

    item->posicao = hash_function(indice);///cada item salva a posicao com base na funçao hash dele
    strcpy(item->nomeJogador, key);
    item->id_user = idUser;
    item->indice = indice;
    item->notaMedia = notaMed;
    item->notaUserJog = notUsua;
    item->quantAval = quantAval;
    item->sofifa_id = idJog;


    return item;
}

///insere na tabela
void inserTabela( int indice, int idUser, int idJog, char* key, int notaMed,int quantAval, int notUsua)
{
    unsigned long index;
    Ht_item* item;

    index = hash_function(indice);
    item = create_item(indice, idUser, idJog, key, notaMed, quantAval,notUsua);

    Tabela[index] = insereInicio(item, Tabela[index]);
}


///procura na tabela o nome desejado
int ht_search(int key)
{
    //procura um item na tabela
    //retorna nulo se ele não existir

    int index = hash_function(key);
    /* NoLis *no = buscarNo(key, Tabela[index]->inicio);




     if(no == NULL)
     {
         return -1;
     }
     else
         return 0;

         */
}
///função para dar print na tabela
void print_table()
{
    int i;

    std::cout << "\n \t TABELA HASH \n---------------------------------\n";
    for(i=0; i<CAPACITY; i++)
    {
        printf("\nIndice: %d Lista tamaho: %d\t lista encadeada dessa posicao: \n ", i,Tabela[i]->tam);
        imprimirLista(Tabela[i]->inicio);
    }

    std::cout<< "\n---------------------------------\n\n";

}

int contaVal()
{

    int cont, i;

    for(i=0; i<CAPACITY; i++)
    {
        if(Tabela[i] != NULL)
            cont++;
    }
    return cont;
}

