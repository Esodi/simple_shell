#include "project.h"

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

void dollar(void)
{
	show(" # ");
}

void exitShell(char *_cmd, char **_par)
{
	free(_cmd);
	free(_par);

	exit(0);
}

void printEnvironment(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		show(*env);
		env++;
	}
}
