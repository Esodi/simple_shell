#include "project.h"

/**
 * wordsno - Counts the number of occurrences of a character in a string
 * @_cmd: The input string to count occurrences in
 * @_c: The character to count occurrences of
 *
 * Return: The number of occurrences of @_c in @_cmd
 */

int wordsno(char *_cmd, char _c)
{
	int _j = 0, _i = 0;

	while (_cmd[_j] != '\0')
	{
		if (_cmd[_j] == _c)
			_i++;
		_j++;
	}
	_i++;

	return (_i);
}

/**
 * dollar - Prints the shell prompt symbol '#'
 */

void dollar(void)
{
	show(" # ");
}

/**
 * exitShell - Frees memory and exits the shell
 * @_cmd: The input command string
 * @_par: Array of strings containing the command and its arguments
 */

void exitShell(char *_cmd, char **_par)
{
	free(_cmd);
	free(_par);

	exit(0);
}

/**
 * printEnvironment - Prints the environment variables.
 */

void printEnvironment(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		show(*env);
		env++;
	}
}


/**
 * _getline - reads a line from the specified file descriptor.
 * @line: A pointer to the buffer where the line will be stored.
 * @size: The size of the buffer.
 * @fd: The file descriptor to read from (e.g., STDIN_FILENO).
 *
 * Return: The number of characters read (including the newline character).
 */
