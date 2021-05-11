/*
    ====[A really really really really really basic LISP interpreter]====
    Author: Nicholas Jordan
    Class: CMPS 3500 Final
    Date: 11/18/2020

    Compile with: gcc main.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define OP_ADD '+'
#define OP_SUB '-'
#define OP_MUL '*'
#define OP_DIV '/'
#define OP_MOD '%'

void printUsage() {
    printf("Usage: (<+,-,*,/,%%> <integer> <integer> ... )\n");
}

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

//sums any number of integers together:
//(+ 1 1) +> 1 + 1
//(+ 12 4 64 3 75 ...) => 12 + 4 + 64 + 3 + 75 + ...
int compute_add(char* expr) {
    if (*(expr+1) == ')' || *(expr+1) == '\n') {
        return FALSE;
    }
    int sum = 0;
    while (*expr != ')') {
        if (*expr == '\n') {    //needs to end with ')'
            return 1;
        } else if (isdigit(*expr)) {
            int length = 0;
            sum += getNum(expr, &length);
            expr += length;
        } else {
            //treat everything that isnt checked for as whitespace and move on
            *expr++;
        }
    }
    printf("Sum = %d\n", sum);
    return TRUE;
}

//subtracts any number of integers together:
//(- 1 1) +> 1 - 1
//(- 12 4 64 3 75 ...) => 12 - 4 - 64 - 3 - 75 - ...
int compute_sub(char* expr) {
    if (*(expr+1) == ')' || *(expr+1) == '\n') {
        return FALSE;
    }
    int diff;
    int first = 0;  //flag whether the first number has been acknowledged
    while (*expr != ')') {
        if (*expr == '\n') {    //needs to end with ')'
            return 1;
        } else if (isdigit(*expr)) {
            int length = 0;
            int n = getNum(expr, &length);
            if (first == 0) {
                diff = n;
                first++;    //set flag
            } else {
                diff -= n;
            }
            expr += length;
        } else {
            //treat everything that isnt checked for as whitespace and move on
            *expr++;
        }
    }
    printf("Difference = %d\n", diff);
    return TRUE;
}

//multiplies any number of integers together:
//(* 1 1) +> 1 * 1
//(* 12 4 64 3 75 ...) => 12 * 4 * 64 * 3 * 75 * ...
int compute_mul(char* expr) {
    if (*(expr+1) == ')' || *(expr+1) == '\n') {
        return FALSE;
    }
    int prod;
    int first = 0;  //flag whether the first number has been acknowledged
    while (*expr != ')') {
        if (*expr == '\n') {    //needs to end with ')'
            return 1;
        } else if (isdigit(*expr)) {
            int length = 0;
            int n = getNum(expr, &length);
            if (first == 0) {
                prod = n;
                first++;    //set flag
            } else {
                prod *= n;
            }
            expr += length;
        } else {
            //treat everything that isnt checked for as whitespace and move on
            *expr++;
        }
    }
    printf("Product = %d\n", prod);
    return TRUE;
}

//divides any number of integers together:
//(/ 1 1) +> 1 / 1
//(/ 12 4 64 3 75 ...) => 12 / 4 / 64 / 3 / 75 / ...
//excludes 0's in the denominator
int compute_div(char* expr) {
    if (*(expr+1) == ')' || *(expr+1) == '\n') {
        return FALSE;
    }
    float quot;
    int first = 0;  //flag whether the first number has been acknowledged
    while (*expr != ')') {
        if (*expr == '\n') {    //needs to end with ')'
            return 1;
        } else if (isdigit(*expr)) {
            int length = 0;
            int n = getNum(expr, &length);
            if (first == 0) {
                quot = n;
                first++;    //set flag
            } else {
                if (n == 0) {
                    printf("You cannot divide by 0..., so it was excluded from evaluation\n");
                } else {
                    quot /= n;
                }
            }
            expr += length;
        } else {
            //treat everything that isnt checked for as whitespace and move on
            *expr++;
        }
    }
    printf("Quotient = %f\n", quot);
    return TRUE;
}

int compute_mod(char* expr) {
    if (*(expr+1) == ')' || *(expr+1) == '\n') {
        return FALSE;
    }
    int remainder;
    int count = 0;  //mod can only be between 2 numbers
    while (*expr != ')') {
        if (*expr == '\n') {    //needs to end with ')'
            return 1;
        } else if (isdigit(*expr)) {
            int length = 0; //length of the number found in getNum
            int n = getNum(expr, &length);
            if (count == 0) {
                remainder = n;
                count++;
            } else if (count == 1) {
                remainder = remainder % n;
                count++;
            } else {
                printf("You can only mod between 2 numbers..., so %d was excluded from evaluation\n", n);
            }
            expr += length;
        } else {
            //treat everything that isnt checked for as whitespace and move on
            *expr++;
        }
    }
    printf("Remainder = %d\n", remainder);
    return TRUE;
}

int eval(char* expr) {
    if (*expr != '(') { //must begin with '('
        printUsage();
        return FALSE;
    }
    printf("Evaluating %s", expr);
    while (*expr++ != '\n') {
        switch(*expr) {
            case OP_ADD: ;
                if (!compute_add(expr)) printUsage();
                return TRUE;  //quit while loop
                break;
            case OP_SUB:
                if (!compute_sub(expr)) printUsage();
                return TRUE;
                break;
            case OP_MUL:
                if (!compute_mul(expr)) printUsage();
                return TRUE;
                break;
            case OP_DIV:
                if (!compute_div(expr)) printUsage();
                return TRUE;
                break;
            case OP_MOD:
                if (!compute_mod(expr)) printUsage();
                return TRUE;
                break;
            case ' ':
                //ignore spaces
                break;
            default:
                //any other character is invalid
                printUsage();
                return FALSE;
                break;
        }
    }
    return TRUE;
}

char* read() {
    char* expr = malloc(256);
    fgets(expr, 256, stdin);
    return expr;
}

int main() {
    printf("Lisp interpretor is now listening for input strings\n");
    printUsage();
    while(1) {
        eval(read());
    }
    return 0;
}