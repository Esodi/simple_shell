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
