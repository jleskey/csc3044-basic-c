/**
 * @file hello.c
 * @author Joseph Leskey
 * @date 15 January 2024
 * @note
 *  I just found out about Doxygen syntax, so my C comments have gotten
 *  an upgrade.
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * The incrementation factor of dynamically allocated char arrays
 *
 * @note
 *  Names often aren't very long, so we're going to try to save
 *  some memory just for the fun of it.
 */
#define STRING_INCREMENT 16

/**
 * Read a line from a given file descriptor
 *
 * @param[in] stream The file descriptor
 * @returns A meaningful line, or `NULL` if empty
 */
char *jReadLine(FILE *stream);

/**
 * Display prompt until the user inputs a useful value.
 *
 * @param[in] prompt The prompt to display
 * @returns A meaningful line of input from `stdin`
 */
char *promptInput(char const *prompt);

int main(int argc, char const *argv[])
{
    // NOTE: `name` should not be freed if sourced from the arguments.
    // This would perhaps be unwise in a larger project, but it saves
    // a negligable amount of CPU time since it doesn't copy the
    // argument.
    char *name = argc > 1 ? (char *)argv[1] : promptInput("Enter name:");

    printf("hello %s\n", name);

    // Name was not sourced from the arguments. Let's free this thing.
    // Since the OS would do this anyway, this is just to keep up
    // appearances.
    if (argc == 1)
    {
        free(name);
    }

    return EXIT_SUCCESS;
}

char *promptInput(char const *prompt)
{
    char *response = NULL;

    // We want to get useable input.
    while (!response)
    {
        printf("%s ", prompt);
        response = jReadLine(stdin);
    }

    // Add a newline after input for style and consistency with the sqrt
    // program.
    printf("\n");

    return response;
}

char *jReadLine(FILE *stream)
{
    char *buffer = NULL;

    char c, prevC = '\0';
    int length = 0;

    // Loop through all input characters until newline or EOF.
    while ((c = fgetc(stream)) != '\n' && c != EOF)
    {
        // Strip extraneous whitespace.
        // NOTE: This can leave a whitespace at the end of the line.
        if (c != ' ' || (prevC != ' ' && length != 0))
        {
            // If the buffer is full or empty, allocate more space in
            // increments of `STRING_INCREMENT`.
            if (length % STRING_INCREMENT == 0)
            {
                int newLength = length + STRING_INCREMENT + 1;

                // It would be a shame to lose the original buffer
                // reference if `realloc` fails. Let's avoid that.
                char *tempBuffer = realloc(buffer, sizeof(char) * newLength);
                if (!tempBuffer)
                {
                    free(buffer);
                    fprintf(stderr, "Memory allocation error.\n");
                    return NULL;
                }
                buffer = tempBuffer;
            }
            buffer[length++] = c;
        }
        prevC = c;
    }

    if (buffer)
    {
        if (prevC == ' ')
        {
            // We don't want a single space. Count this as empty.
            if (length == 1)
            {
                free(buffer);
                return NULL;
            }

            // We'll remove a trailing space.
            buffer[length - 1] = '\0';
        }
        else
        {
            // If we don't have to worry about a final space, we'll just
            // tidily close off the character array and make it an
            // official string.
            buffer[length] = '\0';
        }
    }

    return buffer;
}
