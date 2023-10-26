#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHA_MAX 27

struct root_node {
    char value;
    struct root_node* word[ALPHA_MAX];
    bool word_end;
};

int my_atoi (char ch)
{
    int i=(int)(ch - 'a');
    if (i==32) return 123;
    else return i;
}

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
    root->word[my_atoi(ch)] = pnode;
}

void insert_word(struct root_node* root, const char* wr) {
    int len = strlen(wr);
    for (int i = 0; i < len - 1; i++) {
        if (root->word[my_atoi(wr[i])] == NULL) {
            AddNode(root, wr[i], false);
        }
        root = root->word[my_atoi(wr[i])];
    }
    char last = wr[len - 1];
    if (root->word[my_atoi(last)] == NULL) {
        AddNode(root, last, true);
    } else {
        root->word[my_atoi(last)]->word_end = true;
    }
}

bool search_trie(struct root_node* node, const char* ch) {
    int len = strlen(ch);
    for (int i = 0; i < len - 1; i++) {
        if (node->word[my_atoi(ch[i])] == NULL) {
            return false;
        }
        if (node->word[my_atoi(ch[i])]->value == ch[i]) {
            node = node->word[my_atoi(ch[i])];
        } else {
            return false;
        }
    }
    if (node->word[my_atoi(ch[len-1])]->value == ch[len - 1]) {
        if (node->word[my_atoi(ch[len-1])]->word_end == true) {
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
    insert_word(root, "done ");
    insert_word(root, "asd3rrf ");
    insert_word(root, "do r3gt4");
    insert_word(root, "dont efk");
    insert_word(root, "blast ");
    insert_word(root, "win");
    insert_word(root, "won");

    display_root(root);
    bool a = search_trie(root, "blast ");
    if (a == true) {
        printf("found\n");
    } else {
        printf("missing\n");
    }

    return 0;
}
