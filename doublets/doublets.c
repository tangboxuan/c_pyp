#include "doublets.h"

/* ------------------ YOUR CODE HERE ------------------- */

#define ALPHABET_SIZE 26

bool valid_step(dictionary_t *dict, const char *curr_word, const char *next_word) {
  int len = strlen(curr_word);
  int diff = 0;
  if (len  == strlen(next_word) && find(dict, next_word)) {
    for (int i = 0; i < len; i++) {
      if (curr_word[i] != next_word[i]) {
        diff++;
      }
    }
    if (diff == 1) {
      return true;
    }
  }
  return false;
}

void print_chain(const char **chain) {
  char copy[MAX_WORD_SIZE];
  for (int i = 0; chain[i] != NULL; i++) {
    for (int j = 0; j < strlen(chain[i]); j++) {
      if (i == 0 || chain[i+1] == NULL) {
        copy[j] = toupper(chain[i][j]);
      } else {
        copy[j] = tolower(chain[i][j]);
      }
    }
    printf("%s\n", copy);
  }
}

bool valid_chain(dictionary_t *dict, const char **chain) {
  for (int i = 0; chain[i + 1]; i++) {
    if (!valid_step(dict, chain[i], chain[i+1])) {
      return false;
    }
  }
  return true;
}


bool find_chain_helper(dictionary_t *dict, const char *start_word, 
                const char *target_word, const char **chain, int max_words, int pos) {
  if (max_words == 2) {
    if(valid_step(dict, start_word, target_word)) {
      chain[pos] = calloc(MAX_WORD_SIZE, sizeof(char));
      strcpy(chain[pos], target_word);
      chain[pos+1] = NULL;
      return true;
    } else {
    return false;
    }
  }
  char *temp = calloc(MAX_WORD_SIZE, sizeof(char));
  for (int i = 0; i < strlen(start_word); i++) {
    for (int j = 0; j < ALPHABET_SIZE; j++) {
      strcpy(temp, start_word);
      temp[i] = j + 'A';
      if (valid_step(dict, start_word, temp)) {
        if (find_chain_helper(dict, temp, target_word, chain, max_words - 1, pos + 1)) {
          chain[pos] = temp;
          return true;
        }
      }
    }
  }
  free(temp);
  return false;
}

bool find_chain(dictionary_t *dict, const char *start_word, 
                const char *target_word, const char **chain, int max_words) {
  if (find_chain_helper(dict, start_word, target_word, chain, max_words, 1)) {
    chain[0] = calloc(MAX_WORD_SIZE, sizeof(char));
    strcpy(chain[0], start_word);
    return true;
  }
  return false;
}
