#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;
    int     i;

    i = 1;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Erreur ouverture fichier\n");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d : %s", i, line);
        free(line);
        i++;
    }

    close(fd);
    return (0);
}
