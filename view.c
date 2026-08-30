#include <stdio.h>
#include <string.h>
#include "header.h"

void do_view(view *v)
{
    s.fp = fopen("file_name", "rb");
    char header[10];
    if(s.fp == NULL)
    {
        printf("File not found\n");
    }

    fread(header, 1, 10, fp);

    if(header[0] == 'I' && 
        header[1] == 'D' &&
        header[2] == '3')
        {
            printf("ID3 found\n");
        }
    else{
        printf("ID3 not found\n");
    }

    char tag[5];
    char flag[2];
    int size;
    
    int i = 6;
    while(i > 0)
    {
        //read tag from file
        fread(tag, 1, 4, s.fp);
        tag[4] = '\0';
        
        //read size from file
        fread(&size, 1, 4, s.fp);

        //coverting big endian to little endian
        char *ptr = (char *)&size;
        for(int j = 0; j < 2; j++)
        {
            char temp = ptr[j];
            ptr[j] = ptr[3-j];
            ptr[3-j] = temp;
        }

        char data[size + 1];

        fread(flag, 1, 2, s.fp);
        fread(data, 1, size, s.fp);
        data[size] = '\0';

        char *text = data + 1;

        if(strcmp(tag, "TIT2") == 0)
        {
            printf("Title : %s\n",text);
            i--;
        }
        else if(strcmp(tag, "TYER") == 0)
        {
            printf("Year : %s\n",text);
            i--;
        }
        else if(strcmp(tag, "TALB") == 0)
        {
            printf("Album : %s\n",text);
            i--;
        }
        else if(strcmp(tag, "TPE1") == 0)
        {
            printf("Artist : %s\n",text);
            i--;
        }
        else if(strcmp(tag, "TCON") == 0)
        {
            printf("Genre : %s\n",text);
            i--;
        }
        else if(strcmp(tag, "COMM") == 0)
        {
            printf("Comment : %s\n",text);
            i--;
        }

    }

    fclose(fp);
}

void read_and_validate_view_arg(view *v,char *argv[])
{
    if(strstr(argv[2], .mp3) != NULL)
    {
        strcpy(v->filename, argv[2]);
    }
    else
    {
        printf("The given name is not a mp3 file\n");
    }
}