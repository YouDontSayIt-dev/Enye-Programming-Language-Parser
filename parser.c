#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 100
#define MAX_LENGTH 30

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

int main() {
    char input[MAX_WORDS*MAX_LENGTH];
    char *words[MAX_WORDS];
    char delim[] = " ";
    char* token;
    int i = 0;

    printf("Enter a series of strings: ");
    fgets(input, MAX_WORDS*MAX_LENGTH, stdin);

    // Use strtok to split input into words
    token = strtok(input, delim);
    while (token != NULL) {
        words[i++] = token;
        token = strtok(NULL, delim);
    }
    int numWords = i;

    // Print the words stored in the array
    printf("The words entered were: \n");
    for (int i = 0; i < numWords; i++) {
        printf("%s\n", words[i]);
    }

    return 0;
}
