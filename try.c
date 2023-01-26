#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char word[100];
char **words = NULL;
int num_words = 0;

//DECLARATIVE STATEMENTS
int pos;
int expected;

void parse_declaration();
void parse_declarator();
void parse_initializer();
void assignment();
void expression();
void term();
void factor();

void cond();
void rel_opr();
void unary_opr();
void variable();
void constant();

void parse_declaration() {
    if (strncmp(words[pos], "INT_KW", 6) == 0) {
        // pos += 6;
        pos++;
        parse_declarator();
        printf("Found int declaration\n");
    } 
    else if (strncmp(words[pos], "CHAR_KW", 7) == 0) {
        // pos += 7;
        pos++;
        parse_declarator();
        printf("Found char declaration\n");
    } 
    else if (strncmp(words[pos], "FLOAT_KW", 8) == 0) {
        // pos += 8;
        pos++;
        parse_declarator();
        printf("Found float declaration\n");
    }
    else if (strncmp(words[pos], "STRING_KW", 9) == 0) {
        // pos += 9;
        pos++;
        parse_declarator();
        printf("Found string declaration\n");
    }
    else {
        printf("Invalid declaration\n");
    }
}

void parse_declarator() {
    while (strcmp(words[pos], "SEMI_COLON") == 1) {
        if (strcmp(words[pos], "ASS_OPR") == 0) {
            // pos+=7;
            pos++;
            parse_initializer();
        }
        // pos+= 10;
        pos++;
    }
}

void parse_initializer() {
    while (strcmp(words[pos], "SEMI_COLON") == 1) {
        // pos+= 10;
        pos++;
    }
}


//ASSIGNMENT STATEMENTS
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

void assignment() {
    char* variable = words[pos];
    match2(words, pos);
    if(strcmp(words[pos], "SEMI_COLON") == 0){
        match("SEMI_COLON");                
        printf("Assigning value to variable %s\n", variable);
    }else{
        match("ASS_OPR");
        expression();
        match("SEMI_COLON");
        printf("Assigning value to variable %s\n", variable);
    }
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

// void print(char** expected, int i) {
//     printf("%s", expected[i]);
// }

// void print(char* expected){
//     if(strcmp(expected, "STRING_KW") == 0){
//         printf("YEHEY");
//     }
// }

//OUTPUT STATEMENT
void output_statement() {
    match("PRINTF_KW");
    expression();
    match("SEMI_COLON");
    printf("Found output statement");
}

//INPUT STATEMENT
void input_statement() {
    match("SCANF_KW");
    expression();
    match("SEMI_COLON");
    printf("Found input statement");
}


// ITERATIVE STATEMENT
void iterative_statement(){
    match("FOR_KW");
    assignment();
    cond();
    match("SEMI_COLON");
    unary_opr();
    printf("Found for loop");
}


void rel_opr(){
    if (strcmp(words[pos], "GREAT_OPR") == 0 ){
        match(words[pos]);
    } 
    else if (strcmp(words[pos], "LESS_OPR") == 0){
        match(words[pos]);
    }
    else if (strcmp(words[pos], "NOT_OPR") == 0){ 
        match(words[pos]);
    }
    else if (strcmp(words[pos], "EQ_TO_OPR") == 0){ 
        match(words[pos]);
    }
    else if (strcmp(words[pos], "NOT_EQUAL_TO_OPR") == 0){ 
        match(words[pos]);
    }
    else if (strcmp(words[pos], "GRTR_THAN_OR_EQ_TO_OPR") == 0){ 
        match(words[pos]);
    }
    else if (strcmp(words[pos], "LESS_THAN_OR_EQ_TO_OPR") == 0){ 
        match(words[pos]);
    }
}

void log_opr(){
    if (strcmp(words[pos], "AND_OPR") == 0 ){
        match(words[pos]);
    } 
    else if (strcmp(words[pos], "OR_OPR") == 0){
        match(words[pos]);
    }
    else if (strcmp(words[pos], "NOT_OPR") == 0){ 
        match(words[pos]);
    }
}

void cond(){
        variable();
        rel_opr();
        variable();
    }

void constants(){
    if (strcmp(words[pos], "INTEGER") == 0){
        match(words[pos]);
    }
    else if (strcmp(words[pos], "REAL_NUMBER") == 0){
        match(words[pos]);
    }
    else if (strcmp(words[pos], "STRING_LITERAL") == 0){
        match(words[pos]);
    }
}

void variable(){
    if (strcmp(words[pos], "IDENTIFIER") == 0){
        match(words[pos]);
    }
    else{
        constants();
        }
}

void unary_opr(){
    if (strcmp(words[pos], "INC_OPR") == 0 ){
        match(words[pos]);
    } 
    else if (strcmp(words[pos], "DEC_OPR") == 0){
        match(words[pos]);
    }
}

// Conditional Statements
void conditional_stmt(){
    match("IF_KW");
    cond();
    expression();
    match("SEMI_COLON");
    printf("Found if statement");
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
    // parse_declaration();
    // assignment();
    // output_statement();
    //input_statement();
    //iterative_statement();
    conditional_stmt();
    // if(words[pos] == "int"){
    //     printf("int");
    // }else
    //     printf("not int");
    // printf("%s", words[pos]);
    // printf("%c", word[pos]);

    // char* variable = words[pos];
    // printf("%s", variable);
    // print("STRING_KW");

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
