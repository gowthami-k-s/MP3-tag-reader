#include <stdio.h>
#include <string.h>
#include "header.h"

void do_edit(edit *e)
{
    e->fp = fopen(e->file_name, "rb");
    FILE *fp1 = fopen("temp.mp3", "wb");

    if(e->fp == NULL)
    {
        printf("file not found\n");
        fclose(fp1);
        return;
    }

    char arr[10];
    fread(arr, 1, 10, e->fp);

    if(!(arr[0] == 'I' && 
        arr[1] == 'D' &&
        arr[2] == '3'))
        {
            printf("ID3 not found\n");
        }

    fwrite(arr, 1, 10, fp1);

    char tag[5];
    char flag[3];
    int size;

    int i = 6;
    while(i > 0)
    {
        //read tag from file
        fread(tag, 1, 4, e->fp);
        tag[4] = '\0';
        fwrite(tag, 1, 4, fp1);
        
        //read size from file
        fread(&size, 1, 4, e->fp);
        fwrite(&size, 1, 4, fp1);

        //coverting big endian to little endian
        size = convert_endian(size);

        fread(flag, 1, 3, e->fp);
        fwrite(flag, 1, 3, fp1);

        char data[size];
        fread(data, 1, size-1, e->fp);
        data[size-1] = '\0';

        if(strcmp(tag, "TIT2") == 0)
        {
            
        }
        else if(strcmp(tag, "TYER") == 0)
        {
            
        }
        else if(strcmp(tag, "TALB") == 0)
        {
            
        }
        else if(strcmp(tag, "TPE1") == 0)
        {
            
        }
        else if(strcmp(tag, "TCON") == 0)
        {
            
        }
        else if(strcmp(tag, "COMM") == 0)
        {
            
        }
    }
}

int read_and_validate_edit_arg(edit *e,char *argv[])
{
    if(strcmp(argv[2], "-t") == 0)
    {
        strcpy(e->tag, "TIT2");
    }
    else if(strcmp(argv[2], "-y") == 0)
    {
        strcpy(e->tag, "TYER");
    }
    else if(strcmp(argv[2], "-a") == 0)
    {
        strcpy(e->tag, "TPE1");
    }
    else if(strcmp(argv[2], "-A") == 0)
    {
        strcpy(e->tag, "TALB");
    }
    else if(strcmp(argv[2], "-g") == 0)
    {
        strcpy(e->tag, "TCON");
    }
    else if(strcmp(argv[2], "-c") == 0)
    {
        strcpy(e->tag, "COMM");
    }
    else
    {
        printf("Invalid tag\n");
        return 0;
    }

    strcpy(e->new_data, argv[3]);

    if(strstr(argv[4], ".mp3") != NULL)
    {
        strcpy(e->file_name, argv[2]);
    }
    else
    {
        printf("The given name is not a mp3 file\n");
        return 0;
    }

    return 1;
}
