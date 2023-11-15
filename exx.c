#include "fk.h"
/**
 * fk_strncpy - copies a string
 * @fk_dest: the destination string to be copied to
 * @fk_src: the source string
 * @fk_n: the amount of characters to be copied
 * Return: the concatenated string
 */
char *fk_strncpy(char *fk_dest, char *fk_src, int fk_n)
{
    int i, j;
    char *fk_s = fk_dest;

    i = 0;
    while (fk_src[i] != '\0' && i < fk_n - 1)
    {
        fk_dest[i] = fk_src[i];
        i++;
    }
    if (i < fk_n)
    {
        j = i;
        while (j < fk_n)
        {
            fk_dest[j] = '\0';
            j++;
        }
    }
    return (fk_s);
}

/**
 * fk_strncat - concatenates two strings
 * @fk_dest: the first string
 * @fk_src: the second string
 * @fk_n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *fk_strncat(char *fk_dest, char *fk_src, int fk_n)
{
    int i, j;
    char *fk_s = fk_dest;

    i = 0;
    j = 0;
    while (fk_dest[i] != '\0')
        i++;
    while (fk_src[j] != '\0' && j < fk_n)
    {
        fk_dest[i] = fk_src[j];
        i++;
        j++;
    }
    if (j < fk_n)
        fk_dest[i] = '\0';
    return (fk_s);
}

/**
 * fk_strchr - locates a character in a string
 * @fk_s: the string to be parsed
 * @fk_c: the character to look for
 * Return: (fk_s) a pointer to the memory area fk_s
 */
char *fk_strchr(char *fk_s, char fk_c)
{
    do {
        if (*fk_s == fk_c)
            return (fk_s);
    } while (*fk_s++ != '\0');

    return (NULL);
}

