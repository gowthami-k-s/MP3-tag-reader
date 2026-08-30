#include <stdio.h>
#include <string.h>
#include "header.h"

void do_view(view *v)
{
    v->fp = fopen(v->file_name, "rb");
    char header[10];
    if(v->fp == NULL)
    {
        printf("File not found\n");
        return;
    }

    fread(header, 1, 10, v->fp);

    if(!(header[0] == 'I' && 
        header[1] == 'D' &&
        header[2] == '3'))
        {
            printf("ID3 not found\n");
        }

    char tag[5];
    char flag[3];
    int size;
    
    int i = 6;
    while(i > 0)
    {
        //read tag from file
        fread(tag, 1, 4, v->fp);
        tag[4] = '\0';
        
        //read size from file
        fread(&size, 1, 4, v->fp);

        //coverting big endian to little endian
        size = convert_endian(size);

        fread(flag, 1, 3, v->fp);

        char data[size];
        fread(data, 1, size-1, v->fp);
        data[size-1] = '\0';

        if(strcmp(tag, "TIT2") == 0)
        {
            printf("Title : %s\n",data);
            i--;
        }
        else if(strcmp(tag, "TYER") == 0)
        {
            printf("Year : %s\n",data);
            i--;
        }
        else if(strcmp(tag, "TALB") == 0)
        {
            printf("Album : %s\n",data);
            i--;
        }
        else if(strcmp(tag, "TPE1") == 0)
        {
            printf("Artist : %s\n",data);
            i--;
        }
        else if(strcmp(tag, "TCON") == 0)
        {
            printf("Genre : %s\n",data);
            i--;
        }
        else if(strcmp(tag, "COMM") == 0)
        {
            printf("Comment : %s\n",data);
            i--;
        }

    }

    fclose(v->fp);
}

int read_and_validate_view_arg(view *v,char *argv[])
{
    if(strstr(argv[2], ".mp3") != NULL)
    {
        strcpy(v->file_name, argv[2]);
    }
    else
    {
        printf("The given name is not a mp3 file\n");
        return 0;
    }
    return 1;
}