#ifndef SCANNER_H
#define SCANNER_H
#include "source.h"

/**
 * struct tokens - structure for tokenization.
 * @s: just a random variable.
 * @len_of_text: length of token text
 * @token_text: token text.
 */

struct tokens
{
	struct source *s;

	int len_of_text;
	char *token_text;
};

/* the special EOF token, which indicates the end of input */
extern struct tokens end_of_tok;

struct tokens *tokenizing(struct source *s);
void token_freed(struct tokens *t);
#endif
