#include "project.h"

int show(char *_x)
{
	return (write(STDOUT_FILENO, _x, strlen(_x)));
}
