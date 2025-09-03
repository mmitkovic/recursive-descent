/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:49:38 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/03 11:54:56 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
	parse_error_char(c);
}

void parse_error_char(char c) 
{
	printf("Unexpected token: %c\n", c);
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
