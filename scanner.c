#include "solomon.h"
#include "scanner.h"
#include "source.h"

struct tokens len_of_text;
/* special token to indicate end of input */
struct tokens end_of_tok = len_of_text = 0;

/**
 * addto_buffer - a function to store values inside of a buffer
 *
 * @ch: the character to  be stored in the buffer
 *
 * Return: Nothing
 */

void addto_buffer(char ch)
{
	char *temp, *t_buffer;
	int t_bufsize, t_bufindex;

	t_buffer[t_bufindex++] = ch;

	if (t_bufindex >= t_bufsize)
	{
		temp = realloc(t_buffer, t_bufsize * 2);

		if (!temp)
		{
			errno = ENOMEM;
			return;
		}

		t_buffer = temp;
		t_bufsize *= 2;
	}
}

/**
 * make_token - a function to create the tokens
 *
 * @st: the string of characters that represents the token
 *
 * Return: the tokens that was found from type struct token
 */

struct tokens *make_token(char *st)
{
	struct tokens end_of_tok;
	char *nst;
	struct tokens *tk;
	end_of_tok.len_of_text = 0;
	tk = malloc(sizeof(struct tokens));

	if (!tk)
	{
		return (NULL);
	}

	memset(tk, 0, sizeof(struct tokens));
	tk->len_of_text = strlen(st);

	nst = malloc(tk->len_of_text + 1);

	if (!nst)
	{
		free(tk);
		return (NULL);
	}

	strcpy(nst, st);
	tk->token_text = nst;

	return (tk);
}

/**
 * token_freed - a function to free the memory allocated for a token
 *
 * @t: the value of the freed token
 *
 * Return: Nothing
 */

void token_freed(struct tokens *t)
{
	if (t->token_text)
	{
		free(t->token_text);
	}
	free(t);
}

/**
 * tokenizing - The function responsiable about tokenizing
 * the entred commands
 *
 * @s: the tokenizing parameter
 *
 * Return: the tokenzied strings from struct type tokens
 */

struct tokens *tokenizing(struct source *s)
{
	int loopend;
	struct tokens *tk;
	int t_bufsize, t_bufindex;
	char n, *t_buffer;
	t_buffer[0] = '\0';

	loopend = 0;

	t_bufindex = 0;

	if (!s || !s->bu || !s->bufsize)
	{
		errno = ENODATA;
		return (&end_of_tok);
	}

	if (t_buffer == NULL)
	{
		t_bufsize = 1024;
		t_buffer = malloc(t_bufsize);
		if (t_buffer == NULL)
		{
			errno = ENOMEM;
			return (&end_of_tok);
		}
	}

	n = Nextchar(s);

	if (n == CHARERROR || n == EOF)
	{
		return (&end_of_tok);
	}

	do {
		switch (n)
		{
			case ' ':
			case '\t':
				if (t_bufindex > 0)
				{
					loopend = 1;
				}
				break;

			case '\n':
				if (t_bufindex > 0)
				{
					return_last_char(s);
				}
				else
				{
					addto_buffer(n);
				}
				loopend = 1;
				break;

			default:
				addto_buffer(n);
				break;
		}

		if (loopend)
		{
			break;
		}

	} while ((n = Nextchar(s)) != EOF);

	if (t_bufindex == 0)
	{
		return (&end_of_tok);
	}

	if (t_bufindex >= t_bufsize)
	{
		t_bufindex--;
	}
	t_buffer[t_bufindex] = '\0';

	tk = make_token(t_buffer);

	if (!tk)
	{
		fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
		return (&end_of_tok);
	}

	tk->s = s;
	return (tk);
}

