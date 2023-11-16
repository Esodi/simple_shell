#include "project.h"

/**
 * bufferAndReadInput -  Buffer chained commands and read input from stdin
 * This function handles the buffering of chained commands, reading input
 * from the standard input, and processing it accordingly. It takes care of
 * handling command chaining, removing trailing newlines, and updating the
 * command history
 * @info: Parameter struct holding relevant information
 * @buf: Address of the buffer
 * @len: Address of the length variable
 * Return: Bytes read
 */

ssize_t bufferAndReadInput(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, blockCtrlC);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = getNextLine(info, buf, &len_p);
#endif
		if (r > 0)
		{

			if ((*buf)[r - 1] == '\n')
			{

				(*buf)[r - 1] = '\0';
				r--;
			}

			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			if (_strchr(*buf, ';'))
			{

				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * getUserInput -  Get user input excluding the newline character
 * This function retrieves input from the user, manages command chaining,
 * and returns the length of the current command
 *
 * @info: Parameter struct holding relevant information
 * Return: Bytes read
 */

ssize_t getUserInput(info_t *info)
{
	static char *buf;
	static size_t a, b, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = bufferAndReadInput(info, &buf, &len);

	if (r == -1)
		return (-1);

	if (len)
	{
		b = a;
		p = buf + a;

		check_chain(info, buf, &b, a, len);
		while (b < len)
		{
			if (is_chain(info, buf, &b))
				break;
			b++;
		}

		a = b + 1;

		if (a >= len)
		{
			a = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}

/**
 * readBuffer -  Read a buffer of a specified size
 * This function reads a buffer of a specified size from a given information
 * struct.
 *
 * @info: Parameter struct holding relevant information
 * @buf: Buffer to read into
 * @i: Size of the buffer
 * Return: Bytes read
 */

ssize_t readBuffer(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * getNextLine - Get the next line of input from STDIN
 * This function reads the next line of input from the standard input (STDIN)
 * stream
 * @info: Parameter struct holding relevant information
 * @ptr: Address of the pointer to the buffer (preallocated or NULL)
 * @length: Size of the preallocated buffer if not NULL
 * Return: Bytes read
 */

int getNextLine(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, len;
	size_t d;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
	{
		s = *length;
	}
	if (a == len)
	{
		a = len = 0;
	}
	r = readBuffer(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	d = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + d : d + 1);

	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + a, d - a);
	else
		_strncpy(new_p, buf + a, d - a + 1);

	s += d - a;
	a = d;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * blockCtrlC - Handle the SIGINT signal, blocking the Ctrl-C action
 * This function handles the SIGINT signal, preventing
 * the default Ctrl-C behavior
 * @sig_num: The signal number
 */

void blockCtrlC(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
