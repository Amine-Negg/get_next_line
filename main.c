#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
    int fd;
    char *str;


    fd = open("test.txt", O_RDONLY);
    str = malloc(sizeof(char));
    if (!str)
    {
        free(str);
        return (NULL);
    }
    

    while ((str = get_next_line(fd)) != NULL)
    {
        printf("%s", str);
        free(str);
        str = NULL;
    }
    return 0;
    
}