#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char lookahead;

void expression();
void term();
void factor();
void match(char expected);
void error();
void getNextToken();

void getNextToken() {
    do {
        lookahead = getchar(); // Skip whitespace
    } while (lookahead == ' ');
}

void match(char expected) {
    if (lookahead == expected) {
        getNextToken();
    } else {
        error();
    }
}

void error() {
    printf("Syntax error!\n");
    exit(1);
}

void factor() {
    if (isdigit(lookahead)) {
        // Accept a digit and move on
        getNextToken();
    } else if (lookahead == '(') {
        match('(');
        expression();
        match(')');
    } else {
        error();
    }
}

void term() {
    factor();
    while (lookahead == '*' || lookahead == '/') {
        getNextToken();
        factor();
    }
}

void expression() {
    term();
    while (lookahead == '+' || lookahead == '-') {
        getNextToken();
        term();
    }
}

void parse() {
    getNextToken();  // Initialize lookahead
    expression();    // Start parsing
    if (lookahead != '\n' && lookahead != EOF) {
        error(); // Unexpected extra characters
    }
}

int main() {
    printf("Enter an arithmetic expression: ");
    parse();
    printf("Expression is valid!\n");
    return 0;
}
