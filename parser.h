#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"    /* struct token_s */
#include "source.h"     /* struct source_s */
struct nodes *parse_simple_cmd(struct tokens *tk);
#endif
