#pragma once
/* scanner .h*/
#ifndef __SCANNER__H
#define __SCANNER__H
#define WHITE_SAPCE_CHAR ' '
#define TAB_CHAR '\t'
#define NEW_LINE_CHAR '\0'
#define MAX_TOEKN_SIZE 50
#define COMMENT_CHAR '#'
#define DOUBLE_QUOTE_CHAR '\"'
#define DOT_CHARACTER '.'

#include "fd.h"
#include "token.h"
#include <map>
#include <iostream>
#include <string>
#endif


class SCANNER {
private:
	FileDescriptor *Fd;
	// define your functions ..
	//I would define the following functions..
	// void skip_comments();
	bool isNumber(char c);
	int convertToInteger(char c);
	bool isChar(char c);
	bool isAKeyword(char * word);
	bool isIdentefier(char * word);
	bool isOperator(char c);
	bool errorThrown = false;
	void skipWhiteSpaces();
	TOKEN *handleNumbers();
	TOKEN *handleKeyWords();
	TOKEN *handleOperators();
	TOKEN * handleStrings();
	TOKEN *get_id();
	TOKEN *get_string();
	TOKEN *get_int(); // gets integers and floats
	void skipComments();
	int lineNumber ;
	char peekChar;
	LEXEME_TYPE getKeyWordLexemeName(char * keyword);
	LEXEME_TYPE getOperatorLexemeName(char operatorCHar);
public:
	SCANNER();
	SCANNER(FileDescriptor *fd) { 
		Fd = fd; 
		lineNumber = 1;
	};
	TOKEN* Scan();
	
	// You may define it as TOKEN *Scan(FileDescriptor *fd);

};

// It is helpful to define the following arrays in your .cpp file

