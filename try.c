#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char word[100];
char **words = NULL;
int num_words = 0;

//DECLARATIVE STATEMENTS
int pos;

void parse_declaration();
void parse_declarator();
void parse_initializer();

void parse_declaration() {
    if (strncmp(words[pos], "int", 3) == 0) {
        pos += 3;
        parse_declarator();
        printf("Found int declaration\n");
    } 
    else if (strncmp(words[pos], "char", 4) == 0) {
        pos += 4;
        parse_declarator();
        printf("Found char declaration\n");
    } 
    else if (strncmp(words[pos], "float", 5) == 0) {
        pos += 5;
        parse_declarator();
        printf("Found float declaration\n");
    }
    else {
        printf("Invalid declaration\n");
    }
}

void parse_declarator() {
    while (word[pos] != ';') {
        if (word[pos] == '=') {
            pos++;
            parse_initializer();
        }
        pos++;
    }
}

void parse_initializer() {
    while (word[pos] != ';') {
        pos++;
    }
}

int main() {
    FILE *file;
    char *filename = "file.txt";

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (fscanf(file, "%s", word) != EOF) {
        words = (char **) realloc(words, (num_words + 1) * sizeof(char *));
        words[num_words] = (char *) malloc((strlen(word) + 1) * sizeof(char));
        strcpy(words[num_words], word);
        num_words++;
    }

    fclose(file);

    parse_declaration();
    // printf("%s", words[pos+1]);

    // Print the words in the array
    // for (int i = 0; i < num_words; i++) {
    //     printf("%s\n", words[i]);
    // }

    // Deallocate memory
    for (int i = 0; i < num_words; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}
