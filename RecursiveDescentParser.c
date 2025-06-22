#include <stdio.h>
#include <stdlib.h>  // For exit()
#include <ctype.h>   // For isalnum()

#define MAX 100

char input[MAX];
int pos = 0;  // Position in the input string

void E();
void E_prime();
void T();
void T_prime();
void F();

void error() {
    printf("Error in parsing!\n");
    exit(1);
}

void match(char expected) {
    if (input[pos] == expected) {
        pos++;
    } else {
        error();
    }
}

void E() {
    T();
    E_prime();
}

void E_prime() {
    if (input[pos] == '+') {
        match('+');
        T();
        E_prime();
    }
    // else ε (do nothing)
}

void T() {
    F();
    T_prime();
}

void T_prime() {
    if (input[pos] == '*') {
        match('*');
        F();
        T_prime();
    }
    // else ε (do nothing)
}

void F() {
    if (input[pos] == '(') {
        match('(');
        E();
        match(')');
    } else if (isalnum(input[pos])) {
        match(input[pos]);  // Accept single letter or digit
    } else {
        error();
    }
}

int main() {
    printf("Enter an arithmetic expression: ");
    scanf("%s", input);

    E();  // Start parsing

    if (input[pos] == '\0') {
        printf("The input is a valid arithmetic expression.\n");
    } else {
        error();
    }

    return 0;
}
