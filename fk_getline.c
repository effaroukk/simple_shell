#include "fk.h"

/**
 * fk_my_getline - a function that
 *
 */
char *fk_my_getline(void)
{
	static char fk_buffer[FK_BUFFER_SIZE];
	static size_t fk_buffer_index = 0;
	static ssize_t fk_bytes_read = 0;

	char *fk_line = NULL;
	size_t fk_line_size = 0;

	while (1)
	{
		if (fk_buffer_index >= fk_bytes_read)
		{
			fk_bytes_read = read(STDIN_FILENO, fk_buffer, FK_BUFFER_SIZE);

			if (fk_bytes_read <= 0)
			{
				if (fk_line_size > 0)
				{
					return (fk_line);
				}
				else
				{
					free(fk_line);
					return (NULL);
				}
			}
			fk_buffer_index = 0;
		}
		
		while (fk_buffer_index < fk_bytes_read && fk_buffer[fk_buffer_index] != '\n')
		{
			if (fk_line_size % FK_BUFFER_SIZE == 0)
			{
				fk_line = realloc(fk_line, fk_line_size + FK_BUFFER_SIZE);
				if (fk_line == NULL)
				{
					perror("Error allocating memory");
					exit(EXIT_FAILURE);
				}
			}
			
			fk_line[fk_line_size++] = fk_buffer[fk_buffer_index++];
		}

		if (fk_buffer_index < fk_bytes_read && fk_buffer[fk_buffer_index] == '\n')
		{
			fk_line[fk_line_size++] = fk_buffer[fk_buffer_index++];
			break;
		}
	}
	
	fk_line[fk_line_size] = '\0';

	return (fk_line);
}

int main(void) {
    while (1) {
        char *fk_line = fk_my_getline();

      
        if (fk_line == NULL) {
            printf("Reached end of input\n");
            break;
        }

       
        printf("Line: %s", fk_line);

       
        free(fk_line);
    }

    return 0;
}

