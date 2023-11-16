#include "project.h"

/**
 * customErrorPrint - Prints a custom error message to stderr.
 * @command: The command that was not found.
 * Description: Constructs and prints a custom error message to stderr.
 */
void customErrorPrint(char *command)
{
	char error_msg[1024] = "./hsh: 1: ";

	_strcat(error_msg, command);
	_strcat(error_msg, ": not found\n");
	write(STDERR_FILENO, error_msg, _strlen(error_msg));
	exit(127);
}

/**
 * freeTokenizedInput - Frees memory allocated for an array of strings.
 * @_par: Array of strings to be deallocated.
 * @size: Number of elements in the array.
 */
void freeTokenizedInput(char **_par, int size)
{
	int i;

	for (i = 0; i < size; ++i)
	{
		free(_par[i]);
	}
	free(_par);
}

/**
 * handleComments - Handles comments in the input command string.
 * @_cmd: The input command string to process.
 */
void handleComments(char *_cmd)
{
	int i;

	for (i = 0; _cmd[i] != '\0'; ++i)
	{
		if (_cmd[i] == '#')
		{
			while (_cmd[i] != '\0' && _cmd[i] != '\n')
			{
				_cmd[i++] = '\n';
			}
			_cmd[i] = '\0';
			break;
		}
	}
}

