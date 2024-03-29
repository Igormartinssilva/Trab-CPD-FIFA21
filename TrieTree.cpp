
#include <iostream>

#include <string.h>
//#include "csv.h"
#include "Handle.h"
#include <vector>

#include <stdio.h>
#include <stdlib.h>


// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)' ')

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
struct TrieNode* insert(struct TrieNode *root, char *key, int idJog, char posicao[], Jogadores info)
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
    strcpy(pCrawl->player.Pos, posicao);
    pCrawl->player.quantAval =  info.quantAval;
    pCrawl->player.notaMedia =  info.notaMedia;



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
        cout << root->player.idJog <<"\t\t";
        cout << currPrefix <<"\t\t";
        cout << root->player.Pos << "\t\t";
        cout <<root->player.notaMedia <<"\t\t";
        cout <<root->player.quantAval <<"\t\n";
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
        cout << "\tdado do jogador: " << pCrawl->player.idJog;

        cout << "\tavaliacoes: " <<pCrawl->player.quantAval;
        cout << "\tnota media: " <<pCrawl->player.notaMedia;
        cout << "\tposicao: " << pCrawl->player.Pos << endl;

        return -1;
    }
    cout << "sofifa_id \t | Name \t | player_positions \t | rating \t | count\n";
    suggestionsRec(pCrawl, query);
    return 1;
}
