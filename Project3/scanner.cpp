#include "scanner.h"
#include <regex>

#include <iostream>
using namespace std;
//neccessary arrays
int keys = 30; /* number of keywords */
char *keyword[] = {
	"and", "begin", "boolean", "by", "constant",
	"do", "else", "end", "false", "fi",
	"float", "for", "from", "function", "if",
	"integer", "not", "od", "or", "procedure",
	"program", "read", "return", "string", "then",
	"to", "true","var", "while", "write"
};

LEXEME_TYPE key_type[] = {
	kw_and, kw_begin, kw_boolean, kw_by, kw_constant,
	kw_do, kw_else, kw_end, kw_false, kw_fi,kw_float,
	kw_for, kw_from, kw_function, kw_if, kw_integer, kw_not,
	kw_od, kw_or, kw_procedure, kw_program,kw_read, kw_return,
	kw_string, kw_then, kw_to, kw_true, kw_var, kw_while, kw_write
};
LEXEME_TYPE operator_type[] =
{
	lx_colon,lx_plus , lx_minus , lx_not ,
	lx_star ,lx_slash,lx_eq,lx_lt,
	lx_gt , lx_dot , lx_semicolon,
	lx_comma, lx_lparen,lx_rparen,
	lx_lcbracket ,lx_rcbracket ,lx_lbracket,lx_rbracket
};

int operatorsCount = 18; /* number of operators */
char  operators[] = {
	 ':'  ,  '+' , '-' ,'!',
	'*' , '/' ,  '='  , '<' ,
	'>'  ,'.' , ';' ,
	 ',' , '(' , ')',
	 '{' ,'}' , '[' , ']' 
};



bool SCANNER::isNumber(char c)
{
	return ((c - '0') >= 0 && (c - '0') <= 9);
}

int SCANNER::convertToInteger(char c)
{
	return c - '0';
}

bool SCANNER::isChar(char c)
{
	return ( (c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z') );
}

bool SCANNER::isAKeyword(char * word)
{
	//cout << word;
	//loop through the array and check
	//cout<<strcat(word, "\0");
	for (int i = 0; i < keys; i++) {
		
		if (strcmp(word , keyword[i]) == 0) {
			return true;
		}
	}
	return false;
}

bool SCANNER::isIdentefier(char * word)
{
	return std::regex_match(word, std::regex("[a-zA-Z][a-zA-Z0-9_]*"));
		
}

bool SCANNER::isOperator(char  c)
{
	for (int i = 0; i < operatorsCount; i++) {
		if (c == operators[i])
			return true;
	}
	return false;
}

void SCANNER::skipWhiteSpaces()
{
	while (this->peekChar = Fd->GetChar()) {
		if (this->peekChar == WHITE_SAPCE_CHAR || this->peekChar == TAB_CHAR) {
			continue;
		}
		else if (this->peekChar == NEW_LINE_CHAR) {
			//next 
			this->lineNumber++;
		}
		else {
			break;
		}
	}
	return;
}

TOKEN * SCANNER::handleNumbers()
{
	//int v = 0;
	//if (isNumber(this->peekChar)) 
	//{
	//	do 
	//	{
	//		v = v * 10 + convertToInteger(this->peekChar);
	//		this->peekChar = Fd->GetChar();
	//	} while (isNumber(this->peekChar));
	//	//return a number token
	//	return new INTGER_TOKEN(lx_integer, v);
	//}
	if (isNumber(this->peekChar)) {
		char numberString[MAX_TOEKN_SIZE] = { '\0' };
		int index = 0;
		bool isFloat = false;
		while (isNumber(this->peekChar) || this->peekChar == DOT_CHARACTER && !isFloat) {
			if (this->peekChar == DOT_CHARACTER) {
				isFloat = true;
				this->peekChar = Fd->GetChar();
				char tempDot = this->peekChar;
				Fd->unGetChar(this->peekChar);
				if (!this->isNumber(this->peekChar)) {
					//error
					this->errorThrown = true;
					return NULL;
				}
				this->peekChar = tempDot;
			}
			numberString[index++] = this->peekChar;
			this->peekChar = Fd->GetChar();
		}
		cout << "This is an integer" << endl;
		//make sure it's a number 
		if (isFloat) {
			cout << "Hello " << atof(numberString) << endl;
			return new FLOAT_TOKEN(lx_float, atof(numberString));
		}
		else {
			cout << "Hello " << atoi(numberString) << endl;
			return new INTGER_TOKEN(lx_integer, atoi(numberString));
		}
	}
		return NULL;
}

TOKEN * SCANNER::handleKeyWords()
{
		//collect latters into a phrase
	if (isChar(this->peekChar))
	{
		char * tempBuffer = new char[MAX_TOEKN_SIZE];
		for (int i = 0; i < MAX_TOEKN_SIZE; i++)
		{
			tempBuffer[i] = NULL;
		}
		int index = 0;
		do
		{
			tempBuffer[index++] = this->peekChar;
			this->peekChar = Fd->GetChar();
		} while (isChar(this->peekChar) || isNumber(this->peekChar));
		if (isAKeyword(tempBuffer))
		{
			//this is a reserved word, return its token
			return new KEYWORD_TOKEN(getKeyWordLexemeName(tempBuffer), tempBuffer);
		}
		//this is a new id
		//create a new token for it
		//you must check the syntax of the id
		if (this->isIdentefier(tempBuffer))
			return new STRING_TOKEN(lx_identifier, tempBuffer);
		else
		{
			this->Fd->ReportError("Illegal Identfier");
			return nullptr;
		}
	}
}

TOKEN * SCANNER::handleOperators()
{
	OPERATOR_TOKEN * operatorToken = NULL;
	int state = 0;
	while (this->isOperator(this->peekChar) && this->peekChar!='\0') {
		switch (state) 
		{
		case 0:
			//check the character
			if (this->peekChar == '>')state = 1;
			else if (this->peekChar == '<')state = 2;
			else if (this->peekChar == ':')state = 3;
			else if (this->peekChar == '!')state = 4;
			else if (this->isOperator(this->peekChar))state = 5;
			else return NULL;
			break;
		case 1:
			this->peekChar = Fd->GetChar();
			if (this->peekChar == '=')
			{
				this->peekChar = Fd->GetChar();
				return operatorToken = new OPERATOR_TOKEN(lx_ge, ">=");
			}
			break;
		case 2:
			this->peekChar = Fd->GetChar();
			if (this->peekChar == '=')
			{
				this->peekChar = Fd->GetChar();
				return operatorToken = new OPERATOR_TOKEN(lx_le, "<=");
			}
			break;
		case 3:
			this->peekChar = Fd->GetChar();
			if (this->peekChar == '=')
			{
				this->peekChar = Fd->GetChar();
				return operatorToken = new OPERATOR_TOKEN(lx_colon_eq, ":=");
			}
			break;
		case 4:
			this->peekChar = Fd->GetChar();
			if (this->peekChar == '=')
			{
				this->peekChar = Fd->GetChar();
				return operatorToken = new OPERATOR_TOKEN(lx_neq, "!=");
			}
			break;
		case 5:
			
			return operatorToken = new OPERATOR_TOKEN(this->getOperatorLexemeName(this->peekChar), &this->peekChar);
			break;
		default:
			break;
		}
	}
	return nullptr;
}

TOKEN * SCANNER::handleStrings()
{
	char  stringValue[MAX_TOEKN_SIZE] = {};
	
	int index = 0;
	if (this->peekChar == DOUBLE_QUOTE_CHAR) {
		while ((this->peekChar = Fd->GetChar()) != DOUBLE_QUOTE_CHAR) {
			if (this->peekChar == NEW_LINE_CHAR) {
				//throw an error
				this->Fd->ReportError("Illegal String Identifier");
				this->errorThrown = true;
				return NULL;
			}
			stringValue[index++] = this->peekChar;
		}
		return new STRING_TOKEN(lx_string, stringValue);
	}
	return nullptr;
}

TOKEN * SCANNER::get_id()
{
	return nullptr;
}

TOKEN * SCANNER::get_string()
{
	return nullptr;
}

TOKEN * SCANNER::get_int()
{
	return nullptr;
}

void SCANNER::skipComments()
{
	if (this->peekChar == COMMENT_CHAR) {
		//check the next
		this->peekChar = Fd->GetChar();
		if (this->peekChar == COMMENT_CHAR) {
			//keep reading until you reach other # or the line ends
			while ((this->peekChar = Fd->GetChar()) != COMMENT_CHAR) {
				if ( (this->peekChar == NEW_LINE_CHAR)  || (this->peekChar == '\0')) {
					cout << "This is a comment" << endl;
					return;
				}
				continue;
			}
			
			//now a comment character in then end of the comment
			if (Fd->GetChar() == COMMENT_CHAR) {
				cout << "This is a comment" << endl;
				return;
			}
			else {
				this->Fd->ReportError("Illegal Identfier");
				Fd->unGetChar(this->peekChar);
				this->errorThrown = true;
				return;
			}
		}
		else {
			//throught an error
			this->Fd->ReportError("Illegal Identfier");
			this->errorThrown = true;
			return ;
		}
	}
	else {
		return;
	}
}

LEXEME_TYPE SCANNER::getKeyWordLexemeName(char * reserevedWord)
{
	int index ;
	for (index = 0; index < keys; index++) {
		if (strcmp(reserevedWord, keyword[index]) == 0) {
			return key_type[index];
		}
	}
}
LEXEME_TYPE SCANNER::getOperatorLexemeName(char operatorCHar)
{
	int index;
	for (index = 0; index < operatorsCount; index++)
	{
		if (operatorCHar == operators[index])
			return operator_type[index];
	}
}


SCANNER::SCANNER()
{
	lineNumber = 1;
}

TOKEN * SCANNER::Scan()
{
	this->errorThrown = false;
	this->peekChar = ' ';
	//skip white spaces
	this->skipWhiteSpaces();

	//skip comments
	this->skipComments();
	if (this->errorThrown) {
		return NULL;
	}

	//this->peekChar = Fd->GetChar();
	//handle keywords OR IDs
	TOKEN * keyWordToken = this->handleKeyWords();
	if (keyWordToken != NULL) {
		return keyWordToken;
	}

	//handle String
	TOKEN * stringToken  = this->handleStrings();
	if (stringToken != NULL) {
		return stringToken;
	}
	//handle Numbers
	TOKEN * numberToken = this->handleNumbers();
	if (numberToken != NULL) {
		return numberToken;
	}

	//handle operators
		TOKEN * operatorToken = this->handleOperators();
		if (operatorToken != NULL)
		{
			return operatorToken;
		}
		return NULL;
}



