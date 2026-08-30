#include <stdio.h>
#include "header.h"

void print_the_menu()
{
    printf("title = -t\nyear = -y\nartist = -a\nalbum = -A\ncontent = -g\ncomment = -c\n");
}

int convert_endian(int size)
{
    char *ptr = (char *)&size;

    for(int j = 0; j < 2; j++)
    {
        char temp = ptr[j];
        ptr[j] = ptr[3-j];
        ptr[3-j] = temp;
    }

    return size;
}