#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int count;
    struct trie* next[26];
};

struct Trie *createTrie()
{
    struct Trie* temp = malloc(sizeof(struct Trie));
    temp->count = 0;

    for (int i=0; i<26; i++)
        temp->next[i] = NULL;
    return temp;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    if (word[0] == '\0')
    {
        pTrie->count++;
        return;
    }

    int nextIndex = word[0] - 'a';
    if (pTrie->next[nextIndex] == NULL)
        pTrie->next[nextIndex] = createTrie();

    insert(pTrie->next[nextIndex], word+1);
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int nextIndex = word[0] - 'a';

    if (word[0] == '\0')
        return pTrie->count;

    if (pTrie->next[nextIndex] != NULL)
        return numberOfOccurances(pTrie->next[nextIndex], word+1);

    return 0;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for (int i=0; i<26; i++)
        if (pTrie->next[i] != NULL)
            deallocateTrie(pTrie->next[i]);

    free(pTrie);

    return NULL;
}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fp;
    fp = fopen(filename, "r");
    int count;
    fscanf(fp, "%d", &count);



    for (int i = 0; i < count; i++)
    {
        pInWords[i] = malloc(256);
        fscanf(fp, "%s", pInWords[i]);
    }

    return count;
}

int main(void)
{
	char *inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}

	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
