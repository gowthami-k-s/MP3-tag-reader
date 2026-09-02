#include <stdio.h>
#include <string.h>
#include "header.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Invalid arguments\n");
        printf("Use -h for help\n");
        return 1;
    }

    check_operation_type(argv);
    return 0;
}

void check_operation_type(char *argv[])
{
    view v;
    edit e;
    if(strcmp(argv[1], "-v") == 0)
    {
        if(argv[2] == NULL)
        {
            printf("Use : ./a.out -v file_name.mp3\n");
            return;
        }
        if(read_and_validate_view_arg(&v,argv))
            do_view(&v);
        else
            return;
    }
    else if(strcmp(argv[1], "-e") == 0)
    {
        if(argv[2] == NULL || argv[3] == NULL || argv[4] == NULL)
        {
            printf("Use : ./a.out -e <-t/-y/-a/-A/-g/-c> new_data file_name.mp3\n");
            return;
        }
        if(read_and_validate_edit_arg(&e,argv))
            do_edit(&e);
        else
            return;
    }
    else if(strcmp(argv[1], "-h") == 0)
    {
        print_the_menu();
    }
    else
    {
        printf("Not valid input\n");
        printf("Use -h for help\n");
    }
}