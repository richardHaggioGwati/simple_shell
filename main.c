#include "header.h"

/**
  * _isatty - verif if terminal
  */
void _isatty(void)
{
if (isatty(STDIN_FILENO))
{
_puts("#cisfun$ ");
}
}

/**
* HANDLE_END_OF_FILE - handles the End of File
* @len: return value of getline function
* @buff: buffer
 */
void HANDLE_END_OF_FILE(int len, char *buff)
{
(void)buff;

if (len == -1)
{
if (isatty(STDIN_FILENO))
{
_puts("\n");
free(buff);
}
exit(0);
}
}

/**
 * sign_handler - checks if Ctrl C is pressed
 * @sig_num: int
 */
void sign_handler(int sig_num)
{
if (sig_num == SIGINT)
{
_puts("\n#cisfun$ ");
}
}

/**
 * main - Shell
 * Return: 0 on success
 */
int main(void)
{
ssize_t line_len = 0;
char *line_buf = NULL, *env_value, *pathname, **args;
size_t buf_size = 0;
list_path *path_list = '\0';
void (*cmd_func)(char **);

signal(SIGINT, sign_handler);
while (line_len != EOF)
{
_isatty();
line_len = getline(&line_buf, &buf_size, stdin);
HANDLE_END_OF_FILE(line_len, line_buf);
args = split_string(line_buf, " \n");
if (!args || !args[0])
{
execute(args);
}
else
{
env_value = _getenv("PATH");
path_list = linkpath(env_value);
pathname = _which(args[0], path_list);
cmd_func = checkbuild(args);
if (cmd_func)
{
free(line_buf);
cmd_func(args);
}
else if (!pathname)
{
execute(args);
}
else if (pathname)
{
free(args[0]);
args[0] = pathname;
execute(args);
}
}
}
free_list(path_list);
freearv(args);
free(line_buf);
return (0);
}
