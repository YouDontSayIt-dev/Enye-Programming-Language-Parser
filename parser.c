#include <stdio.h>
#include <stdlib.h>

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
    lookahead = getchar();
    while (lookahead != EOF) {
        if (lookahead >= 'a' && lookahead <= 'z') {
            assignment();
        } else {
            printf("Error: unexpected token %c\n", lookahead);
            exit(1);
        }
        lookahead = getchar();
    }
    return 0;
}