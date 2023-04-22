#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TrieNode {
    struct TrieNode *children[26];
    int count;
};

typedef struct TrieNode Trie;

void insert(Trie **ppTrie, char *word)
{
    if (*ppTrie == NULL) 
    {
        *ppTrie = (Trie *) malloc(sizeof(Trie));
        (*ppTrie)->count = 0;
        
        for (int i = 0; i < 26; i++)
        {
            (*ppTrie)->children[i] = NULL;
        }
    }
    
    Trie *pNode = *ppTrie;

    for (int i = 0; i < strlen(word); i++) 
    {
        int index = word[i] - 'a';

        if (pNode->children[index] == NULL) 
        {
            pNode->children[index] = (Trie *)malloc(sizeof(Trie));
            pNode->children[index]->count = 0;
            
            for (int j = 0; j < 26; j++)
            {
                pNode->children[index]->children[j] = NULL;
            }
        }

        pNode = pNode->children[index];
    }
    
    pNode->count++;
}

int numberOfOccurances(Trie *pTrie, char *word)
{
    Trie *pNode = pTrie;

    for (int i = 0; i < strlen(word); i++) 
    {
        int index = word[i] - 'a';

        if (pNode->children[index] == NULL) 
        {
            return 0;
        }

        pNode = pNode->children[index];
    }
    
    return pNode->count;
}

Trie *deallocateTrie(Trie *pTrie)
{
    if (pTrie != NULL) 
    {
        for (int i = 0; i < 26; i++) 
        {
            pTrie->children[i] = deallocateTrie(pTrie->children[i]);
        }

        free(pTrie);
    }

    return NULL;
}

int main(void)
{
    // read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    Trie *trie = NULL;

    for (int i = 0; i < 5; i++)
    {
        insert(&trie, pWords[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d", pWords[i], numberOfOccurances(trie, pWords[i]));

        if (i < 4)
        {
            printf("\n");
        }
    }

    trie = deallocateTrie(trie);

    if (trie != NULL)
    {
        printf("Error: Trie not deallocated\n");
    }

    return 0;
}
