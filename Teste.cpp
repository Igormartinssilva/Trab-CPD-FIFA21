/*Codigo que abre os arquivos players.csv e coloca numa arvore trie.
Está funcionando bem(Amém)
*/

// C++ implementation of search and insert
// operations on Trie
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

const int ALPHABET_SIZE = 91;
#define CHAR_TO_INDEX(c) ((int)c - (int)' ')
// trie node



typedef struct Jogadores
{
    char *NomeJg;
    int idJog;
    char Pos[20];
};
// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    Jogadores player;
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
struct TrieNode* insert(struct TrieNode *root, char *key, int idJog, char posicao[])
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < strlen(key); i++)
    {
        int index = key[i] - ' ';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
    pCrawl->player.idJog = idJog;
    pCrawl->player.NomeJg = key;
    //pCrawl->player.Pos = posicao;
    strcpy(pCrawl->player.Pos, posicao);

   // cout << posicao<< endl;

    return pCrawl;
}


bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}

// Recursive function to print auto-suggestions for given
// node.
void suggestionsRec(struct TrieNode* root, string currPrefix)
{
    // found a string in Trie with the given prefix
    if (root->isEndOfWord)
    {
        cout << currPrefix;
        cout << "\tdado do jogador: " << root->player.idJog;
        cout << "\tposicao: " << root->player.Pos << endl << endl;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            // child node character value
            char child = ' ' + i;
            suggestionsRec(root->children[i], currPrefix + child);
        }
    }
}

// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root;
    for (char c : query)
    {
        int ind = CHAR_TO_INDEX(c);

        // no string in the Trie has this prefix
        if (!pCrawl->children[ind])
            return 0;

        pCrawl = pCrawl->children[ind];
    }
    // If prefix is present as a word, but
    // there is no subtree below the last
    // matching node.
    if (isLastNode(pCrawl))
    {
        cout << query;
        cout << "dado do jogador: " << pCrawl->player.idJog;
        cout << "posicao: " << pCrawl->player.Pos << endl;
        return -1;
    }
    suggestionsRec(pCrawl, query);
    return 1;
}

// Driver
int main()
{
    // Input keys (use only 'a' through 'z'
    // and lower case)
    char *keys;
    FILE *arq;
    char *separador;
    char linha[1024];
    int idJog;
    char pos[20];
    int w=0;

    struct TrieNode *root = getNode();
    struct TrieNode *raiz = getNode();
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
            separador = strtok(linha, ",");
            idJog = atoi(separador);

            separador = strtok(NULL, ",");
            keys = separador;

            separador = strtok(NULL, "\n");
            //pos = separador;
            strcpy(pos, separador);
            //w++;
            // int n = sizeof(keys)/sizeof(keys[0]);

            //cout << n << endl << endl;
            //cout << keys[w-1];

          //  cout << keys << endl;
            // Construct trie
            for (int i = 0; i < strlen(keys); i++)
                 insert(root, keys,idJog,pos);


        //    cout << "posicao sep:" << separador << endl;
           // cout << "posciao arvore" << raiz->player.NomeJg<< endl<< endl;

        }

    }
    fclose(arq);

    cout << "\ninseriu tudo\n\n";

    printAutoSuggestions(root, "Fer");



    return 0;
}
