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
