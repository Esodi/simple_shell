#include "project.h"

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

	_tkn = strtok(_cmd, " ");
	while (_tkn != NULL)
	{
		_par[_i++] = _strdup(_tkn);
		_tkn = strtok(NULL, " ");
	}
	_par[_i] = NULL;

	return (_par);
}


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
		exit(1);
	}

	free(_par);
}


void searchAndExecute(char **_par, char **env, char *_cmd)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");
	char cmd_path[1024];

	while (token != NULL)
	{
		_strcpy(cmd_path, token);
		_strcat(cmd_path, "/");
		_strcat(cmd_path, _par[0]);
		if (access(cmd_path, X_OK) == 0)
		{
			_par[0] = _strdup(cmd_path);
			execute(_par, _par[0], env, _cmd);
		}
		token = strtok(NULL, ":");
	}
	fprintf(stderr, "Command not found: %s\n", _par[0]);
	exit(1);
}


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
		_child = fork();
		if (_child == -1)
		{
			perror("fork");
			exit(1);
		}
		if (_child == 0)
		{
			if (strchr(_par[0], '/') != NULL)
			{
				execute(_par, _par[0], env, _cmd);
			}
			else
			{
				searchAndExecute(_par, env, _cmd);
			}
			exit(0);
		}
		else
		{
			waitpid(_child, &status, 0);
		}
	}

	free(_par);
}

int main(void)
{
	char *_cmd = NULL;
	size_t _len = 0;
	ssize_t _r;

	while (1)
	{
		dollar();
		_r = getline(&_cmd, &_len, stdin);
		if (_r == -1)
		{
			perror("getline");
			break;
		}
		_cmd[_strlen(_cmd) - 1] = '\0';
		handleCommand(_cmd, environ);
	}


	free(_cmd);
	return (0);
}

