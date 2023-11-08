#include "shell.h"

/**
 * _strlen - this function returns the length of a string
 * @s: the string which length to check
 *
 * Return:the  integer length of string
 */

int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * _strcmp - this performs descriptive comparison of two strings
 * @s1: initial string
 * @s2: second string
 *
 * Return: - if s1 < s2, + if s1 > s2, 0 if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - this checks if the needle starts with haystack
 * @haystack: the string to search for
 * @needle: substring to find
 *
 * Return: the addr of next character of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - this function concatenates two strings
 * @dest: destination buffer
 * @src: source buffer
 *
 * Return: the pointer to destination buffer
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
