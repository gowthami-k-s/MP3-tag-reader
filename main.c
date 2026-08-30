#include <stdio.h>
#include "header.h"

int main(int argc, char *argv[])
{
    check_operation_type(argv);
    return 0;
}

void check_operation_type(char *argv[])
{
    if(strcmp(argv[1], "-v") == 0)
    {
        read_and_validate_view_arg(view,argv);
        do_view(view);
    }
    else if(strcmp(argv[1], "-e") == 0)
    {
        read_and_validate_edit_arg(edit,argv);
        do_edit(edit);
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