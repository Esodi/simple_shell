#include "project.h"

/**
 * _strchr - locates a character in a string
 * @_s: the string to search
 * @_c: the character to locate
 * Return: a pointer to the first occurrence of @_c in @_s
 * or NULL if not found
 */

char *_strchr(char *_s, int _c)
{
	while (*_s != (char)_c)
	{
		if (*_s == '\0')
			return (NULL);
		_s++;
	}
	return (_s);
}

/**
 * _strspn - calculates the length of the initial segment of str.
 * @_str: The string to be searched.
 * @_accept: The string containing the characters to match.
 *
 * Return: The length of the initial segment of str.
 */
size_t _strspn(char *_str, char *_accept)
{
	size_t _count = 0;

	while (_str[_count] != '\0' && _strchr(_accept, _str[_count]) != NULL)
	{
		_count++;
	}

	return (_count);
}

/**
 * _strcspn - calculates the length of the initial segment of str.
 * @_str: The string to be searched.
 * @_reject: The string containing the characters to avoid.
 *
 * Return: The length of the initial segment of str.
 */
size_t _strcspn(char *_str, char *_reject)
{
	size_t _count = 0;

	while (_str[_count] != '\0' && _strchr(_reject, _str[_count]) == NULL)
	{
		_count++;
	}

	return (_count);
}

/**
 * _strtok - extracts tokens from strings.
 * @_str: The string to be tokenized.
 * @_delimiters: The set of characters used as delimiters.
 *
 * Return: A pointer to the next token found in the string.
 */
char *_strtok(char *_str, char *_delimiters)
{
	static char *_token;
	char *_start;

	if (_str != NULL)
	{
		_token = _str;
	}

	if (_token == NULL)
	{
		return (NULL);
	}

	_start = _token + _strspn(_token, _delimiters);

	if (*_start == '\0')
	{
		_token = NULL;
		return (NULL);
	}

	_token = _start + _strcspn(_start, _delimiters);

	if (*_token != '\0')
	{
		*_token = '\0';
		_token++;
	}
	else
	{
		_token = NULL;
	}

	return (_start);
}
