#ifndef LEXER_H
#define LEXER_H

bool keywordChecker(char* str);
bool reservedWordChecker(char* str);
bool booleanOperatorChecker(char* str);
bool delimiterChecker(char ch);
bool operatorChecker(char ch);
bool commentContentChecker(char* str);
bool commentChecker(char* str);
bool noiseWordChecker(char* str);
bool identifierChecker(char* str);
bool integerChecker(char* str);
bool realNumberChecker(char* str);
char* subString(char* str, int left, int right);
void lexer(char* str);
bool bracketsChecker(char ch);


// TOKEN FUNCTIONS
void tokenRoleSingleOperator(char ch);
void tokenRoleBooleanOP(char* str);
void tokenRoleBracket(char ch);
void tokenRoleNoiseWord(char *str);
void tokenRoleIdentifier(char* str);
void tokenRoleInteger(char* str);
void tokenRoleDelimeterOperator(char ch);
void tokenRoleKeyword(char* str);
void tokenRoleReservedWords(char* str);
void tokenRoleCommentChecker(char* str);
void tokenRoleContentChecker(char* str);





/* TOKEN CODES */

#define ADD_OPR 10
#define SUB_OPR 11
#define MULT_OPR 12
#define DIV_OPR 13
#define MOD_OPR 14
#define EXP_OPR 15
#define ASS_OPR 16
#define GREAT_OPR 17
#define LESS_OPR 18
#define INT_DIV_OPR 20
#define EQ_TO_OPR 21
#define GRTR_THAN_OR_EQ_TO_OPR 22
#define LESS_THAN_OR_EQ_TO_OPR 23
#define NOT_EQUAL_TO_OPR 24


#define LEFT_PARENTHESIS 30
#define RIGHT_PARENTHESIS 31
#define LEFT_CURLY_BRACES 32
#define RIGHT_CURLY_BRACES 33
#define LEFT_SQUARE_BRACES 34
#define RIGHT_SQUARE_BRACES 35

#define SEMI_COLON 40
#define COMMA 41
#define COLON 42

#define CASE_KW 50
#define STRING_KW 51
#define GO_KW 52
#define RETURN_KW 53
#define WHILE_KW 54
#define BREAK_KW 55
#define DO_KW 56
#define SWITCH_KW 57
#define INCLUDE_KW 58
#define DEFAULT_KW 59
#define BOOLEAN_KW 60
#define VOID_KW 61
#define ELSE_KW 62
#define FOR_KW 63
#define IF_KW 64
#define INT_KW 65
#define FLOAT_KW 66
#define CHAR_KW 67
#define PRINT_KW 68
#define SCAN_KW 69

#define TRUE_KW 80
#define FALSE_KW 81
#define MAIN_KW 82
#define CONTINUE_KW 83
#define DELETE_KW 84

#define AND_OPR 90
#define OR_OPR 91
#define NOT_OPR 92

#define OPENING_CMNT 100
#define CLOSING_CMNT 101
#define CMNT_CONTENT 102

#define NOISE_WORD 110

#define IDENTIFIER 120
#define INVALID_IDENTIFIER 121

#define INTEGER 130
//#define INVALID_INTEGER 131

#define REAL_NUMBER 140
//#define INVALID_REAL_NUMBER 141

#define STRING_LITERAL 150

int nextToken;
#endif