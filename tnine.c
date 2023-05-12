/* Copyright [2023] <Tongxin Chen>"  [legal/copyright]    
    Author: Tongxin Chen
    UWNetID: tongxc
    Assignment: Homework5 tnine.c
    Date: May 12, 2023
*/ 
/* tnine is a program that drives a trie / t9 program.  This code
   will build a trie, according to trienode.  It will also run
   an interactive session where the user can retrieve words using
   t9 sequences.
   CSE374, HW5, 23sp
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

// run_session run the on-going decoding interaction with the
// user.  It requires a previously build wordTrie to work.
void run_session(trieNode *wordTrie);

int main(int argc, char **argv) {
  FILE *dictionary = NULL;
  trieNode *wordTrie = NULL;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [DICTIONARY]\n", argv[0]);
    return EXIT_FAILURE;
  } else {
    dictionary = fopen(argv[1], "r");
    if (!dictionary) {
      fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
      return EXIT_FAILURE;
    }
  }

  // build the trie
  wordTrie = build_tree(dictionary);
  fclose(dictionary);

  // run interactive session
  printf("Enter 'exit' to quit.\n");
  run_session(wordTrie);

  // clean up
  free_tree(wordTrie);

  return(EXIT_SUCCESS);
}

void run_session(trieNode *wordTrie) {
  for (;;) {
    char input;
    printf("Enter Key Sequence (or '#' for next word):\n");
    scanf("%s", &input);
    int input_length = strlen(&input);
    char *pattern = calloc(input_length, sizeof(char));
    strncpy(pattern, &input, input_length);
    if (strcmp(pattern, "exit") == 0) {
        return;  // exit the loop
    } else {
      char *result = get_word(wordTrie, pattern);
      printf("'%s'\n", result);
      free(result);
    }
    free(pattern);
  }
}
