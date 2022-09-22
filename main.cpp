#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
#include "csv.h"
#include "Handle.h"
#include "vector"
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

// Driver
int main()
{
    // Input keys (use only 'a' through 'z'
    // and lower case)
    string keys[4];
    int data[4];
    int numJogadores=10000;
    int i;
    char str[20];
    char finded[20] = {"the"};
    TrieNode *root = getNode();



    ///abre o rating e pesquisa todas as avaliações de determinado usuario
  // openRating(root);



  root = openJog(root);


    ///função de pesquisar nome na arvore
    printAutoSuggestions(root,"Fer");

    /*
        // Search for different keys
        search(root, "the")? cout << "Searching for THE: found\n" :
                             cout << "Searching for THE: not found\n";

        */
    return 0;
}
