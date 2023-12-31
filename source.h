#ifndef SOURCE_H
#define SOURCE_H

#define EOF (-1)
#define CHARERROR (0)

#define INIT_SRC_POS    (-2)

/**
 * struct source - Just a gaddamn struct.
 * @bu: the input text
 * @busize: size of the input text
 * @cur_pos: absolute char position in source
 */

struct source
{
	char *bu;
	long bufsize;
	long  cur_pos;
};

char Nextchar(struct source *s);
void return_last_char(struct source *s);
char char_sneekpeek(struct source *s);
void skip_whitespace(struct source *s);

#endif
