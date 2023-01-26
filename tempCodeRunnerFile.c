int pos;
// char input[100];

// void parse_declaration();
// void parse_declarator();
// void parse_initializer();

// void parse_declaration() {
//     if (strncmp(&input[pos], "int", 3) == 0) {
//         pos += 3;
//         parse_declarator();
//         printf("Found int declaration\n");
//     } 
//     else if (strncmp(&input[pos], "char", 4) == 0) {
//         pos += 4;
//         parse_declarator();
//         printf("Found char declaration\n");
//     } 
//     else if (strncmp(&input[pos], "float", 5) == 0) {
//         pos += 5;
//         parse_declarator();
//         printf("Found float declaration\n");
//     }
//     else {
//         printf("Invalid declaration\n");
//     }
// }

// void parse_declarator() {
//     while (input[pos] != ';') {
//         if (input[pos] == '=') {
//             pos++;
//             parse_initializer();
//         }
//         pos++;
//     }
// }

// void parse_initializer() {
//     while (input[pos] != ';') {
//         pos++;
//     }
// }