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
	show("");
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
 * changeDirectory - Change the current working directory.
 * @_par: The array of strings containing the command and arguments.
 */
void changeDirectory(char **_par)
{
	char *new_dir;
	char *oldpwd;
	char cwd[1024];

	if (_par[1] == NULL || strcmp(_par[1], "~") == 0)
		new_dir = getenv("HOME");
	else if (strcmp(_par[1], "-") == 0)
	{
		oldpwd = getenv("OLDPWD");
		if (oldpwd != NULL)
			new_dir = strdup(oldpwd);
		else
			return;
	}
	else
		new_dir = _par[1];
	if (chdir(new_dir) != 0)
	{
		perror("cd");
		return;
	}

	if (setenv("OLDPWD", getenv("PWD"), 1) != 0)
	{
		perror("setenv");
		return;
	}

	if (setenv("PWD", new_dir, 1) != 0)
	{
		perror("setenv");
		return;
	}
	if (_par[1] != NULL && strcmp(_par[1], "-") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			return;
	show(cwd);
	show("\n");
	}
}
