/*
    ====[A basic LISP interpreter]====
    Author: Nicholas Jordan
    Class: CMPS 3500 Final
    Date: 11/18/2020

    Compile with: gcc lisp.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define OP_ADD '+'
#define OP_SUB '-'
#define OP_MUL '*'
#define OP_DIV '/'
#define OP_MOD '%'

//global error buffer
static char err[64];

//keep track of how deep in recursion we currently are (depth)
//and record the farthest in recursion we've been (max_depth)
//===============================
//everytime we find a new operation (marked by finding '(' ), we increment depth
//everytime we return from a 'compute_' function we decrement depth
//at the start of each 'compute_' function we check if our current depth is our new max_depth
//===============================
//we need to do this because when we return from the last recursive call, the 'expr' pointer
//goes back to what it was before the recursive call, so we need to adjust for that and iterate
//the 'expr' pointer until we return to the where we were right before we returned.
//the process can be shown by the following code snippet located in each 'compute_' function:
/*
if (depth == 0) max_depth = 0;
for (int i = 0; i < max_depth - depth; i++) {
        while (*expr++ != ')') {}
}
*/
//max_depth needs to be reset when we return to the first function that enacted the recursive call
//because the max_depth of future nested operations may not excede the current max_depth which will
//cause us to skip over more ')' than we should and could cause numbers to be excluded from calculation
static int depth = 0;
static int max_depth = 0;

//forward declaration
float eval(char* expr);

//finds a number in the string (expr),
//calculates how many digits are in the number (length - pass by pointer),
//and returns that number (num),
//===============================
//if the length is not accounted for, we end up with this example:
//(+ 213 32) => computes 213 + 13 + 3 + 32 + 2
//so we want to skip to the end of the number after it is read
int getNum(char* expr, int* length) {
    int num;
    sscanf(expr++, "%d", &num);
    if (num == 0) {
        *length = 1;
    } else {
        *length = floor(log10(abs(num)))+1;
    }
    return num;
}

int compute_add(char* expr) {
    if (depth > max_depth) {
        max_depth = depth;
    }
    int sum = 0;
    while (*(expr++) != ')') {
        if (*expr == '\n' || *expr == '\0') {    //needs to end with ')'
            strcpy(err, "Unfinished operation");
            return 0;
        } else if (isdigit(*expr)) {
            int length = 0;
            sum += getNum(expr, &length);
            expr += length;
        } else if (*expr == '(') {
            depth++;
            sum += (int)eval(expr);
            //after calling eval(), expr points to where it was prior to the call 
            //so we need to catch back up to the last considered instance of ')'
            for (int i = 0; i < max_depth - depth; i++) {
                    while (*expr++ != ')') {}
            }
            if (depth == 0) max_depth = 0;
        } else if (*expr == ')') {
            break;
        } else if (*expr == ' ') {
            //ignore spaces
        } else {
            //any other character is invalid
            strcpy(err, "Invalid character: ");
            strcat(err, &expr[0]);
            return 0;
        }
    }
    depth--;
    return sum;
}

int compute_sub(char* expr) {
    if (depth > max_depth) {
        max_depth = depth;
    }
    int diff;
    int first = 0;  //flag whether the first number has been acknowledged
    while (*expr++ != ')') {
        if (*expr == '\n' || *expr == '\0') {    //needs to end with ')'
            strcpy(err, "Unfinished operation");
            return 0;
        } else if (isdigit(*expr)) {
            int length = 0;
            int n = getNum(expr, &length);
            if (first == 0) {
                diff = n;
                first = 1;    //set flag
            } else {
                diff -= n;
            }
            expr += length;
        } else if (*expr == '(') {
            depth++;
            if (first == 0) {
                diff = (int)eval(expr);
                first = 1;    //set flag
            } else {
                diff -= (int)eval(expr);
            }
            //after calling eval(), expr points to where it was prior to the call 
            //so we need to catch back up to the last considered instance of ')'
            for (int i = 0; i < max_depth - depth; i++) {
                    while (*expr++ != ')') {}
            }
            if (depth == 0) max_depth = 0;
        } else if (*expr == ')') {
            break;
        } else if (*expr == ' ') {
            //ignore spaces
        } else {
            //any other character is invalid
            strcpy(err, "Invalid character: ");
            strcat(err, expr);
            return 0;
        }
    }
    depth--;
    return diff;
}

int compute_mul(char* expr) {
    if (depth > max_depth) {
        max_depth = depth;
    }
    int prod;
    int first = 0;  //flag whether the first number has been acknowledged
    while (*expr++ != ')') {
        if (*expr == '\n' || *expr == '\0') {    //needs to end with ')'
            strcpy(err, "Unfinished operation");
            return 0;
        } else if (isdigit(*expr)) {
            int length = 0;
            int n = getNum(expr, &length);
            if (first == 0) {
                prod = n;
                first = 1;    //set flag
            } else {
                prod *= n;
            }
            expr += length;
        } else if (*expr == '(') {
            depth++;
            if (first == 0) {
                prod = (int)eval(expr);
                first = 1;    //set flag
            } else {
                prod *= (int)eval(expr);
            }
            //after calling eval(), expr points to where it was prior to the call 
            //so we need to catch back up to the last considered instance of ')'
            for (int i = 0; i < max_depth - depth; i++) {
                    while (*expr++ != ')') {}
            }
            if (depth == 0) max_depth = 0;
        } else if (*expr == ')') {
            break;
        } else if (*expr == ' ') {
            //ignore spaces
        } else {
            //any other character is invalid
            strcat(err, "Invalid character: ");
            strcat(err, expr);
            return 0;
        }
    }
    depth--;
    return prod;
}

float compute_div(char* expr) {
    if (depth > max_depth) {
        max_depth = depth;
    }
    float quot;
    int first = 0;  //flag whether the first number has been acknowledged
    while (*expr++ != ')') {
        if (*expr == '\n' || *expr == '\0') {    //needs to end with ')'
            strcpy(err, "Unfinished operation");
            return 0;
        } else if (isdigit(*expr)) {
            int length = 0;
            int n = getNum(expr, &length);
            if (first == 0) {
                quot = n;
                first++;    //set flag
            } else {
                if (n == 0) {
                    strcat(err, "You cannot divide by 0");
                    return 0;
                } else {
                    quot /= n;
                }
            }
            expr += length;
        } else if (*expr == '(') {
            depth++;
            if (first == 0) {
                quot = eval(expr);
                first = 1;    //set flag
            } else {
                quot /= eval(expr);
            }
            //after calling eval(), expr points to where it was prior to the call 
            //so we need to catch back up to the last considered instance of ')'
            for (int i = 0; i < max_depth - depth; i++) {
                    while (*expr++ != ')') {}
            }
            if (depth == 0) max_depth = 0;
        } else if (*expr == ')') {
            break;
        } else if (*expr == ' ') {
            //ignore spaces
        } else {
            //any other character is invalid
            strcpy(err, "Invalid character: ");
            strcat(err, expr);
            return 0;
        }
    }
    depth--;
    return quot;
}

int compute_mod(char* expr) {
    if (depth > max_depth) {
        max_depth = depth;
    }
    int remainder;
    int count = 0;  //mod can only be between 2 numbers
    while (*expr++ != ')') {
        if (*expr == '\n' || *expr == '\0') {    //needs to end with ')'
            strcpy(err, "Unfinished operation");
            return 0;
        } else if (isdigit(*expr)) {
            int length = 0; //length of the number found in getNum
            int n = getNum(expr, &length);
            if (count == 0) {
                remainder = n;
                count++;
            } else if (count == 1) {
                if (n == 0) {
                    strcat(err, "You cannot modulous by 0");
                    return 0;
                } else {
                    remainder = remainder % n;
                    count++;
                }
            } else {
                strcat(err, "You can only modulous two numbers");
                return 0;
            }
            expr += length;
        } else if (*expr == '(') {
            //modulous cant be done with floats, type cast to int
            if (count == 0) {
                depth++;
                remainder = (int)eval(expr);
                count++;
            } else if (count == 1) {
                depth++;
                int n = (int)eval(expr);
                if (n == 0) {
                    strcat(err, "You cannot modulous by 0");
                    return 0;
                } else {
                    remainder = remainder % n;
                    count++;
                }
            } else {
                strcat(err, "You can only modulous two numbers");
                return 0;
            }
            //after calling eval(), expr points to where it was prior to the call 
            //so we need to catch back up to the last considered instance of ')'
            for (int i = 0; i < max_depth - depth; i++) {
                    while (*expr++ != ')') {}
            }
            if (depth == 0) max_depth = 0;
        } else if (*expr == ')') {
            break;
        } else if (*expr == ' ') {
            //ignore spaces
        } else {
            //any other character is invalid
            strcpy(err, "Invalid character: ");
            strcat(err, expr);
            return 0;
        }
    }
    depth--;
    return remainder;
}

float eval(char* expr) {
    if (*expr != '(') {
        strcpy(err, "Expression must begin with '('");
        return 0;
    }
    float result;
    while (*expr++ != '\n') {
        if (*expr == OP_ADD) {
            result = compute_add(expr++);
            break;
        } else if (*expr == OP_SUB) {
            result = compute_sub(expr++);
            break;
        } else if (*expr == OP_MUL) {
            result = compute_mul(expr++);
            break;
        } else if (*expr == OP_DIV) {
            result = compute_div(expr++);
            break;
        } else if (*expr == OP_MOD) {
            result = compute_mod(expr++);
            break;
        } else if (*expr == ' ') {
            //ignore spaces
        } else if (*expr == '\n' || *expr == ')') {
            strcpy(err, "Unfinished operation");
            return 0;
        } else {
            //any other character is invalid
            strcpy(err, "Invalid character: ");
            strcat(err, expr);
            return 0;
        }
    }
    return result;
}

char* read() {
    char* expr = malloc(256);
    fgets(expr, 256, stdin);
    printf("Evaluating %s", expr);
    return expr;
}

int main() {
    memset(err, 0, sizeof(err));
    printf("Lisp interpretor is now listening for input strings\n");
    printf("NOTE: Operations can be nested. Ex: (+ 2 (* 4 2))\n");
    printf("NOTE: The '%%' operation takes the floor of nested division operations\n");
    printf("Usage: (<+,-,*,/,%%> <integer> <integer> ... )\n\n");
    while(1) {
        char* expr = read();
        float result = eval(expr);
        if ((int)strlen(err) == 0) {
            printf("Result: %f\n\n", result);
        } else {
            printf("Error: %s\n", err);
            memset(err, 0, sizeof(err));
        }
        depth = 0;
        max_depth = 0;
        free(expr);
    }
    return 0;
}