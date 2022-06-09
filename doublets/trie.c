#include "trie.h"

dictionary_t *create_dict(void) {
  return create_node();
}

void free_dict(dictionary_t *root) {
  free_node(root);
}

/* ------------ YOUR CODE BELOW -------------- */

#define ALPHABET_SIZE 26
#define MAXIMUM_WORD_SIZE 20

bool find(dictionary_t *root, const char *word) {
  dictionary_t *pointer = root;
  for (int i = 0; i < strlen(word); i++) {
    if (word[i] < 'A' || word[i] > 'Z') {
      return false;
    }
    int no = word[i] - 'A';
    if (pointer->children[no] == NULL) {
      return false;
    }
    pointer = pointer->children[no];
  }
  return pointer->end_of_word;
}

bool insert(dictionary_t *root, const char *word) {
  dictionary_t *pointer = root;
  for (int i = 0; i < strlen(word); i++) {
    if (word[i] == '\n') {
      continue;
    }
    if (word[i] < 'A' || word[i] > 'Z') {
      return false;
    }
    int no = word[i] - 'A';
    if (pointer->children[no] == NULL) {
      pointer->children[no] = create_node();
    }
    pointer = pointer->children[no];
  }
  pointer->end_of_word = true;
  return true;
}

dictionary_t *create_node(void) {
  dictionary_t *node = malloc(sizeof(dictionary_t));
  node->children = calloc(ALPHABET_SIZE, sizeof(dictionary_t*));
  node->end_of_word = false;
  return node;
}

void free_node(dictionary_t *root) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (root->children[i] != NULL) {
      free_node(root->children[i]);
    }
  }
  free(root->children);
  free(root);
}

bool load_from_file(dictionary_t *root, const char *filename) {
  char buffer[MAXIMUM_WORD_SIZE];
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    return false;
  }
  while(fgets(buffer, MAXIMUM_WORD_SIZE, fp) != NULL) {
    insert(root, buffer);
  }
  return true;
}


