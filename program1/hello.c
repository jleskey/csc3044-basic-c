#include <stdio.h>
#include <stdlib.h>

#define STRING_INCREMENT 8

char *jReadLine(FILE *stream);
char *promptInput(char *prompt);

int main(int argc, char const *argv[])
{
    char *name = argc > 1 ? (char *)argv[0] : promptInput("Enter name:");

    printf("hello %s\n", name);
}

char *promptInput(char *prompt)
{
    char *response = NULL;
    while (response == NULL)
    {
        printf("%s ", prompt);
        response = jReadLine(stdin);
    }
}

char *jReadLine(FILE *stream)
{
    char *line = NULL;

    char lastChar;
    int length = 0;

    while ((lastChar = fgetc(stdin)) != '\n')
    {
        if (length % STRING_INCREMENT == 0)
            line = realloc(line, sizeof(line) * STRING_INCREMENT);
        line[length++] = lastChar;
    }

    return line;
}
