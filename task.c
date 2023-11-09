#include "fk.h"

/**
 * fk_strncpy - Function that copies a string into another
 * @fk_dest: destination of the string
 * @fk_src: string to copy
 * @fk_n: length of the string
 * Return: fk_dest
 */
char *fk_strncpyconst(char *fk_dest, char *fk_src, int fk_n)
{
    int i;

    for (i = 0; i < fk_n && fk_src[i] != '\0'; i++)
        fk_dest[i] = fk_src[i];

    for (; i < fk_n; i++)
    {
        fk_dest[i] = '\0';
    }

    return fk_dest;
}

/**
 * fk_strncpyconst - Function that copies a constant string into another
 * @fk_dest: destination of the string
 * @fk_src: string to copy
 * @fk_n: length of the string
 * Return: fk_dest
 */
char *fk_strncpy(char *fk_dest, char *fk_src, int fk_n)
{
    int i;

    for (i = 0; i < fk_n && fk_src[i] != '\0'; i++)
        fk_dest[i] = fk_src[i];

    for (; i < fk_n; i++)
    {
        fk_dest[i] = '\0';
    }

    return fk_dest;
}
/**
 * fk_strlen_const - Function to find the length of a constant string
 * @fk_str: string to calculate the length
 * Return: the length of the string
 */
unsigned int fk_strlen_const(const char *fk_str)
{
    unsigned int i = 0;

    while (fk_str[i] != '\0')
        i++;

    return i;
}

/**
 * fk_strlen - Function to find the length of a string
 * @fk_str: string to calculate the length
 * Return: the length of the string
 */
unsigned int fk_strlen(char *fk_str)
{
    unsigned int i = 0;

    while (fk_str[i] != '\0')
        i++;

    return i;
}

/**
 * fk_strcmp - Function to compare 2 strings and find if they are equal
 * @fk_s1: first string to compare
 * @fk_s2: second string to compare
 * Return: 1 for equal, 0 if not
 */
int fk_strcmp(char *fk_s1, char *fk_s2)
{
    unsigned int i = 0;

    while (fk_s1[i] != '\0')
    {
        if (fk_s1[i] != fk_s2[i])
            return 0;
        i++;
    }

    return 1;
}

