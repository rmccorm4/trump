#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MIN 3
#define VALID(c) ( (((c) >= '0') && ((c) <= '9')) || (((c) >= 'A') && ((c) <= 'Z')) || (((c) >= 'a') && ((c) <= 'z')) || ((c) == '-'))

struct wordNode {
	char *word;
	int count;
	struct wordNode *left;
	struct wordNode *right;
};

char* nextWord()
{
	int i;
	char *start, word[256] = "";

	if(scanf(" %s", word) != 1) return NULL;

	start = word;	
	for(i = 0; word[i] != '\0'; i++) {
		if(VALID(word[i])) {
			start = word + i;
			break;
		}
	}

	for(i = 0 ; start[i] != '\0'; i++) {
		if(!VALID(start[i])) {
			start[i] = '\0';
			break;
		}
	}

	return strdup(start);
}

struct wordNode* makeWordNode(char *word)
{
	struct wordNode *result = (struct wordNode *)malloc(sizeof(struct wordNode));
	result->word = word;
	result->count = 1;
	result->left = result->right = NULL;
	return result;
}

void freeWords(struct wordNode *root)
{
	if(root == NULL) return;

	if(root->left != NULL) freeWords(root->left);
	if(root->right != NULL) freeWords(root->right);
	free(root->word);
	free(root);
}

void insert(struct wordNode *root, char *word)
{
	int order;
	
	if(word != NULL) {
		order = strcasecmp(root->word, word);
		if((order == 0)) {
			root->count++;
		} else if(order > 0) {
			if(root->left == NULL) root->left = makeWordNode(word);
			else insert(root->left, word);
		} else {
			if(root->right == NULL) root->right= makeWordNode(word);
			else insert(root->right, word);
		}
	}

	return;
}

void addWordByCount(struct wordNode *toRoot, struct wordNode *fromRoot)
{
	int order;

	if(fromRoot != NULL) {

		addWordByCount(toRoot, fromRoot->left);
		fromRoot->left = NULL;

		addWordByCount(toRoot, fromRoot->right);
		fromRoot->right = NULL;

		order = toRoot->count - fromRoot->count;
		if(order == 0) {
			order = strcasecmp(toRoot->word, fromRoot->word);
			if(order == 0) {
				toRoot->count += fromRoot->count;
			} else if(order > 0) {
				if(toRoot->left == NULL) toRoot->left = fromRoot;
				else addWordByCount(toRoot->left, fromRoot);
			} else {
				if(toRoot->right == NULL) toRoot->right = fromRoot;
				else addWordByCount(toRoot->right, fromRoot);
			}
		} else if(order > 0) {
			if(toRoot->left == NULL) toRoot->left = fromRoot; 
			else addWordByCount(toRoot->left, fromRoot);
		} else {
			if(toRoot->right == NULL) toRoot->right= fromRoot;
			else addWordByCount(toRoot->right, fromRoot);
		}
	}
	
	return;
}

void reportTree(struct wordNode *root)
{
	if(root == NULL) return;

	reportTree(root->left);
	if(root->count >= MIN) printf("%3d: %s\n", root->count, root->word);
	reportTree(root->right);
}
	
int main(int argc, char *argv[])
{
	char *word;
	struct wordNode *alfaRoot, *bcRoot;

	word = nextWord();
	
	if(word != NULL) {
		alfaRoot = makeWordNode(word);
		while((word = nextWord()) != NULL) {
			insert(alfaRoot, word);
		}
	}
	
	bcRoot = makeWordNode(strdup(""));
	addWordByCount(bcRoot, alfaRoot);

	reportTree(bcRoot);
	
	freeWords(bcRoot);

	return 0;
}
