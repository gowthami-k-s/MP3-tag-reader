#include <stdio.h>
#include "header.h"

void do_edit(FILE *fp)
{
    char info[5];
    char data[100];
    //title = (-t), year = (-y), artist = (-a), album = (-A), content = (-g), comment = (-c)
    printf("Enter the name of the information to change : ");
    scanf(" %[^\n]",info);
    printf("Enter the data : ");
    scanf(" %[^\n]",data);
    

}
