/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:49:45 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/03 11:49:46 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"
#include <stdio.h>

int main(int ac, char **av)
{
	long long result;
	t_lex lex;

	if (ac != 2)
	{
		printf("Usage: %s \"expression\"\n", av[0]);
		return 1;
	}
	lex_init(&lex, av[1]); // initialize lexer
	lex_advance(&lex); // initialize first token
	result = parse_expr(&lex); // parse the expression
	if (lex.token != T_EOF) // if not at end of input, error
		parse_error_here(&lex); // unexpected character
	printf("%lld\n", result); // print the result
	return 0;
}
