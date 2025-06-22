#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

void removeLeftRecursion(char nonTerminal, char productions[MAX][MAX], int n) {
    char alpha[MAX][MAX], beta[MAX][MAX];
    int i, alphaCount = 0, betaCount = 0;
    for (i = 0; i < n; i++) {
        // Remove "A->" from each production
        if (productions[i][0] == nonTerminal && productions[i][1] == '-' && productions[i][2] == '>') {
            char *rhs = productions[i] + 3;  // Skip "A->"
            if (rhs[0] == nonTerminal) {
                // Left recursive: A->Aa, store 'a'
                strcpy(alpha[alphaCount++], rhs + 1);
            } else {
                // Not left recursive: A->b, store 'b'
                strcpy(beta[betaCount++], rhs);
            }
        }
    }

    if (alphaCount == 0) {
        printf("No Left Recursion in %c\n", nonTerminal);
        return;
    }

    // Output transformed grammar
    printf("%c ->", nonTerminal);
    for (i = 0; i < betaCount; i++) {
        printf(" %s%c'", beta[i], nonTerminal);
        if (i < betaCount - 1) printf(" |");
    }
    printf("\n");

    printf("%c' ->", nonTerminal);
    for (i = 0; i < alphaCount; i++) {
        printf(" %s%c'", alpha[i], nonTerminal);
        if (i < alphaCount - 1) printf(" |");
    }
    printf(" | e\n");
}

int main() {
    char nonTerminal;
    int n, i;
    char productions[MAX][MAX];

    printf("Enter the non-terminal: ");
    scanf(" %c", &nonTerminal);

    printf("Enter the number of productions: ");
    scanf("%d", &n);

    printf("Enter the productions (Format: A->Aa or A->b):\n");
    for (i = 0; i < n; i++) {
        scanf(" %s", productions[i]);
    }

    removeLeftRecursion(nonTerminal, productions, n);
    return 0;
}

