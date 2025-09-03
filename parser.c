/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:49:52 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/03 12:20:55 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"
#include "trace.h"
#include <stdlib.h>
#include <stdio.h>

long long parse_factor(t_lex *lex) // factor := INT | '(' expr ')' --- F = N | ( E )
{
	ENTER("factor");
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
		LEAVE("factor", val);
		return val;
	}
	parse_error_here(lex); // error if neither INT nor '('
	return 0; // never reached
}

long long parse_term(t_lex *lex) // term := factor ( '*' factor )* --- T = F ( * F )*
{
	ENTER("term");
	long long val = parse_factor(lex); // parse first factor
	while (lex->token == T_STAR) // while next token is '*'
	{
		lex_advance(lex); // consume '*'
		val *= parse_factor(lex); // parse next factor and multiply
	}
	LEAVE("term", val);
	return val; // return accumulated value
}

long long parse_expr(t_lex *lex) // expr := term ( '+' term )* --- E = T ( + T )*
{
	ENTER("expr");
	long long val = parse_term(lex); // parse first term
	while (lex->token == T_PLUS) // while next token is '+'
	{
		lex_advance(lex); // consume '+'
		val += parse_term(lex); // parse next term and add
	}
	LEAVE("expr", val);
	return val; // return accumulated value
} 