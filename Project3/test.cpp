#include <iostream>
#include <regex>
#include "scanner.h"
using namespace std;


int main() {
	char * Lexemes[] =
	{
		"lx_identifier", "lx_integer", "lx_string", "lx_float","lx_float",
		/* Keywords */
		"kw_program",
		"kw_var", "kw_constant", "kw_integer", "kw_boolean", "kw_string", "kw_float",
		"kw_true", "kw_false", "kw_if", "kw_fi", "kw_then", "kw_else",
		"kw_while", "kw_do","kw_od",
		"kw_and","kw_or",
		"kw_read", "kw_write",
		"kw_for", "kw_from", "kw_to", "kw_by",
		"kw_function", "kw_procedure", "kw_return", "kw_return", "kw_begin", "kw_end",
		/* Operators */
		"lx_lparen", "lx_rparen", "lx_lbracket", "lx_rbracket", "lx_lcbracket", "lx_rcbracket","lx_not",
		"lx_colon", "lx_dot", "lx_semicolon", "lx_comma", "lx_colon_eq",
		"lx_plus", "lx_minus", "lx_star", "lx_slash",
		"lx_eq", "lx_neq", "lx_lt", "lx_le", "lx_ge", "lx_ge", "lx_eof"
	};
	FileDescriptor *fd = new FileDescriptor("example.txt");

	SCANNER scanner(fd);
	TOKEN * t = NULL;
	int i = 0;
	while (fd->GetCurrLine()!=NULL) {
		while ((t = scanner.Scan()) != NULL) {
			//cout << t->str_ptr ;
			cout <<++i<<"\t" << t->type <<"\t"<< Lexemes[t->type] << endl;
		}
	}
		
	
	int x = 0;
	cin >> x;
	return 0;
}