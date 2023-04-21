
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
Lista *Tabela[CAPACITY]; ///tabela HASH, variavel global para facilitar
Lista *tabelaPosition[POS];///tabela das posiçoes dos jogadores
///--------------------------------------------------------FUNÇOES DA TABLEA HASH-------------------------------------------------

///essa função faz aumentar a chance de colisão, ela calcula o valor ASCII da string
unsigned long hash_function(char* str)  ///unsigned long é uma variavel que so aramazena 32 bits positivos
{
    unsigned long i = 0;
    int j;
    int tam = strlen(str);

    ///i vai receber a soma dos valores ascii da string
    for(j=0; j<tam; j++)
    {
        i += str[j] * (j + 1); ///somatorio ascii vezes a posição
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
        Tabela[i]->inicio = NULL;
    }
}

///aloca espaço para o item a ser inserido
Ht_item* create_item(char* indice, int idUser, int idJog, double notUsua)
{
    ///cria um ponteiro para o novo intem da tabela hash
    Ht_item* item = (Ht_item*) malloc(sizeof(Ht_item));

    //  item->nomeJogador = (char*) malloc (strlen(key) + 1);

    //  item->posicao = hash_function(indice);///cada item salva a posicao com base na funçao hash dele
    // strcpy(item->nomeJogador, indice);
    item->id_user = idUser;

    item->indice = indice;
    // item->notaMedia = notaMed;
    item->notaUserJog = notUsua;
    // item->quantAval = quantAval;
    item->sofifa_id = idJog;


    return item;
}

///insere na tabela
void inserTabela(char* indice, int idUser, int idJog, double notUsua)
{
    unsigned long index;
    Ht_item* item;

    index = hash_function(indice);
    item = create_item(indice, idUser, idJog, notUsua);


    insereUser(item, Tabela[index]);

    // cout << Tabela[index]->inicio->item->sofifa_id;
}



///função para dar print na tabela
void print_table()
{
    int i;

    std::cout << "\n \t TABELA HASH \n---------------------------------\n";

    for(i=0; i<CAPACITY; i++)
    {

        if(Tabela[i]->inicio != NULL)
            printf("\nIndice: %d id_user: %d\t nota media: %lf \t quantida aval: %d\n ", i,Tabela[i]->inicio->user.sofifa_id[i]);
        //imprimirLista(Tabela[i]->inicio);
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

int HashUser(int key)
{
    return key % CAPACITY;
}
void InsereUserTab(int key, int sofifa_id, float nota) //insere no início da lista encadeada no índice do hash calculado
{
    int index = HashUser(key), j=0;
    NoLis *pointer;


    pointer = achaUser(key);



    if(!pointer) //caso de nodo não existente
    {
        NoLis *new_pt = (NoLis*)malloc(sizeof(NoLis));

        new_pt->user.user_id = key;
        new_pt->user.sofifa_id[0] = sofifa_id;
        new_pt->user.notas[0] = nota;


        new_pt->next = Tabela[index]->inicio;
        Tabela[index]->inicio = new_pt;
    }
    else //caso em que usuário já foi inserido, logo inserem-se apenas os jogadores
    {
        do
        {
            if(pointer->user.sofifa_id[j]==0)
            {
                pointer->user.sofifa_id[j] = sofifa_id;
                pointer->user.notas[j] = nota;
                j=200;
            }
            j++;
        }
        while(pointer->user.sofifa_id[j-1]!=0&&(j-1)<200);
    }

}


NoLis* achaUser(int key) //pesquisa da chave nos elementos da lista encadeada da hash de usuários (user_id)
{
    int ind = HashUser(key);

    NoLis *pointer = Tabela[ind]->inicio;


    if(pointer==NULL)
    {
        return NULL;
    }
    while(pointer->next!=NULL)
    {
        if (pointer->user.user_id==key)
        {
            return pointer;
        }
        pointer=pointer->next;
    }
    if (pointer->user.user_id==key)
    {
        return pointer;
    }
    return NULL;
}
//escolhi o quicksort pq foi o mais rapido naquele lab
void quicksort_hoare(float *v, int *v2, int s, int e)//qcksrt hoare med3
{
    int p, key, pm, i, j, esq;
    float keyF, compF;

    if(e>s)
    {
        //MEDIANA DE 3
        pm = (s+e)/2;
        if(v[s]>=v[e])
        {
            if(v[s]>=v[pm])
            {
                if(v[pm]>=v[e]) p = pm;
                else p = e;
            }
            else p = s;
        }
        else
        {
            if(v[e]>=v[pm])
            {
                if(v[pm]>=v[s]) p = pm;
                else p = s;
            }
            else p = e;
        }
        if(p!=s)
        {
            keyF = v[p];
            v[p] = v[s];
            v[s] = keyF;
            key = v2[p];
            v2[p] = v2[s];
            v2[s] = key;
        }
        //particionamento
        compF = v[s];
        i = s;
        j = e;
        esq = 1;

        while(i<j)
        {
            if(esq)
            {
                if(compF<v[j])
                {
                    keyF = v[j];
                    v[j] = v[i];
                    v[i] = keyF;
                    key = v2[j];
                    v2[j] = v2[i];
                    v2[i] = key;
                    i++;
                    esq=0;
                }
                else j--;
            }
            else
            {
                if(compF>=v[i])
                {
                    keyF = v[j];
                    v[j] = v[i];
                    v[i] = keyF;
                    key = v2[j];
                    v2[j] = v2[i];
                    v2[i] = key;
                    j--;
                    esq=1;
                }
                else i++;
            }
        }
        quicksort_hoare(v, v2, s, i-1);
        quicksort_hoare(v, v2, i+1, e);
    }
}

///procura na tabela o nome desejado
int pesquisaUser(int key)
{

    int j=0;
    int contador = 0;

    NoLis *pointer =  achaUser(key);
    if(!pointer)
        return -1;
    cout << "id\t\t\t\t\t    name       global_rating    count  rating\n";
    quicksort_hoare(pointer->user.notas,pointer->user.sofifa_id, 0,199);
    while(j<200&&contador<20)
    {
        if((pointer->user.sofifa_id[j])!=0);
        {
            cout << pointer->user.sofifa_id[j] << "\t\t";
            printf("%5.2f", pointer->user.notas[j]);
            contador++;
            j++;
        }
    }
}

