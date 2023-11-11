#include "project.h"

/**
 * show - Displays a string to the standard output
 * @_x: The string to be displayed
 *
 * Returns: The number of characters printed
 */
int show(char *_x)
{
	return (write(STDOUT_FILENO, _x, _strlen(_x)));
}
