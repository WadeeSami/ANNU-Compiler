#include "token.h"

INTGER_TOKEN::INTGER_TOKEN(LEXEME_TYPE type, int value)
{
	this->value = value;
	this->type = type;
}


FLOAT_TOKEN::FLOAT_TOKEN(LEXEME_TYPE type, float value)
{
	this->float_value = value;
	this->type = type;
}

float FLOAT_TOKEN::getValue()
{
	return this->float_value;
}

STRING_TOKEN::STRING_TOKEN(LEXEME_TYPE type, char * value)
{
	this->str_ptr = value;
	this->type = type;
}

char * STRING_TOKEN::getValue()
{
	return this->str_ptr;
}

KEYWORD_TOKEN::KEYWORD_TOKEN(LEXEME_TYPE type, char * value)
{
	this->type = type;
	this->str_ptr = value;
}

OPERATOR_TOKEN::OPERATOR_TOKEN(LEXEME_TYPE type, char * value)
{
	this->type = type;
	this->operatorName = value;
}
