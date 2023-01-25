void match(int expected) {
//     if (strcmp(words[pos], expected) == 0) {
//         pos++;
//     } else {
//         printf("Error: unexpected token %s\n", words[pos]);
//         exit(1);
//     }
// }

// void match2(char* expected, int i) {
//     if (strcmp(words[pos], expected[i]) == 0) {
//         pos++;
//     } else {
//         printf("Error: unexpected token %s\n", words[pos]);
//         exit(1);
//     }
// }

// void assignment() {
//     char* variable = lookahead;
//     match2(words, pos);
//     match('=');
//     expression();
//     match(';');
//     printf("Assigning value to variable %s\n", *variable);
// }

// void expression() {
//     term();
//     while (strcmp(words[pos], '+') == 0 || strcmp(words[pos], '-') == 0) {
//         match2(words, pos);
//         term();
//     }
// }

// void term() {
//     factor();
//     while (strcmp(words[pos], '*') == 0 || strcmp(words[pos], '/') == 0) {
//         match(words, pos);
//         factor();
//     }
// }

// void factor() {
//     match2(words, pos);
//     else if (strcmp(words[pos], '(') == 0) {
//         match('(');
//         expression();
//         match(')');
//     } else {
//         printf("Error: unexpected token %s\n", words[pos]);
//         exit(1);
//     }
// }
