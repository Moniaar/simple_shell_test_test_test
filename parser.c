#include "solomon.h"
#include "node.h"
#include "parser.h"
#include "scanner.h"
#include "source.h"

/**
 * parse_simple_cmd - a function to parse simple commands
 *
 * @tk: a struct type from tokens user-defined structre
 *
 * Return: struct nodes type to point to the commands
 */

struct nodes *parse_simple_cmd(struct tokens *tk)
{
	struct nodes *command, *Word;
	struct source *s;

	if (!tk)
	{
		return (NULL);
	}

	command = Newnode(NODE_CMD);

	if (!command)
	{
		token_freed(tk);
		return (NULL);
	}

	s = tk->s;

	do {
		if (tk->token_text[0] == '\n')
		{
			token_freed(tk);
			break;
		}

		Word = Newnode(NODE_V);

		if (!Word)
		{
			free_nodetree(command);
			token_freed(tk);
			return (NULL);
		}
		set_node_string(Word, tk->token_text);
		add_childnode(command, Word);

		token_freed(tk);

	} while ((tk = tokenizing(s)) != &end_of_tok);
	return (command);
}

