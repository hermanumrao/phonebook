#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHA_MAX 26

struct root_node {
    char value;
    struct root_node* word[ALPHA_MAX];
    bool word_end;
};

struct root_node* init_node(char ch, bool end) {
    struct root_node* node = (struct root_node*)malloc(sizeof(struct root_node));
    node->value = ch;
    node->word_end = end;
    for (int i = 0; i < ALPHA_MAX; i++) {
        node->word[i] = NULL;
    }
    return node;
}

void display_root(struct root_node* node) {
    printf("%c", node->value);
    if (node->word_end == true) {
        printf("*");
    }
    printf("\n");
    for (int i = 0; i < ALPHA_MAX; i++) {
        if (node->word[i] != NULL) {
            display_root(node->word[i]);
        }
    }
}

void AddNode(struct root_node* root, char ch, bool end) {
    struct root_node* pnode = init_node(ch, end);
    root->word[(int)(ch - 'a')] = pnode;
}

void insert_word(struct root_node* root, const char* wr) {
    int len = strlen(wr);
    for (int i = 0; i < len - 1; i++) {
        if (root->word[(int)(wr[i] - 'a')] == NULL) {
            AddNode(root, wr[i], false);
        }
        root = root->word[(int)(wr[i] - 'a')];
    }
    char last = wr[len - 1];
    if (root->word[(int)(last - 'a')] == NULL) {
        AddNode(root, last, true);
    } else {
        root->word[(int)(last - 'a')]->word_end = true;
    }
}

bool search_trie(struct root_node* node, const char* ch) {
    int len = strlen(ch);
    for (int i = 0; i < len - 1; i++) {
        if (node->word[(int)(ch[i] - 'a')] == NULL) {
            return false;
        }
        if (node->word[(int)(ch[i] - 'a')]->value == ch[i]) {
            node = node->word[(int)(ch[i] - 'a')];
        } else {
            return false;
        }
    }
    if (node->word[(int)(ch[len - 1] - 'a')]->value == ch[len - 1]) {
        if (node->word[(int)(ch[len - 1] - 'a')]->word_end == true) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

int main() {
    struct root_node* root = init_node('_', true);
    insert_word(root, "done");
    insert_word(root, "asd");
    insert_word(root, "do");
    insert_word(root, "dont");
    insert_word(root, "blast");
    insert_word(root, "win");
    insert_word(root, "won");

    display_root(root);
    bool a = search_trie(root, "rt3tg");
    if (a == true) {
        printf("found\n");
    } else {
        printf("missing\n");
    }

    return 0;
}
