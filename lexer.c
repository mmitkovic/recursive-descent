#include "vbc.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void parse_error_char(char c) 
{
	printf("Unexpected character: %c\n", c);
	exit(EXIT_FAILURE);
}

void parse_error_eoi()
{
	printf("Unexpected end of input\n");
	exit(EXIT_FAILURE);
}

void lex_init(t_lex *lex, const char *input)
{
	lex->input = input;
	lex->pos = 0;
	lex->token = T_EOF;
	lex->value = 0;
}
void lex_advance(t_lex *lex)
{
	const char *input = lex->input; // local copy for convenience
	char c = input[lex->pos]; // current character;

	if (c == '\0')
	{
		lex->token = T_EOF;
		return ;
	}
	if (ft_isdigit((unsigned char)c))
	{
		lex->token = T_INT;
		lex->value = c - '0';
		lex->pos++;
		return ;
	}
	if (c == '+')
	{
		lex->token = T_PLUS;
		lex->pos++;
		return ;
	}
	else if (c == '*')
	{
		lex->token = T_STAR;
		lex->pos++;
		return ;
	}
	else if (c == '(')
	{
		lex->token = T_LPAR;
		lex->pos++;
		return ;
	}
	else if (c == ')')
	{
		lex->token = T_RPAR;
		lex->pos++;
		return ;
	}
	parse_error_char(c);
}
