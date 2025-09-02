#include "vbc.h"
#include <stdlib.h>
#include <stdio.h>

void parse_error_here(t_lex *lex)
{
	if (lex->token == T_EOF)
		parse_error_eoi();
	char c = '?'; // default unknown char
	if (lex->token == T_INT)
		c = (char)('0' + lex->value); // convert int value to char
	else if (lex->token == T_PLUS)
		c = '+';
	else if (lex->token == T_STAR)
		c = '*';
	else if (lex->token == T_LPAR)
		c = '(';
	else if (lex->token == T_RPAR)
		c = ')';
	printf("Unexpected token '%c'\n", c);
	exit(EXIT_FAILURE);
}

long long parse_factor(t_lex *lex) // factor := INT | '(' expr ')' --- F = N | ( E )
{
	if (lex->token == T_INT)
	{
		long long val = lex->value;
		lex_advance(lex);
		return val;
	}
	if (lex->token == T_LPAR)
	{
		lex_advance(lex); // consume '('
		long long val = parse_expr(lex); // parse sub-expression
		if (lex->token != T_RPAR) // expect ')'
			parse_error_here(lex); // error if not found
		lex_advance(lex); // consume ')'
		return val;
	}
	parse_error_here(lex); // error if neither INT nor '('
	return 0; // never reached
}

long long parse_term(t_lex *lex) // term := factor ( '*' factor )* --- T = F ( * F )*
{
	long long val = parse_factor(lex); // parse first factor
	while (lex->token == T_STAR) // while next token is '*'
	{
		lex_advance(lex); // consume '*'
		val *= parse_factor(lex); // parse next factor and multiply
	}
	return val; // return accumulated value
}

long long parse_expr(t_lex *lex) // expr := term ( '+' term )* --- E = T ( + T )*
{
	long long val = parse_term(lex); // parse first term
	while (lex->token == T_PLUS) // while next token is '+'
	{
		lex_advance(lex); // consume '+'
		val += parse_term(lex); // parse next term and add
	}
	return val; // return accumulated value
} 