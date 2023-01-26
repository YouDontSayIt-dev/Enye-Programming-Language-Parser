parseToken();
    match("RIGHT_PARENTHESIS");
    parseToken();
    match("LEFT_CURLY_BRACES");
    parseToken();
    match("RIGHT_CURLY_BRACES");
    printf("Found if statement");