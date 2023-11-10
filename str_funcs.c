#include "project.h"

/**
 * _strlen - length of a string
 * @_s: the stringlength check
 * Return: length of string
 */

int _strlen(char *_s)
{
	int a = 0;

	if (_s == NULL)
		return (0);

	while (*_s++)
	{
		a++;
	}

	return (a);
}

/**
 * _strcmp - comparison of two strings
 * @_s1: string
 * @_s2: string
 * Return: - COMPARISON
 */

int _strcmp(char *_s1, char *_s2)
{
	while (*_s1 && *_s2)
	{
		if (*_s1 != *_s2)
			return (*_s1 - *_s2);
		_s1++;
		_s2++;
	}
	if (*_s1 == *_s2)
		return (0);
	else
		return (*_s1 < *_s2 ? -1 : 1);
}

/**
 * _strcat - concatenates two strings
 * @_dest: destination
 * @_src: source
 * Return: the to dest
 */

char *_strcat(char *_dest, char *_src)
{
	char *ret = _dest;

	while (*_dest)
		_dest++;
	while (*_src)
		*_dest++ = *_src++;
	*_dest = *_src;
	return (ret);
}

/**
 * _strcpy - copies a string
 * @_dest: destination
 * @_src: source
 * Return: pointer to destination
 */

char *_strcpy(char *_dest, char *_src)
{
	int a = 0;

	if (_dest == _src || _src == 0)
		return (_dest);
	while (_src[a])
	{
		_dest[a] = _src[a];
		a++;
	}
	_dest[a] = 0;

	return (_dest);
}

/**
 * _strdup - duplicates a string
 * @_tr: string to duplicate
 * Return: the pointer to the duplicated str
 */

char *_strdup(const char *_tr)
{
	int l = 0;
	char *ret;

	if (_tr == NULL)
		return (NULL);
	while (*_tr++)
		l++;
	ret = malloc(sizeof(char) * (l + 1));
	if (!ret)
		return (NULL);
	for (l++; l--;)
		ret[l] = *--_tr;
	return (ret);
}
