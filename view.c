#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
            fclose(v->fp);
            return;
        }


    int tag_size = ((unsigned char)header[6] << 21) |
                    ((unsigned char)header[7] << 14) |
                    ((unsigned char)header[8] << 7) |
                    (unsigned char)header[9];
    
    int read_byte = 0;
    char tag[5];
    char flag[2];
    int size;
    
    while(read_byte < tag_size)
    {
        if(fread(tag, 1, 4, v->fp) != 4)
            break;

        tag[4] = '\0';

        // Padding reached
        if(tag[0] == '\0')
            break;

        if(fread(&size, 1, 4, v->fp) != 4)
            break;

        size = convert_endian(size);

        if(size <= 0 || read_byte + 10 + size > tag_size)
        {
            printf("Invalid frame size\n");
            break;
        }

        if(fread(flag, 1, 2, v->fp) != 2)
            break;

        char *data = malloc(size + 1);

        if(data == NULL)
        {
            printf("Memory allocation failed\n");
            break;
        }

        if(fread(data, 1, size, v->fp) != size)
        {
            free(data);
            break;
        }

        data[size] = '\0';

        read_byte += 10 + size;

        if(strcmp(tag, "TIT2") == 0)
            printf("Title   : %s\n", data + 1);

        else if(strcmp(tag, "TYER") == 0)
            printf("Year    : %s\n", data + 1);

        else if(strcmp(tag, "TALB") == 0)
            printf("Album   : %s\n", data + 1);

        else if(strcmp(tag, "TPE1") == 0)
            printf("Artist  : %s\n", data + 1);

        else if(strcmp(tag, "TCON") == 0)
            printf("Genre   : %s\n", data + 1);

        else if(strcmp(tag, "COMM") == 0)
            printf("Comment : %s\n", data + 1);

        free(data);
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