#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
#include "csv.h"
#include "Handle.h"

using namespace std;


// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')


// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode()
{
    ///aloca espaço oara o nodo
    struct TrieNode *pNode =  new TrieNode;

    ///fim da arvore recebe falso, pois tem mais coisa para add
    pNode->isEndOfWord = false;
    ///o vetor de letras fica zerado
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key, int data)
{
    ///inicia o no raiz
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        ///cria um novo nó se o caminho não existir
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        ///vai para o proximo nó
        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
    pCrawl->id=data;

}

// Returns true if key presents in trie, else
// false
bool search(struct TrieNode *root, string key)
{
    ///retorna False se a aravore estiver vazia
    if(root == nullptr)
        return false;


    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        ///se a string for invalida(alcançou o final de um caminho)
        if (!pCrawl->children[index])
            return false;

        ///vai para o proximo no
        pCrawl = pCrawl->children[index];
    }

    ///retorna true se o no atual for uma folha e o
    ///fim da string é atingido
    return (pCrawl != NULL && pCrawl->isEndOfWord);
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
        cout << currPrefix << endl;
        cout << "dado do jogador: " << root->id;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            // child node character value
            char child = 'a' + i;
            suggestionsRec(root->children[i], currPrefix + child);
        }
    }
}

// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root;
    for (char c : query) {
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
        cout << query << endl;
        cout << "dado do jogador: " << pCrawl->id;
        return -1;
    }
    suggestionsRec(pCrawl, query);
    return 1;
}
