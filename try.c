#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char word[100];
char **words = NULL;
int num_words = 0;
int strIndex = 0;
char currentLexeme[100];
char currentToken[20];
int lineNo = 1;

FILE *file;
char *filename = "SymbolTable.txt";


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

void getToken();
void parser();
void stmts();
void stmt();

void parse_declaration() {
    getToken();
    if (strncmp(currentToken, "INT_KW", 6) == 0) {
        // pos += 6;
        pos++;
        parse_declarator();
        printf("Found int declaration\n");
    } 
    else if (strncmp(currentToken, "CHAR_KW", 7) == 0) {
        // pos += 7;
        pos++;
        parse_declarator();
        printf("Found char declaration\n");
    } 
    else if (strncmp(currentToken, "FLOAT_KW", 8) == 0) {
        // pos += 8;
        pos++;
        parse_declarator();
        printf("Found float declaration\n");
    }
    else if (strncmp(currentToken, "STRING_KW", 9) == 0) {
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
    while (strcmp(currentToken, "SEMI_COLON") == 1) {
        if (strcmp(currentToken, "ASS_OPR") == 0) {
            // pos+=7;
            pos++;
            parse_initializer();
        }
        // pos+= 10;
        pos++;
    }
}

void parse_initializer() {
    while (strcmp(currentToken, "SEMI_COLON") == 1) {
        // pos+= 10;
        pos++;
    }
}


//ASSIGNMENT STATEMENTS
void match(char* expected) {
    if (strcmp(currentToken, expected) == 0) {
        pos++;
        getToken();
    } else {
        printf("Error: unexpected token %s\n", currentToken);
        exit(1);
    }
}

void match2(char** expected, int i) {
    if (strcmp(currentToken, expected[i]) == 0) {
        getToken();
        pos++;
    } else {
        printf("Error: unexpected token %s\n", currentToken);
        exit(1);
    }
}

void assignment() {
    getToken();
    char* variable = currentToken;
    match2(words, pos);
    if(strcmp(currentToken, "SEMI_COLON") == 0){
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
    while (strcmp(currentToken, "ADD_OPR") == 0 || strcmp(currentToken, "SUBT_OPR") == 0) {
        match2(words, pos);
        term();
    }
}

void term() {
    factor();
    while (strcmp(currentToken, "MULT_OPR") == 0 || strcmp(currentToken, "DIV_OPR") == 0) {
        match2(words, pos);
        factor();
    }
}

void factor() {
    if (strcmp(currentToken, "REAL_NUMBER") == 0 || strcmp(currentToken, "INTEGER") == 0) {
        match(currentToken);
    } else if (strcmp(currentToken, "IDENTIFIER") == 0) {
        match(currentToken);
    }else if (strcmp(currentToken, "STRING_LITERAL") == 0){
        match(currentToken);
    }else if (strcmp(currentToken, "LEFT_PARENTHESIS") == 0) {
        match("LEFT_PARENTHESIS");
        expression();
        match("RIGHT_PARENTHESIS");
    }else {
        printf("Error: unexpected token %s\n", currentToken);
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
    getToken();
    match("PRINTF_KW");
    match("LEFT_PARENTHESIS");
    expression();
    match("RIGHT_PARENTHESIS");
   // match("SEMI_COLON");
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
    if (strcmp(currentToken, "GREAT_OPR") == 0 ){
        match(currentToken);
    } 
    else if (strcmp(currentToken, "LESS_OPR") == 0){
        match(currentToken);
    }
    else if (strcmp(currentToken, "NOT_OPR") == 0){ 
        match(currentToken);
    }
    else if (strcmp(currentToken, "EQ_TO_OPR") == 0){ 
        match(currentToken);
    }
    else if (strcmp(currentToken, "NOT_EQUAL_TO_OPR") == 0){ 
        match(currentToken);
    }
    else if (strcmp(currentToken, "GRTR_THAN_OR_EQ_TO_OPR") == 0){ 
        match(currentToken);
    }
    else if (strcmp(currentToken, "LESS_THAN_OR_EQ_TO_OPR") == 0){ 
        match(currentToken);
    }
}

void log_opr(){
    if (strcmp(currentToken, "AND_OPR") == 0 ){
        match(currentToken);
    } 
    else if (strcmp(currentToken, "OR_OPR") == 0){
        match(currentToken);
    }
    else if (strcmp(currentToken, "NOT_OPR") == 0){ 
        match(currentToken);
    }
}

void cond(){
        variable();
        rel_opr();
        variable();
    }

void constants(){
    if (strcmp(currentToken, "INTEGER") == 0){
        match(currentToken);
    }
    else if (strcmp(currentToken, "REAL_NUMBER") == 0){
        match(currentToken);
    }
    else if (strcmp(currentToken, "STRING_LITERAL") == 0){
        match(currentToken);
    }
}

void variable(){
    if (strcmp(currentToken, "IDENTIFIER") == 0){
        match(currentToken);
    }
    else{
        constants();
        }
}

void unary_opr(){
    if (strcmp(currentToken, "INC_OPR") == 0 ){
        match(currentToken);
    } 
    else if (strcmp(currentToken, "DEC_OPR") == 0){
        match(currentToken);
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

void parser(){

    stmts();
}

void stmts(){
    stmt();
}

void stmt(){
    
    //  parse_declaration();
    //  assignment();
     output_statement();
    //  input_statement();
    //  iterative_statement();
    //  conditional_stmt();
}
int main() {
    
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }else{
       parser();
    }

    // while (fscanf(file, "%s", word) != EOF) {
    //     words = (char **) realloc(words, (num_words + 1) * sizeof(char *));
    //     words[num_words] = (char *) malloc((strlen(word) + 1) * sizeof(char));
    //     strcpy(words[num_words], word);
    //     num_words++;
    //     printf("%s",word);
    // }

    fclose(file);
    // parse_declaration();
    // assignment();
    // output_statement();
    //input_statement();
    //iterative_statement();
    //conditional_stmt();
    // if(currentToken == "int"){
    //     printf("int");
    // }else
    //     printf("not int");
    // printf("%s", currentToken);
    // printf("%c", word[pos]);

    // char* variable = currentToken;
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


void getToken(){
    char ch = fgetc(file);
    int index = 0;

    if(ch == '\n'){
        lineNo++;
        //printf("Line %d\n", lineNo);
        ch = fgetc(file);
        while(ch=='\n'){
            ch = fgetc(file);
        }
    }
    // gets the lexeme
    while(ch != '\t'){
        currentLexeme[index] = ch;
        index++;
        ch = fgetc(file);
    }
    currentLexeme[index] = '\0';

    // skips all \t
    while(ch == '\t'){
        ch = fgetc(file);
    }

    // gets the token
    index = 0;
    while(ch != '\n'){
        if(ch != EOF){
        currentToken[index] = ch;
        index++;
        ch = fgetc(file);
        }
        else{
            break;
        }
    }
    currentToken[index] = '\0';
        //printf("Lexeme: %s\t",currentLexeme);
        printf("Token: %s\n",currentToken);
}