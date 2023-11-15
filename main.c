#include "project.h"

/**
 * tokenizeInput - Tokenizes the input command string
 * @_cmd: The input command string to tokenize
 * @_l: Pointer to store the number of words in the command
 *
 * Return: An array of strings containing the tokens
 */

char **tokenizeInput(char *_cmd, int *_l)
{
	int _i = 0;
	char **_par = NULL;
	char *_tkn = NULL;

	*_l = wordsno(_cmd, ' ');
	_par = (char **)malloc(sizeof(char *) * (*_l + 1));
	if (_par == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	_tkn = _strtok(_cmd, DELIM);
	while (_tkn != NULL)
	{
		_par[_i++] = _strdup(_tkn);
		_tkn = _strtok(NULL, DELIM);
	}
	_par[_i] = NULL;

	return (_par);
}

/**
 * execute - Executes a command with the given parameters
 * @_par: Array of strings containing the command and its arguments
 * @command: The command to execute
 * @env: Array of strings containing the environment variables
 * @_cmd: The original input command string
 */

void execute(char **_par, char *command, char **env, char *_cmd)
{
	if (_par == NULL)
	{
		free(_cmd);
		return;
	}

	if (execve(command, _par, env) == -1)
	{
		perror("execve");
		free(_par);
		exit(127);
	}

	free(_par);
}

/**
 * searchAndExecute - Searches for and executes a command in the PATH
 * @_par: Array of strings containing the command and its arguments
 * @env: Array of strings containing the environment variables
 * @_cmd: The original input command string
 */

void searchAndExecute(char **_par, char **env, char *_cmd)
{
	char *path = getenv("PATH");
	char *token = _strtok(path, ":");
	char cmd_path[1024];
	int found = 0;

	while (token != NULL)
	{
		_strcpy(cmd_path, token);
		_strcat(cmd_path, "/");
		_strcat(cmd_path, _par[0]);
		if (access(cmd_path, X_OK) == 0)
		{
			_par[0] = _strdup(cmd_path);
			execute(_par, _par[0], env, _cmd);
			found = 1;
			exit(127);
		}
		else
		    exit(127);
		token = _strtok(NULL, ":");
	}
	if (!found)
	{
		customErrorPrint(_par[0]);
		exit(127);
	}
}

/**
 * handleCommand - Handles the execution of a command
 * @_cmd: The input command string
 * @env: Array of strings containing the environment variables
 */

void handleCommand(char *_cmd, char **env)
{
	int  _l, status;
	char **_par = tokenizeInput(_cmd, &_l);
	pid_t _child;

	if (_par == NULL)
	{
		free(_cmd);
		return;
	}

	if (_par[0] != NULL)
	{
		if (_strcmp(_par[0], "exit") == 0)
			exitShell(_cmd, _par);
		else if (_strcmp(_par[0], "env") == 0)
			printEnvironment(env);
		else if (_strcmp(_par[0], "cd") == 0)
			changeDirectory(_par);
		_child = fork();
		if (_child == -1)
		{
			perror("fork");
			exit(127);
		}
		if (_child == 0)
		{
			if (_strchr(_par[0], '/') != NULL)
			{
				execute(_par, _par[0], env, _cmd);
			}
			else
			{
				searchAndExecute(_par, env, _cmd);
			}
			exit(127);
		}
		else
			waitpid(_child, &status, 0);
	}
	free(_par);
}

/**
 * main - Entry point for the shell program.
 * @argc: Number of arguments passed to the program.
 * @argv: Array of strings containing the arguments passed to the program.
 * @env: Array of strings containing the environment variables.
 * Return: Exit status of the shell program.
 */
int main(int argc, char *argv[], char **env)
{
	char *_cmd = NULL;
	size_t _len = 0;
	ssize_t _r;

	(void)argc;
	(void)argv;

	while (1)
	{
		dollar();
		_r = getline(&_cmd, &_len, stdin);
		if (_r == -1)
		{
			break;
		}
		_cmd[_strlen(_cmd) - 1] = '\0';
		handleCommand(_cmd, env);
	}


	free(_cmd);
	return (0);
}
