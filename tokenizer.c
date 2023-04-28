#include "header.h"

/**
 * tokenizer - tokenizes input and stores it into an array
 *@input_string: input to be parsed
 *@delim: delimiter to be used, needs to be one character string
 *
 *Return: array of tokens
 */

char **tokenizer(char *input_string, char *delim)
{
    char **tokens = NULL;
    char *token = NULL;
    char *tmp = input_string;
    int num_tokens = 0;

    while ((token = strsep(&tmp, delim)) != NULL)
    {
        if (*token != '\0')
        {
            tokens = _realloc(tokens, sizeof(*tokens) * num_tokens,
                              sizeof(*tokens) * (num_tokens + 1));
            tokens[num_tokens++] = token;
        }
    }

    tokens = _realloc(tokens, sizeof(*tokens) * num_tokens,
                      sizeof(*tokens) * (num_tokens + 1));
    tokens[num_tokens] = NULL;

    return (tokens);
}

/**
 *print - prints a string to stdout
 *@string: string to be printed
 *@stream: stream to print out to
 *
 *Return: void, return nothing
 */
void print(char *string, int stream)
{
	int i = 0;

	for (i = 0; string[i] != '\0'; i++)
		write(stream, &string[i], 1);
}

/**
 *remove_newline - removes new line from a string
 *@str: string to be used
 *
 *
 *Return: void
 */

void remove_newline(char *str)
{
    char *ptr = strchr(str, '\n');
    if (ptr != NULL) {
        *ptr = '\0';
    }
}

/**
 *_strcpy - copies a string to another buffer
 *@source: source to copy from
 *@dest: destination to copy to
 *
 * Return: void
 */

void _strcpy(char *source, char *dest)
{
	int i = 0;

	for (; source[i] != '\0'; i++)
	{
		dest[i] = source[i];
	}
	dest[i] = '\0';
}

/**
 *_strlen - counts string length
 *@string: string to be counted
 *
 * Return: length of the string
 */

int _strlen(char *string)
{
    const char *end = string;

    if (string == NULL)
        return 0;
    while (*end) {
        end++;
    }
    return (size_t)(end - string);
}
