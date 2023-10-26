#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHA_MAX 28  

struct root_node {
    struct root_node* word[ALPHA_MAX];
    bool word_end;
    char* num;
};

int my_atoi(char ch) {
    if (ch == ' ') {
        return 26; 
    } else if (ch >= 'a' && ch <= 'z') {
        return (int)(ch - 'a');
    } else if (ch == '\0') {
        return 27; 
    } else {
        return -1; 
    }
}

struct root_node* init_node(bool end) {
    struct root_node* node = (struct root_node*)malloc(sizeof(struct root_node));
    node->word_end = end;
    node->num = NULL;
    for (int i = 0; i < ALPHA_MAX; i++) {
        node->word[i] = NULL;
    }
    return node;
}

void display_root(struct root_node* node) {
    if (node->word_end == true) {
        printf("* %s\n", node->num);
    }
    for (int i = 0; i < ALPHA_MAX; i++) {
        if (node->word[i] != NULL) {
            display_root(node->word[i]);
        }
    }
}

void AddNode(struct root_node* root, char ch, char str[10], bool end) {
    struct root_node* cnode = init_node(end);
    root->word[my_atoi(ch)] = cnode;
    if (end) {
        cnode->num = strdup(str);
    }
}

void insert_word(struct root_node* root, const char* wr, char str[10]) {
    int len = strlen(wr);
    for (int i = 0; i <= len; i++) { // Include the end-of-string marker '\0'
        int idx = my_atoi(wr[i]);
        if (idx == -1) {
            return; // Invalid character
        }
        if (root->word[idx] == NULL) {
            AddNode(root, wr[i], str, i == len);
        }
        root = root->word[idx];
    }
}

char* search_trie(struct root_node* node, const char* ch) {
    int len = strlen(ch);
    for (int i = 0; i <= len; i++) { // Include the end-of-string marker '\0'
        int idx = my_atoi(ch[i]);
        if (idx == -1) {
            return NULL; // Invalid character
        }
        if (node->word[idx] == NULL) {
            return NULL;
        }
        node = node->word[idx];
    }
    if (node->word_end == true) {
        return node->num;
    }
    return NULL;
}

int main() {
    struct root_node* root = init_node(false);
    insert_word(root, "do ne", "1234567890");
    insert_word(root, "asd rrf", "1234567891");
    insert_word(root, "don fe ", "1234567892");
    insert_word(root, "blast ", "1234567894");
    insert_word(root, "win", "1234567895");
    insert_word(root, "won", "1234567896");
    insert_word(root, "done ", "1234567897");

    char* ans = search_trie(root, "do ne");
    if (ans != NULL) {
        printf("Found: %s\n", ans);
    } else {
        printf("Not found\n");
    }

    //display_root(root);

    free(root);

    return 0;
}
