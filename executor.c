#include "solomon.h"
#include "node.h"
#include "executor.h"

/** 
 * search_path - a function to search the path of your shell
 *
 * @file: thee name of the files inside the path
 *
 * Return: the path name
 */

char *search_path(char *file)
{
	char *PATH = getenv("PATH");
	char *p = PATH;
	int plen, alen;
	char *path;
	char *p2;
	struct stat st;

	plen = p2 - p;
	alen = strlen(file);
	path = (char *)malloc(plen + 1 + alen + 1);
	if (path == NULL)
		return (NULL);

	while (p && *p)
	{
		p2 = p;

		while (*p2 && *p2 != ':')
		{
			p2++;
		}

		if (!plen)
		{
			plen = 1;
		}

		strncpy(path, p, p2 - p);
		path[p2 - p] = '\0';

		if (p2[-1] != '/')
		{
			strcat(path, "/");
		}

		strcat(path, file);

		if (stat(path, &st) == 0)
		{
			if (!S_ISREG(st.st_mode))
			{
				errno = ENOENT;
				p = p2;
				if (*p2 == ':')
				{
					p++;
				}
				continue;
			}

			p = malloc(strlen(path) + 1);
			if (!p)
			{
				return NULL;
			}

			strcpy(p, path);
			return (p);
		}
		else
		{
			p = p2;
			if (*p2 == ':')
			{
				p++;
			}
		}
	}
	free(path);
	errno = ENOENT;
	return (NULL);
}

/**
 * do_exec_cmd - a function that exectues simple commands
 *
 * @argc: the count for arguments
 *
 * @argv: argument vector
 *
 * Return: integer number of exectued commands
 */

int do_exec_cmd(int argc, char **argv)
{
	char *path;
	if (strchr(argv[0], '/'))
	{
		execv(argv[0], argv);
	}
	else
	{
		path = search_path(argv[0]);
		if (!path)
		{
			return (0);
		}
		execv(path, argv);
		free(path);
	}
	if (argc < 0)
		return (0);
	return (0);
}

/**
 * free_argv - a function to free the arguments after being
 * called as an executable form
 *
 * @argc: count of arguments
 *
 * @argv: vector of arguments
 *
 * Return: Nothing
 */

static inline void free_argv(int argc, char **argv)
{
	if (!argc)
	{
		return;
	}

	while (argc--)
	{
		free(argv[argc]);
	}
}

/**
 * do_simple_command - a function to handle the simple commands
 *
 * @node: a struct type from nodes
 *
 * Return: number of exectued commands
 */

int do_simple_command(struct nodes *node)
{
	pid_t child_pid;
	struct nodes *child;
	int argc, status;
	long int max_args;
	char *s;
	char *argv[max_args + 1];
	status = 0;

	if (!node)
	{
		return (0);
	}

	child = node->firstchild;
	if (!child)
	{
		return (0);
	}

	argc = 0;
	max_args = 255;

	while (child)
	{
		s = child->val.s;
		argv[argc] = malloc(strlen(s)+1);

		if (!argv[argc])
		{
			free_argv(argc, argv);
			return (0);
		}

		strcpy(argv[argc], s);
		if (++argc >= max_args)
		{
			break;
		}
		child = child->nextsibling;
	}
	argv[argc] = NULL;

	child_pid = 0;
	if ((child_pid = fork()) == 0)
	{
		do_exec_cmd(argc, argv);
		fprintf(stderr, "error: failed to execute command: %s\n", strerror(errno));
		if (errno == ENOEXEC)
		{
			exit(126);
		}
		else if (errno == ENOENT)
		{
			exit(127);
		}
		else
		{
			exit(EXIT_FAILURE);
		}
	}
	else if (child_pid < 0)
	{
		fprintf(stderr, "error: failed to fork command: %s\n", strerror(errno));
		return (0);
	}

	waitpid(child_pid, &status, 0);
	free_argv(argc, argv);

	return (1);
}
