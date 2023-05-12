/* Copyright [2023] <Tongxin Chen>"  [legal/copyright]    
    Author: Tongxin Chen
    UWNetID: tongxc (2068798)
    Assignment: Homework5 trie.c
    Date: May 12, 2023
*/ 
/* trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
   CSE374, HW5, 23sp
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "trienode.h"

/* You'll want to prototype any helper functions you need here */
trieNode* make_node();
int get_key(char character);
/* You'll need to implement the functions declare in trienode.h */
/* As well as the helpfer functions you prototype above. */

// struct trieNode *branches[BRANCHES]; char word;
// given a word list (dict), build a trie that holds
// each word.  Return pointer to the root node.
trieNode* build_tree(FILE *dict) {
    trieNode* node = make_node();
    char cur_word[MAXLEN];
    while (fgets(cur_word, MAXLEN, dict) != NULL) {
        int word_length = strlen(cur_word);
        int key;
        for (int j = 0; j < word_length - 1; j++) {
            key = get_key(cur_word[j]) - 1;
            if (node->branches[key] == NULL) {
                node->branches[key] = make_node();
            }
            node = node->branches[key];
        }
        // The key for the last character
        key = get_key(cur_word[word_length - 1]) - 1;
        node = node->branches[key];
        // Check if a word with the same numeric sequence already exists
        while (node->word != NULL) {
            node->branches[key] = make_node();  // make new branches
            key = 0;  // # = 0
            node = node->branches[key];  // current node is at branch #
        }
        node->word = cur_word;
    }
    return node;
}

// Create the new trie branches
trieNode* make_node() {
    trieNode* node = (trieNode*)  malloc(sizeof(trieNode));
    node->word = NULL;
    for (int i = 0; i < BRANCHES; i++) {
        node->branches[i] = NULL;
    }
    return node;
}

// convert a letter to a numerical key using T9
int get_key(char character) {
    character = tolower(character);
    int key;
    if (character == 'a' || character == 'b' || character == 'c') {
        key = 2;
    } else if (character == 'd' || character == 'e' || character == 'f') {
        key = 3;
    } else if (character == 'g' || character == 'h' || character == 'i') {
        key = 4;
    } else if (character == 'j' || character == 'k' || character == 'l') {
        key = 5;
    } else if (character == 'm' || character == 'n' || character == 'o') {
        key = 6;
    } else if (character == 'p' || character == 'q' || character == 'r' || \
                character == 's') {
        key = 7;
    } else if (character == 't' || character == 'u' || character == 'v') {
        key = 8;
    } else if (character == 'w' || character == 'x' || character == 'y' || \
                character == 'z') {
        key = 9;
    }
    return key;
}

// given a pattern, return the word stored in the
// appropriate trieNode
char* get_word(trieNode *root, char *pattern) {
    char *result;
    int length = strlen(pattern);
    for (int i = 0; i < length; i++) {
        char cur_char = pattern[i];
        if (root == NULL) {
            printf("Can not find any words corresponding to input pattern.\n");
            break;
        } else {
            if (cur_char != '#' && cur_char != '2' && \
                cur_char != '3' && cur_char != '4' && \
                cur_char != '5' && cur_char != '6' && \
                cur_char != '7' && cur_char != '8' && \
                cur_char != '9') {
                fprintf(stderr, \
                        "Input Pattern Error: Cannot find the symbol %c\n", \
                        cur_char);
            } else if (cur_char == '#') {
                root = root->branches[0];
            } else if (cur_char == '2') {
                root = root->branches[1];
            } else if (cur_char == '3') {
                root = root->branches[2];
            } else if (cur_char == '4') {
                root = root->branches[3];
            } else if (cur_char == '5') {
                root = root->branches[4];
            } else if (cur_char == '6') {
                root = root->branches[5];
            } else if (cur_char == '7') {
                root = root->branches[6];
            } else if (cur_char == '8') {
                root = root->branches[7];
            } else if (cur_char == '9') {
                root = root->branches[8];
            }
        }
    }
    result = root->word;
    return result;
}

// deletes the entire tree branching from root
void free_tree(trieNode *root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0 ; i < BRANCHES; i++) {
        free_tree(root->branches[i]);
    }
    free(root);
}
