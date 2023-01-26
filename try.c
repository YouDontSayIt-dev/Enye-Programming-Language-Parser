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
int lineNo = 0;
int lineNoMax = 0;
int errorFlag = 0;
int stmtFlag = 0;


char lexerContent;
char lexerData[2000];

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
void power();

void cond();
void rel_opr();
void unary_opr();
void variable();
void constants();

void parseToken();
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
            
              // variable to store contents of input file
                for(int i=0; i<sizeof(lexerData); i++) {
                    lexerContent = fgetc(inputfptr); // reads input file
                    if(lexerContent == EOF) {
                        break;
                        }
                            lexerData[i] = lexerContent;                
                    }
      
       fclose(inputfptr);    
       //run lexical analysis
       lexer(lexerData);
       fclose(outputfptr);
       //open file for parsing
       file = fopen(symbol_filepath, "r");
       //run parser
       parser();
       printf("%d",errorFlag);
        fclose(file);
      
    


    return 0;
}
}


//recursive function to parse declarative statements
//will receive a token from the lexer
//then parse it base on the grammar
void parse_declaration() {
    data_type(); //parse data type
    parseToken(); //get next token
    assignment(); //parse assignment statement
    //parse_declarator();
}

//parses data type
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
        printf("Invalid declaration at line: %d\n", stmtFlag);
        errorFlag = 1;
    }
}

//ASSIGNMENT STATEMENTS

//a function that checks if the current token is the expected token
//if not, it will print an error message
//if it is an invalide, it will print an error message
void match(char* expected) {
    if (strcmp("INVALID_IDENTIFIER", expected) == 0) {
        printf("Error: unexpected token %s at line: %d\n", currentToken, lineNo);
        errorFlag = 1;
    }
    else if (strcmp(currentToken, expected) != 0) {
        printf("Error: unexpected token %s at line: %d\n", currentToken, lineNo);
        errorFlag = 1;
    }
}

//a recursive function that parses assignment statements
//will receive a token from the lexer
//then parse it base on the grammar
//it will match the given token to the expected token using the match function
void assignment() {
    match(currentToken);
    //if the current token is the expected token, it will get the next token
    //this should get the identifier
    parseToken();
    //if the token is a semicolon, it will match the token to the expected token
    //and will print a success message if the token is the expected token which is a semi-colon
    if(strcmp(currentToken, "SEMI_COLON") == 0){
        match("SEMI_COLON");                
        if(errorFlag == 0){
            printf("Parsing assignment statement success\n");
        }else{
            printf("Parsing assignment statement failed\n");
        }
    }else if(strcmp(currentToken, "ASS_OPR") == 0){
        //if the token is not a semi-colon, it will match the token to the expected token
        //the expected token is an assignment operator
        match("ASS_OPR");
        //if the token is the expected token, it will get the next token
        parseToken();
        //if the token is a semi-colon, it will call the recursive function expression()
        expression();
        //once the expression is parsed, it will match the token to the expected token
        //the expected token is a semi-colon
        //if the token is the expected token, it will print a success message
        //if not, it will print an error message
        match("SEMI_COLON");
        if(errorFlag == 0){
            printf("Parsing assignment statement success\n");
        }else{
            printf("Parsing assignment statement failed\n");
    }
    }
}

//a recursive function that parses expressions
void expression() {
    //will first call the recursive function term()
    term();
    //if term is parsed, it will check if the current token is an add or subtract operator or a comma
    //if it is, it will match the token to the expected token
    //and will call the recursive function term()
    while (strcmp(currentToken, "ADD_OPR") == 0 || strcmp(currentToken, "SUBT_OPR") == 0 || strcmp(currentToken, "COMMA") == 0) {
        match(currentToken);
        parseToken();
        term();
    }
}

//a recursive function that parses terms
void term() {
    //will first call the recursive function power()
    power();
    //if power is parsed, it will check if the current token is a multiply, divide, modulus or integer divide operator
    //if it is, it will match the token to the expected token
    //and will call the recursive function power()
    while (strcmp(currentToken, "MULT_OPR") == 0 || strcmp(currentToken, "DIV_OPR") == 0 || 
    strcmp(currentToken, "MOD_OPR") == 0 || strcmp(currentToken, "INT_DIV_OPR") == 0) {
        match(currentToken);
        parseToken();
        power();
    }
}

//a recursive function that parses powers
void power(){
    //will first call the recursive function factor()
    factor();
    //if factor is parsed, it will check if the current token is an exponent operator
    //if it is, it will match the token to the expected token
    //and will call the recursive function factor()
    while (strcmp(currentToken, "EXP_OPR") == 0) {
        match(currentToken);
        parseToken();
        factor();
    }
}

//a recursive function that parses factors
void factor() {
    //if the current token is an real number,identifier, or string literal- it will match the token to the expected token
    //and will get the next token
    //if the token is an string, it will loop while the token is still a string
    //if the token is an invalid identifier, it will print an error message
    //if the token is not any of the expected tokens, it will print an error message
    if (strcmp(currentToken, "REAL_NUMBER") == 0 || strcmp(currentToken, "INTEGER") == 0) {
        match(currentToken);
        parseToken();
    } else if (strcmp(currentToken, "IDENTIFIER") == 0) {
        match(currentToken);
        parseToken();
    }else if (strcmp(currentToken, "INVALID_IDENTIFIER") == 0) {
        printf("Error: unexpected token %s at line no: %d\n", currentToken, lineNo);
        errorFlag = 1;
    }else if (strcmp(currentToken, "STRING_LITERAL") == 0){
        match(currentToken);
        parseToken();
        while(strcmp(currentToken, "STRING_LITERAL") == 0){
            match(currentToken);
            parseToken();
        }
    }else if (strcmp(currentToken, "LEFT_PARENTHESIS") == 0) {
        //if the token is a left parenthesis, it will match the token to the expected token
        //and will call the recursive function expression()
        //and will match the right parenthesis to the expected token
        //and will get the next token
        match("LEFT_PARENTHESIS");
        parseToken();
        expression();
        match("RIGHT_PARENTHESIS");
        parseToken();
    }else {
        printf("Error: unexpected token %s at line %d\n", currentToken, stmtFlag);
        errorFlag = 1;
    }
}


//OUTPUT STATEMENT

//this function parses output statements
void output_statement() {
    //if the token is a print keyword, it will match the token to the expected token
    match("PRINTF_KW");
    //and will get the next token
    parseToken();
    //if the token is a left parenthesis, it will match the token to the expected token
    match("LEFT_PARENTHESIS");
    //and will get the next token
    parseToken();
    //it will call the recursive function expression()
    expression();
    //if the token is a right parenthesis, it will match the token to the expected token
    match("RIGHT_PARENTHESIS");
    //and will get the next token
    parseToken();
    //if the token is a semi-colon, it will match the token to the expected token
    match("SEMI_COLON");
    //if the error flag is 0, it will print a success message
    if(errorFlag == 0){
        printf("Parsing output statement success\n");
    }else{
        printf("Parsing output statement failed");
    }
}

//INPUT STATEMENT

//this function parses input statements
void input_statement() {
    //if the token is a scan keyword, it will match the token to the expected token
    match("SCANF_KW");
    //and will get the next token
    parseToken();
    //if the token is a left parenthesis, it will match the token to the expected token
    match("LEFT_PARENTHESIS");
    //and will get the next token
    parseToken();
    //it will then call the recursive function expression()
    expression();
    //if the token is a right parenthesis, it will match the token to the expected token
    match("RIGHT_PARENTHESIS");
    //and will get the next token
    parseToken();
    //if the token is a semi-colon, it will match the token to the expected token
    match("SEMI_COLON");
    //if the error flag is 0, it will print a success message
    if(errorFlag == 0){
        printf("Parsing input statement success\n");
    }else{
        printf("Parsing input statement failed");
    }
}


// ITERATIVE STATEMENT

//this function parses iterative statements
void iterative_statement(){ 
    //if the token is a for keyword, it will match the token to the expected token
    match("FOR_KW");
    //and will get the next token
    parseToken();
    //if the token is a left parenthesis, it will match the token to the expected token
    match("LEFT_PARENTHESIS");
    //and will get the next token
    parseToken();
    //it will then call the recursive function assignment()
    assignment();
    //and will get the next token
    parseToken();
    //it will then call the function cond()
    cond();
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("SEMI_COLON");
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("IDENTIFIER");
    //and will get the next token
    parseToken();
    //it will then call the function unary_opr()
    unary_opr();
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("RIGHT_PARENTHESIS");
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("LEFT_CURLY_BRACES");
    //and will get the next token
    parseToken();
    //it will then call the function stmt()
    stmt();
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("RIGHT_CURLY_BRACES");
    //if the error flag is 0, it will print a success message
    if(errorFlag == 0){
        printf("Parsing iterative statement success\n");
    }else{
        printf("Parsing iterative statement failed");
    }
}

//a function that matches the current token to the expected token
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

//a function that matches the current token to the expected token
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

//a function that parses conditional statements
void cond(){
    //it will call the function variable()
    //and will get the next token
    //it will then call the function rel_opr()
    //and will get the next token
    //it will then call the function variable()
        variable();
        parseToken();
        rel_opr();
        parseToken();
        variable();
}

//a function that matches the current token to the expected token
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

//a function that matches the current token to the expected token
//if the token is not matched as an identifier, then it is a constant
void variable(){
    if (strcmp(currentToken, "IDENTIFIER") == 0){
        match(currentToken);
    }
    else{
        constants();
        }
}

//a function that matches the current token to the expected token
//if a token is not matched as an increment operator, then it is a decrement operator
void unary_opr(){
    if (strcmp(currentToken, "INC_OPR") == 0 ){
        match(currentToken);
    } 
    else if (strcmp(currentToken, "DEC_OPR") == 0){
        match(currentToken);
    }
}

//a recursive function that parses else statements
void else_stmt(){
    //if the token is an else keyword, it will match the token to the expected token
    match("ELSE_KW");
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("LEFT_CURLY_BRACES");
    //and will get the next token
    parseToken();
    //it will then call the function stmt()
    stmt();
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("RIGHT_CURLY_BRACES");
    //if the error flag is 0, it will print a success message
    if(errorFlag == 0){
        printf("Parsing else statement success\n");
    }else{
        printf("Parsing else statement failed");
    }
}

//a recursive function that parses else if statements
void else_if_stmt(){
    //if the token is an else keyword, it will match the token to the expected token
    match("ELSE_KW");
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("IF_KW");
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("LEFT_PARENTHESIS");
    //and will get the next token
    parseToken();
    //it will then call the function cond()
    cond();
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("RIGHT_PARENTHESIS");
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("LEFT_CURLY_BRACES");
    //and will get the next token
    parseToken();
    //it will then call the function stmt()
    stmt();
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("RIGHT_CURLY_BRACES");
    //if the error flag is 0, it will print a success message
    if(errorFlag == 0){
        printf("Parsing else if statement success\n");
    }else{
        printf("Parsing else if statement failed");
    }
}

// Conditional Statements

//a function that parses conditional statements
void conditional_stmt(){
    //if the token is an if keyword, it will match the token to the expected token
    match("IF_KW");
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("LEFT_PARENTHESIS");
    //and will get the next token
    parseToken();
    //it will then call the function cond()
    cond();
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("RIGHT_PARENTHESIS");
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("LEFT_CURLY_BRACES");
    //and will get the next token
    parseToken();
    //it will then call the function stmt()
    stmt();
    //and will get the next token
    parseToken();
    //it will then match the token to the expected token
    match("RIGHT_CURLY_BRACES");
    //if the error flag is 0, it will print a success message
    if(errorFlag == 0){
        printf("Parsing conditional statement success\n");
    }else{
        printf("Parsing conditional statement failed");
    }
}

// START OF GRAMMAR RULE
//start of the parser
void parser(){
    //do the following while the statement flag is greater than or equal to the line number
    do{
         parseToken();
         stmts();
         lineNoMax++;
         stmtFlag++;
    }while(stmtFlag >= lineNoMax);

    if(errorFlag == 0){
        printf("Parsing success\n");
}
}

void stmts(){
    //error flag that increments if there is an error
    errorFlag=0;
    //call the function stmt()
    stmt();
    
}


//a function that parses statements
//it will call the appropriate function depending on the token
//if the token is not matched, it will print an error message
void stmt(){
      if(strcmp(currentToken, "INT_KW") == 0 || strcmp(currentToken, "FLOAT_KW") == 0 
      || strcmp(currentToken, "CHAR_KW") == 0 || strcmp(currentToken, "STRING_KW") == 0){
        parse_declaration();}
        else if(strcmp(currentToken, "IDENTIFIER") == 0){
            assignment();  
        }
        else if(strcmp(currentToken, "PRINTF_KW") == 0){
            output_statement();
        }
        else if(strcmp(currentToken, "SCANF_KW") == 0){
            input_statement();
        }
        else if(strcmp(currentToken, "FOR_KW") == 0){
            iterative_statement();
        }
        else if(strcmp(currentToken, "IF_KW") == 0){
            conditional_stmt();
        }
        else if(strcmp(currentToken, "ELSE_KW") == 0){
            else_stmt();
        }
        else if(strcmp(currentToken, "ELSE_KW") == 0){
            parseToken();
            if(strcmp(currentToken, "IF_KW") == 0){
                else_if_stmt();
            }
        }
        else{
            printf("Error in line %d: Invalid statement", stmtFlag);
        }
}

//a function that gets the next token
void parseToken(){
    char ch = fgetc(file);
    int index = 0;

    //if ch is a \n, it will increment the line number
    //while ch is a \n, it will get the next character
    if(ch == '\n'){
        lineNo++;
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