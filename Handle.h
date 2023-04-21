// C++ implementation of search and insert
// operations on Trie
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
//#include "csv.h"
#include "vector"
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

//#define CAPACITY 503 //capacitade da tabela
//#define CAPACITY 2503
//#define CAPACITY 5003
//#define CAPACITY 104003
//#define CAPACITY 7503
#define CAPACITY 157207
#define M 20000
#define POS 17


using namespace std;

const int ALPHABET_SIZE = 91;

///struct dos jogadores, o arquivo player so vai fornecer o nome o id e posicao
typedef struct Jogadores Jogadores;

struct Jogadores
{
    char *NomeJg;
    int idJog;
    char Pos[20];
    double notaMedia;
    double quantAval;

};
// Converts key current character into index
// use only 'a' through 'z' and lower case
//#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
// trie node
struct TrieNode
{
    TrieNode *children[ALPHABET_SIZE];///aqui e a arvore

    Jogadores player;///todos os dados do jogador
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

typedef struct Positions Positions;

struct Positions
{
    char pos[4];
};
///do arquivo Rating, aqui vai todas as notas dos usuarios
///vector e uma lista encadeada, super simples de usar
typedef struct notasUsers notasUsers;

struct notasUsers
{
    int user_id;
    int sofifa_id[200];
    float notas[200];

};
//--------------------------------------------------------tabela hash e lista encadeada da tabela-------------------------------------------
typedef struct Ht_item Ht_item;

///Define o item da tabela Hash
struct Ht_item
{
    char* indice;         ///isso era char* key, vai ser a posição dele na tabela, será o mesmo valor que id_user
    int id_user;        ///isso era char* value, trocar tudos value por essa nova variavel

    int sofifa_id;      ///aqui começa os dados dos jogadores avaliados pelo usuario
    char *nomeJogador;
    float notaMedia;
    int quantAval;
    float notaUserJog;


    unsigned long posicao; ///vai guardar a posição dele na tabela, util nas estatisticas
};

typedef struct NoLis NoLis ;

struct NoLis
{
    Ht_item* item;
    notasUsers user;
    NoLis* next;
};

typedef struct Lista Lista;

struct Lista
{
    NoLis *inicio;
    int tam;
};
typedef struct{
     int sofifa_id;      ///aqui começa os dados dos jogadores avaliados pelo usuario
    int id_user;
    float notaMedia;
    int quantAval;
    float notaUserJog;
}DadosRating;


TrieNode *getNode();///nao sei o que faz, acho que cria um nodo novo na arvore
struct TrieNode* insert(struct TrieNode *root, char *key, int idJog, char posicao[], Jogadores info);/// funçao para inserir na arvore
bool search(TrieNode *root, string key);/// função paraprcurar palavra, ACHO que nao foi ultilizado, tava no cod do comba
bool isLastNode(TrieNode* root);///função para marcar que e o ultimo nodo
void suggestionsRec(TrieNode* root, string currPrefix);///função que faz parte da auto sugestao
int printAutoSuggestions(TrieNode* root, const string query);///função para autosugerir nomes que estao na arvore
//funçoes de abrir o arquivo
void openRating();///funçao para abrir as avaliçoes dos usuarios e inserir na struct ESTA OK
TrieNode* openJog(TrieNode* root, notasUsers dadosRating);///essa função abre o arquivo dos players e insere na arvore COM PROBLEMAS
Jogadores juntaDados(int idFifa,notasUsers dados);
///--------------------------------Lista encadea e tabela hash-------------------------------------------------------------------
Lista* criarLista();
Lista* insereOrdenado(Ht_item* item, Lista *lista);
NoLis* buscarNo(char *mat, NoLis* inicio);
void imprimirPessoa(Ht_item *item);
void imprimirLista(NoLis* inicio);
Lista* insereInicio(Ht_item* item, Lista *lista);
void insereUser(Ht_item* item, Lista *lista);

unsigned long hash_function(char* str);
void inicializar();
Ht_item* create_item(char* indice, int idUser, int idJog, double notUsua);
void inserTabela(char* indice, int idUser, int idJog, double notUsua);
int ht_search(int key);
void print_table();
int contaVal();
void InsereUserTab(int key, int sofifa_id, float nota);
NoLis* achaUser(int key);

///--------- tabela inteira----
void buscar(int chave);
void inserir(int idJog, int idUser, float nota);
int gerarCodigoHash(int chave);
void inicializarTabela();
void imprimir();

Jogadores pegaDados(int idJog);
int pesquisaUser(int key);
void quicksort_hoare(float *v, int *v2, int s, int e);
