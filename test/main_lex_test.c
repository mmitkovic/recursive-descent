/* main_lex_test.c */
#include "vbc.h"
#include <stdio.h>

static const char* name(t_tok t){
    if (t==T_INT) return "INT";
    if (t==T_PLUS) return "PLUS";
    if (t==T_STAR) return "STAR";
    if (t==T_LPAR) return "LPAR";
    if (t==T_RPAR) return "RPAR";
    if (t==T_EOF) return "END";
    return "?";
}

int main(void)
{
    t_lex lx;
	lex_init(&lx, "3+(4*5)+6");
    lex_advance(&lx);
    while (lx.token != T_EOF) {
        if (lx.token == T_INT) 
			printf("%s(%d)\n", name(lx.token), lx.value);
        else
		    printf("%s\n", name(lx.token));
        lex_advance(&lx);
    }
    printf("END\n");
}
