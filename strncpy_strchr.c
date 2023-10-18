/**
 * *_strchr - a function that locates a character in a string
 *
 * @c: first occurrence of the character
 *
 * @s: input string
 *
 * Return: c if true, NULL if the character is not found
 */

char *_strchr(char *s, char c)
{
	int k;

	for (k = 0 ; s[k] >= '\0' ; k++)
	{
		if (s[k] == c)
		{
			return (s + k);
		}
	}

	return ('\0');
}

/**
 * *_strncpy - a function that copies a string.
 *
 *@n: input character
 *
 *@dest: input string
 *
 *@src: input string
 *
 * Return: character
 */

char *_strncpy(char *dest, char *src, int n)
{
	int m;

	for (m = 0 ; m < n && src[m] != '\0' ; m++)
	{
		dest[m] = src[m];
	}

	while (m < n)
	{
		dest[m] = '\0';
		m++;
	}

	return (dest);
}
