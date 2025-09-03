/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:49:57 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/03 11:49:58 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VBC_H
# define VBC_H

#include <stddef.h>

typedef enum e_tok 
{
	T_INT, T_PLUS, T_STAR, T_LPAR, T_RPAR, T_EOF
}	t_tok;

typedef struct s_lex 
{
	const char	*input;
	size_t		pos; // current position in input
	t_tok		token; // current token kind
	int			value; // valid if token == T_INT
} t_lex;

/* lexer */
void lex_init(t_lex *lex, const char *input); // initialize lexer
void lex_advance(t_lex *lex); // advance to next token (set lex->token and lex->value for T_INT)

/* parser */
long long parse_expr(t_lex *lex); // parse an expression and return its value
long long parse_term(t_lex *lex); // parse a term and return its value
long long parse_factor(t_lex *lex); // parse a factor and return its value

/* errors */
void parse_error_char(char c); // pritnd "Unexpected character: c" and exits
void parse_error_eoi(void); // pritns "Unexpected end of input" and exits
void parse_error_here(t_lex *lex); // pritns "Unexpected token 'c'" and exits, where c is current token or '?' if unknown

/* utils */
int ft_isdigit(unsigned char c); // returns 1 if c is a digit, 0 otherwise

# endif // VBC_H