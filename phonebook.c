
#include <stdio_ext.h>
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

void display_root_helper(struct root_node* node, char str[], int level) {
    if (node->word_end == true) {
        str[level] = '\0'; 
        printf("* %s %s\n", node->num, str);
    }
    for (int i = 0; i < ALPHA_MAX; i++) {
        if (node->word[i] != NULL) {
            str[level] = (i == 26) ? ' ' : (char)('a' + i);
            display_root_helper(node->word[i], str, level + 1);
        }
    }
}

void display_root(struct root_node* root) {
    char str[100]; 
    display_root_helper(root, str, 0);
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
    for (int i = 0; i <= len; i++) { 
        int idx = my_atoi(wr[i]);
        if (idx == -1) {
            return;
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
    char name[64];
    char num[11];
    insert_word(root, "asd rrf", "1234567891");
    insert_word(root, "don fe ", "1234567892");
    insert_word(root, "blast ", "1234567894");
    insert_word(root, "win", "1234567895");
    insert_word(root, "won", "1234567896");
    insert_word(root, "done ", "1234567897");

    char str[100];
        int i=0;
    
    do{

        printf("Select the options --->");
        printf("1. Create a new contact 2. Search the contact 3. Display all the contact 4. Exit");
        scanf("%d",&i);
        switch(i){
                case 1: printf("\n enter list:------------------------------------------\n");
                         printf("Enter name:");
                        __fpurge(stdin);
                        scanf("%[^\n]",name);
                         printf("Enter number:");
                        scanf("%s",num);
                         if(strlen(num)==10 && (int)num[0]>=6){
                            //printf("%s %s",name,num);
                                insert_word(root,name,num);
                            }
                        else{
                                printf("Please re enter the value \n\n");
                                continue;
                            }
                        break;
                case 2: printf("Enter name to search for:");
                         __fpurge(stdin);
                        scanf("%[^\n]",name);
                        char* ans = search_trie(root, name);
                        if (ans != NULL) {
                                 printf("Found: %s\n", ans);
                        } else {
                             printf("Not found\n");
                         }
                        break;
                case 3:
                        display_root(root);
                        break;
        }
    }

    while(i<4);

    free(root);

    return 0;
}