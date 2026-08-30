#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>

typedef struct
{
    char file_name[30];
    FILE *fp;
}view;

typedef struct
{
    char file_name[30];
    char tag[10];
    FILE *fp;
}edit;

void read_and_validate_view_arg(view,char *argv[]);
void read_and_validate_edit_arg(edit,char *argv[]);
void do_view(view);
void do_edit(edit);
void check_operation_type(char *argv[]);
void print_the_menu();

#endif