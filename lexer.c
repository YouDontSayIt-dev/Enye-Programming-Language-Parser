 #include <ctype.h>
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <stdbool.h>
 #include "include/lexer.h"

   FILE *outputfptr;
// Checks current lexeme if it is an operator
// returns true if true
bool operatorChecker(char ch){
   if (ch == '+' || ch == '-' || ch == '*' ||
   ch == '/' || ch == '>' || ch == '<' ||
   ch == '!' || ch == '~' || ch == '=' || 
   ch == '%' || ch == '^')
   return (true);
   return (false);
}

void tokenRoleSingleOperator(char ch){
   if(ch == '+'){
   fprintf(outputfptr,"\t\t\tADD_OPR\n");
   nextToken = ADD_OPR;
   }
   else if (ch == '-'){
   fprintf(outputfptr,"\t\t\tSUB_OPR\n");
   nextToken = SUB_OPR;
   }
   else if (ch == '*')
   fprintf(outputfptr,"\t\t\tMULT_OPR\n");
   else if (ch == '/')
   fprintf(outputfptr,"\t\t\tDIV_OPR\n");
   else if (ch == '>')
   fprintf(outputfptr,"\t\t\tGREAT_OPR\n");
   else if (ch == '<')
   fprintf(outputfptr,"\t\t\tLESS_OPR\n");
   else if (ch == '!')
   fprintf(outputfptr,"\t\t\tNOT_OPR\n");
   else if (ch == '~')
   fprintf(outputfptr,"\t\t\tINT_DIV_OPR\n");
   else if (ch == '=')
   fprintf(outputfptr,"\t\t\tASS_OPR\n");
   else if (ch == '%')
   fprintf(outputfptr,"\t\t\tMOD_OPR\n");
   else if (ch == '^')
   fprintf(outputfptr,"\t\t\tEXP_OPR\n");
}

void tokenRoleMultiOperator(char ch, char ch2){
   if (ch == '=' && ch2 == '=')
   fprintf(outputfptr,"\t\t\tEQ_TO_OPR\n");
   else if (ch == '>' && ch2 == '=')
   fprintf(outputfptr,"\t\t\tGRTR_THAN_OR_EQ_TO_OPR\n");
   else if (ch == '<' && ch2 == '=')
   fprintf(outputfptr,"\t\t\tLESS_THAN_OR_EQ_TO_OPR\n");
   else if (ch == '!' && ch2 == '=')
   fprintf(outputfptr,"\t\t\tNOT_EQUAL_TO_OPR\n");
   else if (ch == '+' && ch2 == '+')
   fprintf(outputfptr,"\t\t\tINC_OPR\n");
   else if (ch == '-' && ch2 == '-')
   fprintf(outputfptr,"\t\t\tDEC_OPR\n");
}

bool bracketsChecker(char ch) {
   if (ch == '(' || ch == ')' || ch == '{' || 
   ch == '}' || ch == '[' || ch == ']')
   return (true);
   return (false);
}
// CHANGED
void tokenRoleBracket(char ch){
   if (ch == '('){
   fprintf(outputfptr,"\t\t\tLEFT_PARENTHESIS\n");
   nextToken = LEFT_PARENTHESIS;
   fprintf(outputfptr3,"LEFT_PARENTHESIS\n");
   }
   else if (ch == ')'){
   fprintf(outputfptr,"\t\t\tRIGHT_PARENTHESIS\n");
   nextToken = RIGHT_PARENTHESIS;
   fprintf(outputfptr3,"RIGHT_PARENTHESIS\n");
   }
   else if (ch == '{')
   fprintf(outputfptr,"\t\t\tLEFT_CURLY_BRACES\n");
   else if (ch == '}')
   fprintf(outputfptr,"\t\t\tRIGHT_CURLY_BRACES\n");
   else if (ch == '[')
   fprintf(outputfptr,"\t\t\tLEFT_SQUARE_BRACES\n");
   else if (ch == ']')
   fprintf(outputfptr,"\t\t\tRIGHT_SQUARE_BRACES\n");
}

// CHANGED
bool delimiterChecker(char ch) {
   if (ch == ' ' || ch == ';' || ch == ',' || 
   ch == '"' || ch == '\n' || ch == '\0' ||
   ch == ':' || operatorChecker(ch) || 
   bracketsChecker(ch))
   return (true);
   return (false);
}
// CHANGED
void tokenRoleDelimeterOperator(char ch){
   if(ch == ';'){
   fprintf(outputfptr,"\t\t\tSEMI_COLON\n");
   nextToken = SEMI_COLON;
   fprintf(outputfptr3,"SEMI_COLON\n");
   }
   else if (ch == ','){
   fprintf(outputfptr,"\t\t\tCOMMA\n");
   fprintf(outputfptr3,"COMMA\n");
   }
   else if (ch == ':')
   fprintf(outputfptr,"\t\t\tCOLON\n");
   fprintf(outputfptr3,"\nCOLON\n");
}


// bool ipakitaChecker(char* str){
//    int i, len = strlen(str);
//    for (i = 0; i <=len; i++) {
     
//    }
// }

// CHANGED
bool keywordChecker(char* str){
   int i, len = strlen(str);
   for (i = 0; i <=len; i++) {
      if (str[0] == 'c' && str[1] == 'a' && str[2] == 's' && str[3] == 'e')
         return (true);
      else if (str[0] == 'i' && str[1] == 'p' && str[2] == 'a' && str[3] == 'k' && str[4] == 'i' && str[5] == 't' && str[6] == 'a')
         return (true);
      else if (str[0] == 'l' && str[1] == 'i' && str[2] == 'p' && str[3] == 'o' && str[4] == 'n')
         return (true);
      else if (str[0] == 'p' && str[1] == 'u' && str[2] == 'm' && str[3] == 'u' && str[4] == 'n' && str[5] == 't'&& str[6] == 'a')
         return (true);  
      else if (str[0] == 'i' && str[1] == 'b' && str[2] == 'a' && str[3] == 'l' && str[4] == 'i' && str[5] == 'k')
         return (true); 
      else if (str[0] == 'h' && str[1] == 'a' && str[2] == 'b' && str[3] == 'a' && str[4] == 'n' && str[5] == 'g')
         return (true); 
      else if (str[0] == 'h' && str[1] == 'i' && str[2] == 'n' && str[3] == 't' && str[4] == 'o')
         return (true);
      else if (str[0] == 'g' && str[1] == 'a' && str[2] == 'w' && str[3] == 'i' && str[4] == 'n')
         return (true);
      else if (str[0] == 'l' && str[1] == 'i' && str[2] == 'p' && str[3] == 'a' && str[4] == 't')
         return (true); 
      else if (str[0] == 'i' && str[1] == 's' && str[2] == 'a' && str[3] == 'm' && str[4] == 'a')
         return (true);
      else if (str[0] == 'k' && str[1] == 'a' && str[2] == 'k' && str[3] == 'u' && str[4] == 'l' && str[5] == 'a'&& str[6] == 'n'&& str[7] == 'g'&& str[8] == 'a'&& str[9] == 'n')
         return (true);
      else if (str[0] == 'b' && str[1] == 'u' && str[2] == 'l' && str[3] == 'y' && str[4] == 'a'&& str[5] == 'n')
         return (true);
      else if (str[0] == 'k' && str[1] == 'a' && str[2] == 'w' && str[3] == 'a' && str[4] == 'l' && str[5] == 'a'&& str[6] == 'n')
         return (true);
      else if (str[0] == 'e' && str[1] == 'd' && str[2] == 'i' )
         return (true);
      else if (str[0] == 'b' && str[1] == 'a' && str[2] == 'w' && str[3] == 'a' && str[4] == 't')
         return (true);
      else if (str[0] == 'k' && str[1] == 'a' && str[2] == 'p' && str[3] == 'a' && str[4] == 'g')
         return (true);
      else if (str[0] == 'n' && str[1] == 'u' && str[2] == 'm' && str[3] == 'e' && str[4] == 'r' && str[5] == 'o')
         return (true);
      else if (str[0] == 'p' && str[1] == 'u' && str[2] == 'n' && str[3] == 't' && str[4] == 'o')
         return (true);
      else if (str[0] == 't' && str[1] == 'i' && str[2] == 't' && str[3] == 'i' && str[4] == 'k')
         return (true);
      else if (str[0] == 'b' && str[1] == 'a' && str[2] == 's' && str[3] == 'a' && str[4] == 'h' && str[5] == 'i'&& str[6] == 'n')
         return (true); 
   }
   return (false);
}

// CHANGED
void tokenRoleKeyword(char* str){
   if (str[0] == 'c' && str[1] == 'a' && str[2] == 's' && str[3] == 'e')
         fprintf(outputfptr,"\t\t\tCASE_KW\n");
      else if (str[0] == 'l' && str[1] == 'i' && str[2] == 'p' && str[3] == 'o' && str[4] == 'n')
         fprintf(outputfptr,"\t\t\tSTRING_KW\n");
      else if (str[0] == 'p' && str[1] == 'u' && str[2] == 'm' && str[3] == 'u' && str[4] == 'n' && str[5] == 't'&& str[6] == 'a')
         fprintf(outputfptr,"\t\tGO_KW\n");  
      else if (str[0] == 'i' && str[1] == 'b' && str[2] == 'a' && str[3] == 'l' && str[4] == 'i' && str[5] == 'k')
         fprintf(outputfptr,"\t\tRETURN_KW\n"); 
      else if (str[0] == 'h' && str[1] == 'a' && str[2] == 'b' && str[3] == 'a' && str[4] == 'n' && str[5] == 'g')
         fprintf(outputfptr,"\t\tWHILE_KW\n"); 
      else if (str[0] == 'h' && str[1] == 'i' && str[2] == 'n' && str[3] == 't' && str[4] == 'o')
         fprintf(outputfptr,"\t\t\tBREAK_KW\n");
      else if (str[0] == 'g' && str[1] == 'a' && str[2] == 'w' && str[3] == 'i' && str[4] == 'n')
         fprintf(outputfptr,"\t\t\tDO_KW\n");
      else if (str[0] == 'l' && str[1] == 'i' && str[2] == 'p' && str[3] == 'a' && str[4] == 't')
         fprintf(outputfptr,"\t\t\tSWITCH_KW\n"); 
      else if (str[0] == 'i' && str[1] == 's' && str[2] == 'a' && str[3] == 'm' && str[4] == 'a')
         fprintf(outputfptr,"\t\t\tINCLUDE_KW\n");
      else if (str[0] == 'k' && str[1] == 'a' && str[2] == 'k' && str[3] == 'u' && str[4] == 'l' && str[5] == 'a'&& str[6] == 'n'&& str[7] == 'g'&& str[8] == 'a'&& str[9] == 'n')
         fprintf(outputfptr,"\t\tDEFAULT_KW\n");
      else if (str[0] == 'b' && str[1] == 'u' && str[2] == 'l' && str[3] == 'y' && str[4] == 'a'&& str[5] == 'n')
         fprintf(outputfptr,"\t\tBOOLEAN_KW\n");
      else if (str[0] == 'k' && str[1] == 'a' && str[2] == 'w' && str[3] == 'a' && str[4] == 'l' && str[5] == 'a'&& str[6] == 'n')
         fprintf(outputfptr,"\t\tVOID_KW\n");
      else if (str[0] == 'e' && str[1] == 'd' && str[2] == 'i' )
         fprintf(outputfptr,"\t\t\tELSE_KW\n");
      else if (str[0] == 'b' && str[1] == 'a' && str[2] == 'w' && str[3] == 'a' && str[4] == 't')
         fprintf(outputfptr,"\t\t\tFOR_KW\n");
      else if (str[0] == 'k' && str[1] == 'a' && str[2] == 'p' && str[3] == 'a' && str[4] == 'g')
         fprintf(outputfptr,"\t\t\tIF_KW\n");
      else if (str[0] == 'n' && str[1] == 'u' && str[2] == 'm' && str[3] == 'e' && str[4] == 'r' && str[5] == 'o')
         fprintf(outputfptr,"\t\tINT_KW\n");
      else if (str[0] == 'p' && str[1] == 'u' && str[2] == 'n' && str[3] == 't' && str[4] == 'o')
         fprintf(outputfptr,"\t\t\tFLOAT_KW\n");
      else if (str[0] == 't' && str[1] == 'i' && str[2] == 't' && str[3] == 'i' && str[4] == 'k')
         fprintf(outputfptr,"\t\t\tCHAR_KW\n");
      else if (str[0] == 'i' && str[1] == 'p' && str[2] == 'a' && str[3] == 'k' && str[4] == 'i' && str[5] == 't' && str[6] == 'a')
         fprintf(outputfptr,"\t\tPRINTF_KW\n");
      else if (str[0] == 'b' && str[1] == 'a' && str[2] == 's' && str[3] == 'a' && str[4] == 'h' && str[5] == 'i'&& str[6] == 'n')
         fprintf(outputfptr,"\t\tSCANF_KW\n");
      else{
      fprintf(outputfptr,"\t\tSTRING_LITERAL\n");
      nextToken = STRING_LITERAL;
      }
}


// CHANGED
bool reservedWordChecker (char* str){
   int i, len = strlen(str);
   for (i = 0; i <=len; i++) {
      if (str[0] == 't' && str[1] == 'a' && str[2] == 'm' && str[3] == 'a')
      return (true);
      else if (str[0] == 'm' && str[1] == 'a' && str[2] == 'l' && str[3] == 'i')
      return (true);
      else if (str[0] == 'p' && str[1] == 'r' && str[2] == 'i' && str[3] == 'n' && str[4] == 's' && str[5] == 'i' && str[6] == 'p' && str[7] == 'a' && str[8] == 'l') 
      return (true);
      else if (str[0] == 't' && str[1] == 'u' && str[2] == 'l' && str[3] == 'o' && str[4] == 'y')
      return (true);
      else if (str[0] == 't' && str[1] == 'a' && str[2] == 'n' && str[3] == 'g' && str[4] == 'g' && str[5] == 'a' && str[6] == 'l' && str[7] == 'i' && str[8] == 'n')
      return (true);
   }
   return (false);
}

// CHANGED
void tokenRoleReservedWords(char* str){
   if (str[0] == 't' && str[1] == 'a' && str[2] == 'm' && str[3] == 'a')
      fprintf(outputfptr,"\t\tTRUE_KW\n");
      else if (str[0] == 'm' && str[1] == 'a' && str[2] == 'l' && str[3] == 'i')
      fprintf(outputfptr,"\t\tFALSE_KW\n");
      else if (str[0] == 'p' && str[1] == 'r' && str[2] == 'i' && str[3] == 'n' && str[4] == 's' && str[5] == 'i' && str[6] == 'p' && str[7] == 'a' && str[8] == 'l') 
      fprintf(outputfptr,"\tMAIN_KW\n");
      else if (str[0] == 't' && str[1] == 'u' && str[2] == 'l' && str[3] == 'o' && str[4] == 'y')
      fprintf(outputfptr,"\t\tCONTINUE_KW\n");
      else if (str[0] == 't' && str[1] == 'a' && str[2] == 'n' && str[3] == 'g' && str[4] == 'g' && str[5] == 'a' && str[6] == 'l' && str[7] == 'i' && str[8] == 'n')
      fprintf(outputfptr,"\t\tDELETE_KW\n");
}

bool booleanOperatorChecker (char* str){
   int i, len = strlen(str);
   for (i = 0; i <=len; i++) {
      if (str[0] == '|' && str[1] == '|')
      return (true);
      else if(str[0] == '&' && str[1] == '&')
      return (true);
      else if(str[0] == '!')
      return (true);
   }
   return (false);
}

void tokenRoleBooleanOP(char* str){
   if (str[0] == '&' && str[1] == '&')
   fprintf(outputfptr,"\t\t\tAND_OPR\n");
   else if (str[0] == '|' && str[1] == '|')
   fprintf(outputfptr,"\t\t\tOR_OPR\n");
   else if (str[0] == '!')
   fprintf(outputfptr,"\t\t\tNOT_OPR\n");
}

bool commentChecker(char* str){
int i, len = strlen(str);
   for (i = 0; i <=len; i++) {
      if (str[0] == '|' && str[1] == 'n' && str[2] == 'y')
         return (true);
      else if(str[0] == 'n' && str[1] == 'y' && str[2] == '|')
      return (true);
   }
   return (false);
}

void tokenRoleCommentChecker(char* str){
   if (str[0] == '|' && str[1] == 'n' && str[2] == 'y')
         fprintf(outputfptr,"\t\t\tOPENING_CMNT\n");
      else if(str[0] == 'n' && str[1] == 'y' && str[2] == '|')
         fprintf(outputfptr,"\t\t\tCLOSING_CMNT\n");
}

// Checks if the comment content are all in capital letters
// Returns true if true
bool commentContentChecker(char* str){
   int i, len = strlen(str), flag = 1;
   for (i = 1; i <=len; i++) {
      if (isupper(str[i])){
         flag ++;
      }
   }

   if(flag == len){
       return (true);
   }
  
   return (false);
}

void tokenRoleContentChecker(char* str){
   int i, len = strlen(str);
   for (i = 1; i <=len; i++) {
      if (isupper(str[i])){
      }
   }
   fprintf(outputfptr,"\t\tCMNT_CONTENT\n");
}


// Checks if the current lexeme is "sa"
// returns true if true
bool noiseWordChecker(char* str){
   int i, len = strlen(str);
   for (i = 0; i <=len; i++) {
      if (str[0] == 's' && str[1] == 'a')
      return (true);
   }
   return (false);
}

void tokenRoleNoiseWord(char *str){
   if (str[0] == 's' || str[1] == 'a')
   fprintf(outputfptr,"\t\t\tNOISE_WORD\n");
}

// NEW
// Checks if a character in a lexeme 
// is an invalid character/symbol
bool invalidSymbolsChecker(char* str){ 
   int i, len = strlen(str); 
   for (i = 0; i <=len; i++) {
      if (str[i] == '@' || str[i] == '#' || str[i] == '1' || str[i] == '2' || 
      str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || 
      str[i] == '7' || str[i] == '8' || str[i] == '9' || str[i] == '0' )
      return (true);
   }
   return (false);
}

// Identifiers starts at ny_
// Checks if the current lexeme is an identifier
// if not, return true
bool identifierChecker(char* str){
    int i, len = strlen(str);
         identifierFlag = 0;
         for(i = 0; i <= len; i++){
            if (str[i] == '_'){
               identifierFlag++;
            }
         }
      if (identifierFlag == 1){
          return (true);
      }else{
            return (false);
      }
 
   }

void tokenRoleIdentifier(char* str){
   if (str[0] == 'n' && str[1] == 'y' && str[2] == '_')
   fprintf(outputfptr,"\tIDENTIFIER\n");
   else
   fprintf(outputfptr,"\t\t\tINVALID_IDENTIFIER\n");
}

// Checks if current lexeme is an int
// Returns false if current lexeme is not equal to any number
// Otherwise returns true
bool integerChecker(char* str) {
   int i, len = strlen(str);
   if (len == 0)
   return (false);
   for (i = 0; i < len; i++) {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2'&& str[i] != '3' && str[i] != '4' && str[i] != '5'
      && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
      return (false);
   }
   return (true);
}

void tokenRoleInteger(char* str){
   if (str[0] != '0' || str[1] != '1' || str[2] != '2' || str[3] != '3' || str[4] != '4' || 
   str[5] != '5' || str[6] != '6' || str[7] != '7' || str[8] != '8' || str[9] != '9')
   fprintf(outputfptr,"\t\t\tINTEGER\n");
}

// Checks if current lexeme is a real number
// Always return false
// Check if the lexeme is not a number or contains a negative sign
// If yes, return false
// Check if the lexeme contains a decimal point
// If has a decimal point, return true
bool realNumberChecker(char* str) {
   int i, len = strlen(str), flag = 0;
   bool hasDecimal = false;
   if (len == 0)
   return (false);
   for (i = 0; i < len; i++) {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8'
      && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0)){
          return (false);
      }
     
      // flag should always be 1, if not then it is invalid (eg 2.1.1..)
      if (str[i] == '.'){
         flag ++;
      }
   }
   if (flag == 1){
      hasDecimal = true;
   }
   return (hasDecimal);
}

// Invalid Real Number Checker
// Returns true if the flag detects multi-decimal floating points
// Normal float must always have only 1 in flag value 
// Flag will increment base on repetitive detected floating points
bool InvalidrealNumberChecker(char* str) {
   int i, len = strlen(str), flag = 0;
   bool hasMultipleDecimal = false;
   if (len == 0)
   return (false);
   for (i = 0; i < len; i++) {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8'
      && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0)){
          return (false);
      }
      // flag should always be 1, if not then it is invalid (eg 2.1.1..)
      if (str[i] == '.'){
         flag ++;
      }
   }
   if (flag != 0 && flag != 1){
      hasMultipleDecimal = true;
   }
   return (hasMultipleDecimal);
}

char* subString(char* str, int left, int right) {
   int i;
   char* subStr = (char*)malloc( sizeof(char) * (right - left + 2)); //dynamically allocating memory 
   for (i = left; i <= right; i++)
      subStr[i - left] = str[i];
   subStr[right - left + 1] = '\0';
   return (subStr);
}

//funtion that scans code 
//and takes lexemes as input
//and outputs tokens based on their classification
void lexer(char* str) {
   int left = 0, right = 0;
   int length = strlen(str);
   int flag = 0;
   
   while (right <= length && left <= right) { //while there is another lexeme next to current lexeme
      if (delimiterChecker(str[right]) == false) //checks if str[0] is a delimiter, if not, increment right
      right++;
      if(delimiterChecker(str[right]) == true && left == right) { //checks if the current lexeme is a single character type    
      if (delimiterChecker(str[right]) == true && str[right] == ';' || str[right] == ':' || str[right] == ','){
         fprintf(outputfptr,"\n%c\t",str[right]);
         tokenRoleDelimeterOperator(str[right]);}
      else if (delimiterChecker(str[right]) && bracketsChecker(str[right])){
         fprintf(outputfptr,"\n%c\t",str[right]);
         tokenRoleBracket(str[right]);
      }
      else if(operatorChecker(str[right]) == true && operatorChecker(str[right + 1]) && operatorChecker(str[right+2]) == true){
         fprintf(outputfptr,"\n%c%c%c\t", str[right],str[right+1],str[right+2]);
         fprintf(outputfptr,"\t\t\tINVALID OPERATOR\n");
         right = right+3;
         left = right;
      }
      else if(operatorChecker(str[right]) == true && operatorChecker(str[right + 1]) == true){
         fprintf(outputfptr,"\n%c%c\t", str[right],str[right+1]);
         tokenRoleMultiOperator(str[right],str[right+1]);
         right = right+2;
         left = right;
      }else if (operatorChecker(str[right]) == true)
         //checks if the single character type lexeme is also an operator type one
         fprintf(outputfptr,"\n%c\t", str[right]);
         tokenRoleSingleOperator(str[right]);
         right++;
         left = right;
      }else if (delimiterChecker(str[right]) == true && left != right || (right == length && left != right)){ //checks if the current lexemes is a multicharacter lexeme type
             char* subStr = subString(str, left, right - 1); //takes the current lexeme as input
         if (keywordChecker(subStr) == true){
            fprintf(outputfptr,"\n%s\t", subStr);
            tokenRoleKeyword(subStr);
            // Increment flag
            flag++;
            free (subStr);}
         else if (identifierChecker(subStr) == true){
            int len = strlen(subStr);
            if(len <= 30){
               fprintf(outputfptr,"\n%s\t", subStr);
               tokenRoleIdentifier(subStr);
               // Reset flag counter
               flag = 0;
               free (subStr);}
            else{
               fprintf(outputfptr,"\n%s\t", subStr);
               fprintf(outputfptr,"\tINVALID_LEXEME\n");
               flag = 0;
               free (subStr);
            }
         }
         else if (booleanOperatorChecker(subStr) == true){
            fprintf(outputfptr,"\n%s\t", subStr);   
            tokenRoleBooleanOP(subStr);
            free (subStr);
         }
         else if (reservedWordChecker(subStr) == true){
            fprintf(outputfptr,"\n%s\t", subStr);
            tokenRoleReservedWords(subStr);
            // Increment flag
            flag++;
            free (subStr);}
         else if (integerChecker(subStr) == true){
            fprintf(outputfptr,"\n%s\t", subStr);
            tokenRoleInteger(subStr);
            free (subStr);
            }
         else if (realNumberChecker(subStr) == true){
            fprintf(outputfptr,"\n%s\t\t\tREAL_NUMBER\n", subStr);
            free (subStr);}
         else if (InvalidrealNumberChecker(subStr) == true){
            fprintf(outputfptr,"\n%s\t\t\tINVALID_LEXEME\n", subStr);
            free (subStr);}
         else if (invalidSymbolsChecker(subStr) == true){
            fprintf(outputfptr,"\n%s\t\t\tINVALID_LEXEME\n", subStr);
            free (subStr);}
         else if (commentChecker(subStr) == true){
            fprintf(outputfptr,"\n%s\t", subStr);
            tokenRoleCommentChecker(subStr);
            free (subStr);}
         else if (commentContentChecker(subStr) == true){
            fprintf(outputfptr,"\n%s\t", subStr);
            tokenRoleContentChecker(subStr);
            free (subStr);}
         else if (noiseWordChecker(subStr) == true){
            fprintf(outputfptr,"\n%s\t", subStr);
            tokenRoleNoiseWord(subStr);
            free (subStr);}
         else if(identifierChecker(subStr)== false){
            if(identifierFlag >= 1){
               // A keyword must have succeeding identifier
               // e.g. keyword ny_identifier (+1 -1 = flag: 0)
               // If a keyword (flag: 1) does not reset, it means that the succeeding lexeme 
               // is an invalid keyword, otherwise it is a syntax error
            //   fprintf(outputfptr,"Invalid %s\t", subStr);
               fprintf(outputfptr,"\n%s\t", subStr);
               fprintf(outputfptr,"\tINVALID_IDENTIFIER\n");
               flag = 0;
               free (subStr);
            }
            else{
            //   fprintf(outputfptr,"String : %s", subStr);
               
               fprintf(outputfptr,"\n%s\t", subStr);
               fprintf(outputfptr,"\t\tSTRING_LITERAL\n");
               nextToken = STRING_LITERAL;
               flag = 0;
               free (subStr);
            }
         }
         left = right;
      }
   }
   return;
}

