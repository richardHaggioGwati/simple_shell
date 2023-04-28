#include "header.h"


/**
 *_strtok_r - tokenizes a string
 *@string: string to be tokenized
 *@delim: delimiter to be used to tokenize the string
 *@save_ptr: pointer to be used to keep track of the next token
 *
 *Return: The next available token
 */
char *_strtok_r(char *string, char *delim, char **save_ptr)
{
    char *start, *end;
    if (string == NULL)
        string = *save_ptr;

    start = string + strspn(string, delim);
    if (*start == '\0') {
        *save_ptr = start;
        return (NULL);
    }

    end = start + strcspn(start, delim);
    if (*end != '\0') {
        *end = '\0';
        *save_ptr = end + 1;
    } else {
        *save_ptr = end;
    }
    return (start);
}

/**
 * _atoi - changes a string to an integer
 * @s: the string to be changed
 *
 * Return: the converted int
 */
int _atoi(char *s)
{
    int sign = 1, value = 0;
    const char *p = s;

    if (*p == '-') {
        sign = -1;
        p++;
    }
    while (*p >= '0' && *p <= '9') {
        value = value * 10 + (*p - '0');
        p++;
    }
    return sign * value;
}

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to the memory previously allocated with a call to malloc
 * @old_size: size of ptr
 * @new_size: size of the new memory to be allocated
 *
 * Return: pointer to the address of the new memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *new_ptr;

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    if (ptr == NULL) {
        new_ptr = malloc(new_size);
        return new_ptr;
    }
    if (new_size <= old_size) {
        return ptr;
    }
    new_ptr = malloc(new_size);
    if (new_ptr == NULL) {
        return NULL;
    }
    memcpy(new_ptr, ptr, old_size);
    free(ptr);
    return new_ptr;
}

/**
 * ctrl_c_handler - handles the signal raised by CTRL-C
 * @signum: signal number
 *
 * Return: void
 */
void ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
		print("\n($) ", STDIN_FILENO);
}

/**
 * remove_comment - removes/ignores everything after a '#' char
 * @input: input to be used
 *
 * Return: void
 */
void remove_comment(char *input)
{
    char *hash_pos;

	if (input == NULL || *input == '\0') {
        return;
    }
    hash_pos = strchr(input, '#');
    if (hash_pos != NULL) {
        *hash_pos = '\0';
    }
}
