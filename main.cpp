#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
//#include "csv.h"
#include "Handle.h"
#include "vector"
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

// Driver
int main()
{

    string keys[4];
    int data[4];
    int numJogadores=10000;
    int i;
    char str[20];
    char finded[20];
    notasUsers dados;
    char pesquisa[20];
    char pesq[2][10];
    char *pt;
    int z=0;


    struct TrieNode *root = getNode();
    inicializar();//inicializa a tabela hash
    inicializarTabela();

    ///abre o rating e pesquisa todas as avaliações de determinado usuario
    openRating();

    root = openJog(root,dados);

    cout << "Processamento de dados finalizado!\n";

    // juntaDados(root);

    while(1)
    {
        cout << "Efetue a pesquisa:\n";
        getchar();
        scanf("%s", &pesquisa);
        pt = strtok(pesquisa," ");
        while(pt)
        {
            strcpy(pesq[z+1],pt);
            pt=strtok(NULL," ");
            z++;
        }
        if(strcmp(pesq[1],"player")==0)
        {
            printAutoSuggestions(root,pesq[2]);
        }
        else if(strcmp(pesq[1],"user")==0)
        {
            pesquisaUser(atoi(pesq[2]));
        }
        free(pesq);

    }
    return 0;
}
