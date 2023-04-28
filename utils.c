#include "header.h"

/**
 * Auth: Emma Udeji
 * 		 Pericles Adjovi
 *
 * Description:
 * the extended functions for main.c
 */


/** parse_command - determines the type of the command
 * @command: command to be parsed
 *
 * Return: constant representing the type of the command
 * Description -
 * 		 EXTERNAL_COMMAND (1) represents commands like /bin/ls
 *		 INTERNAL_COMMAND (2) represents commands like exit, env
 *		 PATH_COMMAND (3) represents commands found in the PATH like ls
 *		 INVALID_COMMAND (-1) represents invalid commands
 */

int parse_command(char *command)
{
	char *internal_commands[] = {"env", "exit", NULL};
	char *path = NULL;
	int i;

	/* Check if command has a '/' to indicate external command */
	if (strchr(command, '/') != NULL)
	{
		return EXTERNAL_COMMAND;
	}

	/* Check if command is internal */
	for (i = 0; internal_commands[i] != NULL; i++)
	{
		if (_strcmp(command, internal_commands[i]) == 0)
		{
			return INTERNAL_COMMAND;
		}
	}

	/* Check if command is found in PATH */
	path = check_path(command);
	if (path != NULL)
	{
		free(path);
		return PATH_COMMAND;
	}

	/* If command is not recognized */
	return (INVALID_COMMAND);
}

/**
 * execute_command - executes a command based on it's type
 * @tokenized_command: tokenized form of the command (ls -l == {ls, -l, NULL})
 * @command_type: type of the command
 *
 * Return: void
 */
void execute_command(char **tokenized_command, int command_type)
{
void (*func)(char **command);
switch(command_type)
{
	case EXTERNAL_COMMAND:
		if (execve(tokenized_command[0], tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
		break;

	case PATH_COMMAND:
		if (execve(check_path(tokenized_command[0]), tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
		break;

	case INTERNAL_COMMAND:
		func = get_func(tokenized_command[0]);
		func(tokenized_command);
		break;

	case INVALID_COMMAND:
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tokenized_command[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
		break;

	default:
		break;
}
}

/**
 * check_path - checks if a command is found in the PATH
 * @command: command to be used
 *
 * Return: path where the command is found in, NULL if not found
 */
char *check_path(char *command)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = _getenv("PATH");
	int i;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
	_strcpy(path, path_cpy);
	path_array = tokenizer(path_cpy, ":");
	for (i = 0; path_array[i] != NULL; i++)
	{
		temp2 = _strcat(path_array[i], "/");
		temp = _strcat(temp2, command);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}
	free(path_cpy);
	free(path_array);
	return (NULL);
}

/**
 * get_func - retrieves a function based on the command given and a mapping
 * @command: string to check against the mapping
 *
 * Return: pointer to the proper function, or null on fail
 */
void (*get_func(char *command))(char **)
{
	int i;
	function_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	for (i = 0; i < 2; i++)
	{
		if (_strcmp(command, mapping[i].command_name) == 0)
			return (mapping[i].func);
	}
	return (NULL);
}

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: the value of the variable as a string
 */
char *_getenv(char *name)
{
	size_t name_len;
	char **env;
	
	if (name == NULL) {
		return NULL;
	}

	name_len = strlen(name);

	for (env = environ; *env; env++) {
		if (strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=') {
			return *env + name_len + 1;
		}
	}

	return (NULL);
}
