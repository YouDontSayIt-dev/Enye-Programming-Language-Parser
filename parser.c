
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lookahead;

void match(int);
void assignment();
void expression();
void term();
void factor();

void match(int expected) {
    if (lookahead == expected) {
        lookahead = getchar();
    } else {
        printf("Error: unexpected token %c\n", lookahead);
        exit(1);
    }
}

void assignment() {
    char variable = lookahead;
    match(lookahead);
    match('=');
    expression();
    match(';');
    printf("Assigning value to variable %c\n", variable);
}

void expression() {
    term();
    while (lookahead == '+' || lookahead == '-') {
        match(lookahead);
        term();
    }
}

void term() {
    factor();
    while (lookahead == '*' || lookahead == '/') {
        match(lookahead);
        factor();
    }
}

void factor() {
    if (lookahead >= '0' && lookahead <= '9') {
        match(lookahead);
    } else if (lookahead >= 'a' && lookahead <= 'z') {
        match(lookahead);
    } else if (lookahead == '(') {
        match('(');
        expression();
        match(')');
    } else {
        printf("Error: unexpected token %c\n", lookahead);
        exit(1);
    }
}


//DECLARATIVE STATEMENTS
int pos;
char input[100];

void parse_declaration();
void parse_declarator();
void parse_initializer();

void parse_declaration() {
    if (strncmp(&input[pos], "int", 3) == 0) {
        pos += 3;
        parse_declarator();
        printf("Found int declaration\n");
    } 
    else if (strncmp(&input[pos], "char", 4) == 0) {
        pos += 4;
        parse_declarator();
        printf("Found char declaration\n");
    } 
    else if (strncmp(&input[pos], "float", 5) == 0) {
        pos += 5;
        parse_declarator();
        printf("Found float declaration\n");
    }
    else {
        printf("Invalid declaration\n");
    }
}

void parse_declarator() {
    while (input[pos] != ';') {
        if (input[pos] == '=') {
            pos++;
            parse_initializer();
        }
        pos++;
    }
}

void parse_initializer() {
    while (input[pos] != ';') {
        pos++;
    }
}

int main() {
    // lookahead = getchar();
    // while (lookahead != EOF) {
    //     if (lookahead >= 'a' && lookahead <= 'z') {
    //         assignment();
    //     } else {
    //         printf("Error: unexpected token %c\n", lookahead);
    //         exit(1);
    //     }
    //     lookahead = getchar();
    // }

    // printf("Enter a statement: ");
    // fgets(input, 100, stdin);
    // parse_declaration();

    FILE *file;
    char *filename = "file.txt";
    char word[100];
    char **words;
    int num_words = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (fscanf(file, "%s", word) != EOF) {
        words = realloc(words, (num_words + 1) * sizeof(char *));
        words[num_words] = malloc(strlen(word) + 1);
        strcpy(words[num_words], word);
        num_words++;
    }

    fclose(file);

    //parse_declaration();

    //Print the words in the array
    for (int i = 0; i < num_words; i++) {
        printf("%s\n", words[i]);
    }
        
    return 0;
}