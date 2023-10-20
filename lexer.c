#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Token type enumeration
typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_CONSTANT,
    TOKEN_STRING,
    TOKEN_SPECIAL_SYMBOL,
    TOKEN_OPERATOR,
    TOKEN_ERROR,
    TOKEN_END_OF_FILE
} TokenType;

// Structure to represent a token
typedef struct {
    TokenType type;
    char value[100];
} Token;

// Global variables for source code and position
char sourceCode[10000];
int currentPosition = 0;

// Keywords in your language (modify as needed)
const char* keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

// Special symbols in your language (modify as needed)
const char* specialSymbols[] = {"{", "}", "(", ")", ";", ",", "[", "]"};

// Function to initialize the lexer
void initializeLexer(const char* code) {
    strncpy(sourceCode, code, sizeof(sourceCode) - 1);
    sourceCode[sizeof(sourceCode) - 1] = '\0';
    currentPosition = 0;
}

// Function to get the next character from the source code
char getNextChar() {
    return sourceCode[currentPosition++];
}

// Function to check if a character is a valid identifier character
bool isValidIdentifierChar(char c) {
    return isalnum(c) || c == '_';
}

bool isKeyword(const char* str) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to get the next token
Token getNextToken() {
    Token token;
    char currentChar = getNextChar();

    while (isspace(currentChar)) {
        currentChar = getNextChar();  // Skip whitespace
    }

    if (currentChar == '\0') {
        token.type = TOKEN_END_OF_FILE;
        return token;
    }

    if (isalpha(currentChar) || currentChar == '_') {
        int i = 0;
        token.value[i++] = currentChar;
        while (isValidIdentifierChar(sourceCode[currentPosition])) {
            token.value[i++] = getNextChar();
        }
        token.value[i] = '\0';

        // Check if the identifier is a keyword
        if (isKeyword(token.value)) {
            token.type = TOKEN_KEYWORD;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }
    } 
    else if (isdigit(currentChar)) {
        int i =
