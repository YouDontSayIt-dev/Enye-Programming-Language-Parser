#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char word[100];
char **words = NULL;
int num_words = 0;
int pos;
int expected;

void assignment();
void expression();
void term();
void factor();

void match(char* expected) {
    if (strcmp(words[pos], expected) == 0) {
        pos++;
    } else {
        printf("Error: unexpected token %s\n", words[pos]);
        exit(1);
    }
}

void match2(char** expected, int i) {
    if (strcmp(words[pos], expected[i]) == 0) {
        pos++;
    } else {
        printf("Error: unexpected token %s\n", words[pos]);
        exit(1);
    }
}

// Function to parse output statements
void output_statement() {
    match("PRINTF_KW");
    // match2(words, pos);
    expression();
    printf("Found output statement");
}

void expression() {
    term();
    while (strcmp(words[pos], "ADD_OPR") == 0 || strcmp(words[pos], "SUBT_OPR") == 0) {
        match2(words, pos);
        term();
    }
}

void term() {
    factor();
    while (strcmp(words[pos], "MULT_OPR") == 0 || strcmp(words[pos], "DIV_OPR") == 0) {
        match2(words, pos);
        factor();
    }
}

void factor() {
    if (strcmp(words[pos], "REAL_NUMBER") == 0 || strcmp(words[pos], "INTEGER") == 0) {
        match(words[pos]);
    } else if (strcmp(words[pos], "IDENTIFIER") == 0) {
        match(words[pos]);
    } else if (strcmp(words[pos], "LEFT_PARENTHESIS") == 0) {
        match("LEFT_PARENTHESIS");
        expression();
        match("RIGHT_PARENTHESIS");
    }else {
        printf("Error: unexpected token %s\n", words[pos]);
        exit(1);
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

    // assignment();
    output_statement();
    // printf("%s", words[pos]);

    // Deallocate memory
    for (int i = 0; i < num_words; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}
