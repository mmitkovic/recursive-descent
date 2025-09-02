#include "vbc.h"
#include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: %s \"expression\"\n", av[0]);
		return 1;
	}
	t_lex lex;
	lex_init(&lex, av[1]);
	lex_advance(&lex); // initialize first token
	long long result = parse_expr(&lex); // parse the expression
	if (lex.token != T_EOF) // if not at end of input, error
		parse_error_char(lex.input[lex.pos]); // unexpected character
	printf("%lld\n", result); // print the result
	return 0;
}