
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

///---------------------------------------------------FUN�OES DA LISTA ENCADEADA----------------------------------------
///cria uma lista vazia e retorna o seu endere�o de memoria
Lista* criarLista()
{
    Lista *lis = (Lista*)malloc(sizeof(Lista));
    lis->inicio = NULL;
    lis->tam = 0;

    return lis;
}

///Fun��o que vai inserir no inicio da lista encadeada, n�o precisando ir ate o fim dela
Lista* insereInicio(Ht_item* item, Lista *lista)
{
    NoLis *no = (NoLis*)malloc(sizeof(NoLis));
    no->item = item;

    // cout << "isere incio";
    if(lista->inicio == NULL)
    {
        //se nao tiver nada, tu cria a lista
        no->next = lista->inicio;
        lista->inicio = no;
        lista->inicio->item->quantAval = lista->inicio->item->quantAval + 1;
        lista->inicio->item->notaUserJog += item->notaUserJog;
        lista->inicio->item->notaMedia = (lista->inicio->item->notaUserJog / lista->inicio->item->quantAval);

    }
    else
    {
        //se nao tu so atualiza ela
        lista->inicio->item->quantAval = lista->inicio->item->quantAval + 1;
        lista->inicio->item->notaUserJog += item->notaUserJog;
        lista->inicio->item->notaMedia = (lista->inicio->item->notaUserJog / lista->inicio->item->quantAval);
    }


    ///Aqui linka a lista ja existente no com o novo elemento adicionado
    // no->next = lista->inicio;
    //  lista->inicio = no;
    //  lista->tam++;

}

//Fun��o que vai inserir no inicio da lista encadeada, n�o precisando ir ate o fim dela
void insereUser(Ht_item* item, Lista *lista)
{
    NoLis *no = (NoLis*)malloc(sizeof(NoLis));
    no->item = item;

    ///Aqui linka a lista ja existente no com o novo elemento adicionado
    no->next = lista->inicio;
    lista->inicio = no;

}


///Fun��o que vai inserir no inicio da lista encadeada de forma ordenada
Lista* insereOrdenado(Ht_item* item, Lista *lista)
{
    ///comparar a lista com  item , Lista � a tabela tbm
    NoLis *novo = (NoLis*)malloc(sizeof(NoLis));
    novo->item = item;

    NoLis *ptAux, *ptAnte;

    if(lista == NULL)
    {
        novo->next = lista->inicio;
        lista->inicio = novo;

        return lista;
    }
    else
    {
        ptAux = lista->inicio;
        ptAnte = NULL;

        while(ptAux != NULL && ptAux->item->notaUserJog > novo->item->notaUserJog)// enquanto nao ta no final da lista  e o codigo do novo dado for menor que o codigo do proximo
        {

            if (ptAux->next == NULL && ptAux->item->notaUserJog > novo->item->notaUserJog)//se o proximo elemento � nulo, e o cod novo � menor, entao adiciona no final
            {
                novo->next = NULL;

                for(ptAux = lista->inicio; ptAux->next; ptAux = ptAux->next);
                ptAux->next = novo;

                return lista;
            }
            /*   else if(ptAux->item->sofifa_id == lista->inicio->item->sofifa_id)
               {
                   lista->inicio->item->quantAval++;
                   lista->inicio->item->notaMedia = (item->notaUserJog + lista->inicio->item->notaMedia) / lista->inicio->item->quantAval;

                   return lista;
               }
            */

            ptAnte = ptAux;
            ptAux = ptAux->next;
        }
        // ponteiro anterior nulo tem dois casos, o que o codigo do novo � maior que o que tem na lista ou o que � menor//
        if(ptAnte == NULL && ptAux->item->notaUserJog > novo->item->notaUserJog)      //ele � o segundo elemento a ser posto na lista e codigo � menor
        {
            novo->next = NULL;      //como foi adicionado no final da lista, ele vai apontar para nada
            lista->inicio->next = novo;
        }

        else if(ptAnte == NULL && ptAux->item->notaUserJog < novo->item->notaUserJog )// caso o codigo seja maior que o elmento que ja esta na lista ele � adicionado no inicio
        {
            novo->next = lista->inicio;
            lista->inicio = novo;

        }


        //agora os casos que ja tem dois elementos na lista, ele pode ser insirido no meio ou no fim.//
        else if(ptAnte != NULL)// quando achar onde deve ser posto o elemento, ele adiciona ele.
        {
            if(ptAux->item->notaUserJog < novo->item->notaUserJog)// vai ser adicionado no meio da lista
            {
                novo->next = ptAux;
                ptAnte->next = novo;

            }
        }
    }

    lista->tam++;

    return lista;
}

///quando for buscar uma palavra, aqui percorre a lista no indice correto
NoLis* buscarNo(char *mat, NoLis* inicio)
{

    while(inicio != NULL)
    {
        //encontrei o nome que eu queria
        if(strcmp(inicio->item->indice, mat)== 0)
        {
            return inicio;
        }
        else
        {
            inicio = inicio->next;///vou para proxima parte da lista encadeada

        }

    }
    return NULL;
}

void imprimirPessoa(Ht_item *item)
{
    printf("Chave: %d Nome: %s\n", item->posicao,item->nomeJogador);
}
void imprimirLista(NoLis* inicio)
{
    while(inicio != NULL)
    {
        if(inicio)//evita de imprimir coisa nula
        {
            imprimirPessoa(inicio->item);
            inicio = inicio->next;
        }
    }
}


