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


using namespace std;
//int acessos=0;
//Lista *Tabela[CAPACITY]; ///tabela HASH, variavel global para facilitar

void openRating()
{
    FILE *arq;
    char* fname;
    string line, word;
    char content[1024];
    char *v;


    int idenUser=0;
    int idenFifa=0;
    double notas=0;



//    dadosNotas.rating.reserve(24200000);///aloca espaço no vector
    //  dadosNotas.sofifa_id.reserve(24200000);
    //  dadosNotas.user_id.reserve(24200000);


    arq = fopen("minirating.csv", "r");

    //fstream arq("minirating.csv", ios::in);

    if(arq)
    {
        fgets(content,1024, arq);

        while(fgets(content,1024, arq))
        {
            ///id user, id fifa, rating
            v = strtok(content, ",");
            fname = v;//aqui vai ser o indice da tabela=idUser
            idenUser= (atoi(v));

            v = strtok(NULL, ",");
            idenFifa = (atoi(v));

            v = strtok(NULL, ",");
            notas = (atof(v));

            v = strtok(NULL, ",");

            ///o indice vai ser o id fifa
            inserir(idenFifa, idenUser, notas); ///insere na TabelaidFifa, cujo o indice é id fifa

            InsereUserTab(idenUser, idenFifa, notas);///tabela cujo indice é id user

        }
    }
    else
    {
        cout<< "nao foi possivel abrir o arquivo \n";
        exit;

    }

    fclose(arq);

    cout << "conseguiu colocar tudo";

      //print_table();



    //caso fosse procurar na tabela hash um jogador fifa
    //int chave = 228618;
    //buscar(chave);
    //procurar usuario
    //char key[] = {"52505"};
    //ht_search(52505);

// imprimir();




    /*
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



         como andar pelo vetor e dar print nele, pode ser apagado
        for(int i=9950; i<10001; i++)
        {
            cout << "O user id: " << dadosNotas.user_id[i];
            cout << "\tO sofifa_id e: " << dadosNotas.sofifa_id[i];
            cout << "\tA nota e: " << dadosNotas.rating[i] << endl << endl;
        }
        */


}


///essa função abre o arquivo dos players e insere na arvore
TrieNode* openJog(TrieNode* root, notasUsers dadosRating)
{
    // ACEITA TODoS OS CARACTERES
    char *keys;
    FILE *arq;
    char *separador;
    char linha[1024];
    int idJog;
    char pos[20];
    Jogadores infor;

    Positions posicoes[17];

    strcpy(posicoes[0].pos, "GK");
    strcpy(posicoes[1].pos, "RB");
    strcpy(posicoes[2].pos, "RWB");
    strcpy(posicoes[3].pos, "CB");
    strcpy(posicoes[4].pos, "LB");
    strcpy(posicoes[5].pos, "LWB");
    strcpy(posicoes[6].pos, "CDM");
    strcpy(posicoes[7].pos, "CM");
    strcpy(posicoes[8].pos, "CAM");
    strcpy(posicoes[9].pos, "RM");
    strcpy(posicoes[10].pos, "RW");
    strcpy(posicoes[11].pos, "LM");
    strcpy(posicoes[12].pos, "LW");
    strcpy(posicoes[13].pos, "RF");
    strcpy(posicoes[14].pos, "CF");
    strcpy(posicoes[15].pos, "LF");
    strcpy(posicoes[16].pos, "ST");
    // struct TrieNode *root = getNode();

    arq = fopen("players.csv", "r");

    if(!arq)
    {
        cout << "erro na abertura do arquivo";
    }
    else
    {
        fgets(linha, 1024, arq);
        while(fgets(linha,1024,arq))
        {
            //pega o sofifa_id
            separador = strtok(linha, ",");
            idJog = atoi(separador);

            //com isso tu procura esse sofifa_id na tabela para mesclar os dados com os nomes
            infor = pegaDados(idJog);

            //aqui tu pega o nome do jogador
            separador = strtok(NULL, ",");
            keys = separador;

            //aqui tu pega a posicao dele
            separador = strtok(NULL, "\n");
            strcpy(pos, separador);

            for (int i = 0; i < strlen(keys); i++)
                insert(root, keys,idJog,pos, infor);

               // for(int i=0; i< POS; i++)
                //{
                  //  if()
                //}
            //InsereTabPos(pos, idJog, keys, infor);
        }

    }
    fclose(arq);

    cout << "\ninseriu tudo\n\n";


    return root;

}
