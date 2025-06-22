#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#define MAX 100 
typedef struct { 
char op; 
char arg1; 
char arg2; 
char result; 
} Instruction; 
Instruction ir[MAX]; 
int instructionCount = 0; 
char tempVar = 't';  // Starting variable for temporary storage 
void generateIR(char op, char arg1, char arg2, char result) { 
ir[instructionCount].op = op; 
ir[instructionCount].arg1 = arg1; 
ir[instructionCount].arg2 = arg2; 
ir[instructionCount].result = result; 
instructionCount++; 
} 
char getNextTempVar() { 
return tempVar++; 
} 
int precedence(char op) { 
if (op == '+' || op == '-') return 1; 
if (op == '*' || op == '/') return 2; 
return 0; 
} 
void parseExpression(char *expr) { 
int i = 0; 
char stack[MAX]; 
int top = -1; 
char output[MAX]; 
int outPos = 0; 
// Shunting-yard algorithm to convert to postfix 
while (expr[i] != '\0') { 
if (isalnum(expr[i])) { 
output[outPos++] = expr[i]; 
} else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') { 
while (top != -1 && precedence(stack[top]) >= precedence(expr[i])) { 
output[outPos++] = stack[top--]; 
} 
stack[++top] = expr[i]; 
} 
i++; 
} 
while (top != -1) { 
output[outPos++] = stack[top--]; 
} 
output[outPos] = '\0'; 
// Generate IR from postfix expression 
i = 0; 
char operands[MAX]; 
int opTop = -1; 
while (output[i] != '\0') { 
if (isalnum(output[i])) { 
operands[++opTop] = output[i]; 
} else { 
char arg2 = operands[opTop--]; 
char arg1 = operands[opTop--]; 
char result = getNextTempVar(); 
generateIR(output[i], arg1, arg2, result); 
operands[++opTop] = result; 
} 
i++; 
} 
} 
void printIR() { 
printf("Intermediate Representation (Three-Address Code):\n"); 
int i;  // Declare i outside the for loop 
for (i = 0; i < instructionCount; i++) { 
printf("%c = %c %c %c\n", ir[i].result, ir[i].arg1, ir[i].op, ir[i].arg2); 
} 
} 
int main() { 
char expression[MAX]; 
printf("Enter an arithmetic expression (e.g., a+b*c/d-e): "); 
scanf("%s", expression); 
parseExpression(expression); 
printIR(); 
return 0; 
}
