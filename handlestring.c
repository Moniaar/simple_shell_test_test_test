#include "solomon.h"

/**
 * _strcomp - performs comparison of two strangs.
 *
 * @st1: the first strang
 * @st2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, 0 if s1 == s2
 */
int _strcomp(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * _strcpy - a function that copies the string pointed to by src
 * including the terminating null byte (\0), to the buffer pointed to by dest
 *
 *@src: input string of character
 *
 *@dest: input string of character
 *
 * Return: character (Success)
 */

char *_strcpy(char *dest, char *src)
{
	int y = -1;

	while (src[y] != '\0')
	{
		y++;
		dest[y] = src[y];
	}

	return (dest);
}

/**
 * *_memset - a function that fills memory with a constant byte.
 *
 * @n: bytes of the memory area
 *
 * @s: input pointer
 *
 * @b: constant byte
 *
 * Return: a pointer to the memory area s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int k;

	k = 0;

	for (k = 0 ; n > 0 ; k++)
	{
		s[k] = b;
		n--;
	}
	return (s);
}

/**
 * _strlen - A function to return the length of a string
 *
 * @s: input character
 *
 * Return: int length of a string
*/

int _strlen(char *s)
{
	int cnu;

	for (cnu = 0 ; *s != '\0' ; s++)
	{
		++cnu;
	}
	return (cnu);
}

/**
 * *_strcat -  a function that concatenates two strings
 *
 * @src: input string
 *
 * @dest: input string
 *
 * Return: a pointer to the resulting string dest
 */

char *_strcat(char *dest, char *src)
{
	int m, i;

	m = 0;

	while (dest[m])
		m++;

	for (i = 0 ; src[i] ; i++)
	{
		dest[m++] = src[i];

	}

	return (dest);
}

