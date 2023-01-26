#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "include/lexer.h"
#include "include/main.h"
#include "lexer.c"

char word[100];
char **words = NULL;
int num_words = 0;
int strIndex = 0;
char currentLexeme[100];
char currentToken[20];
int lineNo = 1;
int lineNoMax = 1;
int errorFlag = 0;

FILE *file;
char *filename = "example/SymbolTable.txt";
char in_filepath[100],out_filepath[100] = "example/SymbolTable.txt",
parser_filepath[100] = "example/ParsingInput.txt",symbol_filepath[100] = "example/SymbolTable.txt"; // file path variable
  int len;


//DECLARATIVE STATEMENTS
int pos;
int expected;

void parse_declaration();
void parse_declarator();
void parse_initializer();
void data_type();
void assignment();
void expression();
void term();
void factor();

void cond();
void rel_opr();
void unary_opr();
void variable();
void constants();

void getToken();
void parser();
void stmts();
void stmt();


int main() {
        /* FOR LEXER */
      printf("Input file path: ");
      scanf("%s",in_filepath);
      len = strlen(in_filepath);
      if (len <= 2) { // Checks if file path is invalid
        printf("Invalid file path");
        return 0;
      }
      // Checks if file extension is invalid
      if(in_filepath[len-1] == 'y' && in_filepath[len-2] == 'n' && in_filepath[len-3] == '.'){
            /* FOR LEXER */
            inputfptr = fopen(in_filepath, "r");
            outputfptr = fopen(out_filepath, "w");
            
            char lexerContent;
            char lexerData[1000];  // variable to store contents of input file
                for(int i=0; i<sizeof(lexerData); i++) {
                    lexerContent = fgetc(inputfptr); // reads input file
                    if(lexerContent == EOF) {
                        break;
                        }
                            lexerData[i] = lexerContent;                
                    }
      
      
       fclose(inputfptr);    
       lexer(lexerData);
       fclose(outputfptr);
       file = fopen(symbol_filepath, "r");
       getToken();
       parser();
       printf("%d",lineNo);
        fclose(file);
      
    


    return 0;
}
}

void parse_declaration() {
    data_type();
    getToken();
    assignment();
    //parse_declarator();
}

void data_type(){
    if (strcmp(currentToken, "INT_KW") == 0){
        printf("Found int declaration\n");
    } 
    else if (strcmp(currentToken, "CHAR_KW") == 0) {
        printf("Found char declaration\n");
    } 
    else if (strcmp(currentToken, "FLOAT_KW") == 0) {
        printf("Found float declaration\n");
    }
    else if (strcmp(currentToken, "STRING_KW") == 0) {
        printf("Found string declaration\n");
    }
    else {
        printf("Invalid declaration\n");
        errorFlag = 1;
    }
}




// void parse_declarator() {
//     while (strcmp(currentToken, "SEMI_COLON") == 1) {
//         if (strcmp(currentToken, "ASS_OPR") == 0) {
//             // pos+=7;
//             pos++;
//             parse_initializer();
//         }
//         // pos+= 10;
//         pos++;
//     }
// }

// void parse_initializer() {
//     while (strcmp(currentToken, "SEMI_COLON") == 1) {
//         // pos+= 10;
//         pos++;
//     }
// }


//ASSIGNMENT STATEMENTS
void match(char* expected) {
    if (strcmp(currentToken, expected) != 0) {
        printf("Error: unexpected token %s\n", currentToken);
        errorFlag = 1;
    } else {
        

    }
}

// void match2(char** expected, int i) {
//     if (strcmp(currentToken, expected[i]) == 0) {
//         getToken();
//     } else {
//         printf("Error: unexpected token %s\n", currentToken);
//         errorFlag = 1;
//     }
// }

void assignment() {
    match(currentToken);
    getToken();
    if(strcmp(currentToken, "SEMI_COLON") == 0){
        match("SEMI_COLON");                
        printf("Found assignment statement");
    }else if(strcmp(currentToken, "ASS_OPR") == 0){
        
        match("ASS_OPR");
        getToken();
        expression();
        getToken();
        match("SEMI_COLON");
        printf("Found assignment statement");
    }
    }


void expression() {
    term();
    while (strcmp(currentToken, "ADD_OPR") == 0 || strcmp(currentToken, "SUBT_OPR") == 0) {
        match(currentToken);
        term();
    }
}

void term() {
    factor();
    while (strcmp(currentToken, "MULT_OPR") == 0 || strcmp(currentToken, "DIV_OPR") == 0) {
        match(currentToken);
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
        errorFlag = 1;;
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
    match("LEFT_CURLY_BRACES");
    stmt();
    match("RIGHT_CURLY_BRACES");
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
        match("LEFT_CURLY_BRACES");
        stmt();
        match("RIGHT_CURLY_BRACES");
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
    match("LEFT_CURLY_BRACES");
    stmt();
    match("RIGHT_CURLY_BRACES");
    printf("Found if statement");
}
// START OF GRAMMAR RULE
void parser(){
    
         stmts();
    
   
}

void stmts(){
    stmt();
}

void stmt(){
    
      parse_declaration();
    //  assignment();
    // output_statement();
    //  input_statement();
    //  iterative_statement();
    //  conditional_stmt();
}

void getToken(){
    char ch = fgetc(file);
    int index = 0;

    if(ch == '\n'){
        
        printf("Line %d\n", lineNo);
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
        currentToken[index] = ch;
        index++;
        ch = fgetc(file);
    }
    currentToken[index] = '\0';
      //  printf("Lexeme: %s\t",currentLexeme);
        printf("Token: %s\n",currentToken);
}