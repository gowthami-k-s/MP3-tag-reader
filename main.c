#include <stdio.h>
#include <string.h>
#include "header.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Invalid arguments\n");
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
        if(read_and_validate_view_arg(&v,argv))
            do_view(&v);
        else
            return;
    }
    else if(strcmp(argv[1], "-e") == 0)
    {
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
    }
}