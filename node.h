#ifndef NODE_H
#define NODE_H

/**
 * node_type - an enum
 * @NODE_CMD: simple command
 * @NODE_V: variable name (or simply, a word)
 */
enum node_type {NODE_CMD, NODE_V};

/**
 * val_type - enum for val_type
 * @VAL_CHR: char
 * @VAL_STR: str (char pointer)
 */

enum val_type
{
	VAL_CHR,            /* char */
	VAL_STR,            /* str (char pointer) */
	VAL_SINT = 1
};

/**
 * symval_u - enum for symval
 * @chr: character.
 * @s: string
 */
union symval_u
{
	char               chr;
	char              *s;
};

/**
 * struct nodes - just a random struct
 * @node_type type: type of this node.
 * @val_type: type of this node's val field.
 * @val: value of this node.
 * @xchildren: number of child nodes.
 * @firstchild: first child node.
 * @nextsibling: child to be awaited for to be born.
 * @prevsibling: previouse child.
 */

struct nodes
{
	enum   node_type type;    /* type of this node */
	enum   val_type val_type; /* type of this node's val field */
	union  symval_u val;        /* value of this node */
	int    xchildren;            /* number of child nodes */
	struct nodes *firstchild; /* first child node */
	struct nodes *nextsibling, *prevsibling; /*
						  * if this is a child node, keep
						  * pointers to prev/next siblings
						  */
};

struct nodes *Newnode(enum node_type type);
void add_childnode(struct nodes *parent, struct nodes *child);
void free_nodetree(struct nodes *node);
void set_node_string(struct nodes *node, char *val);
#endif
