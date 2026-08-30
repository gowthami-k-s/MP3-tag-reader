#ifndef HEAD_H
#define HEAD_H

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
    char new_data[100];
    FILE *fp;
}edit;

int read_and_validate_view_arg(view *v,char **argv);
int read_and_validate_edit_arg(edit *e,char **argv);

void do_view(view *v);
void do_edit(edit *e);

void check_operation_type(char **argv);
void print_the_menu();
int convert_endian(int size);

#endif