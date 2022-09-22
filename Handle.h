// C++ implementation of search and insert
// operations on Trie
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
#include "csv.h"
#include "vector"
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

//#define CAPACITY 503 //capacitade da tabela
//#define CAPACITY 2503
//#define CAPACITY 5003
//#define CAPACITY 104003
#define CAPACITY 7503

using namespace std;

const int ALPHABET_SIZE = 28;

///struct dos jogadores, o arquivo player so vai fornecer o nome o id e posicao
typedef struct Jogadores
{
    int soFifaJog_id;
    char nomeJog[100];
    string position;
    double notaMedia;
    double quantAval;

};
// Converts key current character into index
// use only 'a' through 'z' and lower case
//#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
// trie node
typedef struct TrieNode
{
    TrieNode *children[ALPHABET_SIZE];///aqui e a arvore

    Jogadores player;///todos os dados do jogador
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};


///do arquivo Rating, aqui vai todas as notas dos usuarios
///vector e uma lista encadeada, super simples de usar
typedef struct notasUsers
{
    vector<string> user_id;
    vector<string> sofifa_id;
    vector<string> rating;

};
//--------------------------------------------------------tabela hash e lista encadeada da tabela-------------------------------------------
typedef struct Ht_item Ht_item;

///Define o item da tabela Hash
struct Ht_item
{
    int indice;         ///isso era char* key, vai ser a posição dele na tabela, será o mesmo valor que id_user
    int id_user;        ///isso era char* value, trocar tudos value por essa nova variavel

    int sofifa_id;      ///aqui começa os dados dos jogadores avaliados pelo usuario
    char *nomeJogador;
    int notaMedia;
    int quantAval;
    int notaUserJog;


    unsigned long posicao; ///vai guardar a posição dele na tabela, util nas estatisticas
};

typedef struct NoLis NoLis ;

struct NoLis
{
    Ht_item* item;
    NoLis* next;
};

typedef struct Lista Lista;

struct Lista
{
    NoLis *inicio;
    int tam;
};


TrieNode *getNode();///nao sei o que faz, acho que cria um nodo novo na arvore
void insert(TrieNode *root, char key[], int sofifa, string posicao);/// funçao para inserir na arvore
bool search(TrieNode *root, string key);/// função paraprcurar palavra, ACHO que nao foi ultilizado, tava no cod do comba
bool isLastNode(TrieNode* root);///função para marcar que e o ultimo nodo
void suggestionsRec(TrieNode* root, string currPrefix);///função que faz parte da auto sugestao
int printAutoSuggestions(TrieNode* root, const string query);///função para autosugerir nomes que estao na arvore
void openRating(TrieNode* root);///funçao para abrir as avaliçoes dos usuarios e inserir na struct ESTA OK
TrieNode* openJog(TrieNode* root);///essa função abre o arquivo dos players e insere na arvore COM PROBLEMAS

///--------------------------------Lista encadea e tabela hash-------------------------------------------------------------------
Lista* criarLista();
Lista* insereInicio(Ht_item* item, Lista *lista);
NoLis* buscarNo(char *mat, NoLis* inicio);
void imprimirPessoa(Ht_item *item);
void imprimirLista(NoLis* inicio);
unsigned long hash_function(int str);
void inicializar();
Ht_item* create_item(int indice, int idUser, int idJog, char* key, int notaMed,int quantAval, int notUsua);
void inserTabela( int indice, int idUser, int idJog, char* key, int notaMed,int quantAval, int notUsua);
int ht_search(int key);
void print_table();
int contaVal();


