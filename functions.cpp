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

using namespace std;
//int acessos=0;
//Lista *Tabela[CAPACITY]; ///tabela HASH, variavel global para facilitar


void openRating(TrieNode *root)
{
    FILE *arq;
    string fname;
    string line, word;
    char content[1024];
    char *v;
    char* procurado = {"118046"};
    float i=0;
    int vintPrint=0;
    notasUsers dadosNotas;

    dadosNotas.rating.reserve(24200000);///aloca espaço no vector
    dadosNotas.sofifa_id.reserve(24200000);
    dadosNotas.user_id.reserve(24200000);


    arq = fopen("rating.csv", "r");

    //fstream arq("minirating.csv", ios::in);

    if(arq)
    {
        fgets(content,1024, arq);

        while(fgets(content,1024, arq))
        {
            v = strtok(content, ",");

            //pelo jeito que fiz, acho que nem precisa do while, mas time que ta ganhando nao se meche, ta funcioando bem
            while(v)
            {
                ///funçao push_back insere no fim do vetor
                dadosNotas.user_id.push_back(v);
                v = strtok(NULL, ",");
                dadosNotas.sofifa_id.push_back(v);
                v = strtok(NULL, ",");
                dadosNotas.rating.push_back(v);
                v = strtok(NULL, ",");
            }
        }
    }
    else
    {
        cout<< "nao foi possivel abrir o arquivo \n";
        exit;

    }

    fclose(arq);

    cout << "conseguiu colocar tudo";


    cout << "o max size e : " << dadosNotas.user_id.size() << endl << endl;///da print para saber a quantidade de dados tem no vetor

    ///percorre todo o vetor e caso ja tenha dado 20 print, fecha a função, se for dar todos print da pau
    while(i < dadosNotas.user_id.size() && vintPrint != 20)
    {
        if(dadosNotas.user_id[i] == procurado)
        {
            cout << "idFifa: "<< dadosNotas.sofifa_id[i];
            cout << "\t Nota do user para jog: " << dadosNotas.rating[i] << endl<<endl;
            vintPrint++;
            cout << vintPrint;
        }
        i++;
    }



    /* como andar pelo vetor e dar print nele, pode ser apagado
    for(int i=9950; i<10001; i++)
    {
        cout << "O user id: " << dadosNotas.user_id[i];
        cout << "\tO sofifa_id e: " << dadosNotas.sofifa_id[i];
        cout << "\tA nota e: " << dadosNotas.rating[i] << endl << endl;
    }
    */
}

TrieNode* raiz;
///essa função abre o arquivo dos players e insere na arvore
TrieNode* openJog(TrieNode* root)
{
    int i=0;
    FILE *arq;
    char linha[5024];
    char *separador;
    int idJog;
    char nomeJog[100];
    char especial[]={"'"};
    char nomeJogmin[100];
    string posicaoGeral;
    root = getNode();
    arq = fopen("players.csv", "r");


    raiz = (TrieNode*) malloc(sizeof(TrieNode));
     raiz = getNode();
    if(!arq)
    {
        cout << "erro na abertura do arquivo";
    }
    else
    {
        cout << "erro na abertura do arquivaaaaaaaaaaao";
        fgets(linha,10024,arq);
        while(fgets(linha,10024,arq))
        {
            separador = strtok(linha, ",");
          //  printf("\n\npegando os dados: %s %s", nomeJog,posicao);

            idJog = atoi(separador);
            separador = strtok(NULL, ",");
            //nomeJog = separador;
            strcpy(nomeJog,separador);
            separador = strtok(NULL, "\n");
            posicaoGeral = separador;


            while(nomeJog[i] != '\0')
            {
                nomeJogmin[i]=tolower(nomeJog[i]);
                if(nomeJogmin[i]== especial[0] )
                {
                    nomeJogmin[i] = ' ';
                }

                i++;
            }
            i=0;

     cout << "\n\n!- " << nomeJogmin;


     for(i=0;i<strlen(nomeJogmin);i++)
    {
            ///insere na arvore
            insert(raiz, nomeJogmin, idJog, posicaoGeral);
    }
    i=0;


            ///era para dar print mostrando que achou o Messi, mas da erro, eu vi tbm que anda bugando o nome dele na hora de dar print na arvore


             //separador = strtok(NULL, ",");


            idJog=0;
            while(nomeJog[i] != '\0' )
            {
                nomeJog[i]='\0';
                nomeJogmin[i]='\0';
                i++;
            }
            i=0;

        }

        cout << "\n\nconseguiu pegar todos os dados\n\n";

    }
    fclose(arq);

    printAutoSuggestions(raiz,"Lio");

    return root;

}






