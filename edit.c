#include <stdio.h>
#include <string.h>
#include "header.h"

void do_edit(edit *e)
{
    e->fp = fopen(e->file_name, "rb");
    FILE *fp1 = fopen("temp.mp3", "wb");

    //checking if file is empty
    if(e->fp == NULL)
    {
        printf("file not found\n");
        if(fp1 != NULL)
            fclose(fp1);

        return;
    }
    if(fp1 == NULL)
    {
        printf("Cannot create a temporary file\n");
        fclose(e->fp);
        return;
    }

    char arr[10];
    fread(arr, 1, 10, e->fp);

    if(!(arr[0] == 'I' && 
        arr[1] == 'D' &&
        arr[2] == '3'))
        {
            printf("ID3 not found\n");
            return;
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
        
        //read size from file
        fread(&size, 1, 4, e->fp);

        //coverting big endian to little endian
        int n_size = convert_endian(size);

        fread(flag, 1, 3, e->fp);

        char data[n_size];
        //read data from file using the converted size
        fread(data, 1, n_size-1, e->fp);
        data[n_size-1] = '\0';

        //checking if tag is matching with the user given tag
        if(strcmp(tag, e->tag) == 0)
        {
            //writing new data into the new file
            fwrite(e->tag, 1, 4, fp1);
            int new_size = strlen(e->new_data)+1;
            int temp_size = convert_endian(new_size);
            fwrite(&temp_size, 1, 4, fp1);
            fwrite(flag, 1, 3, fp1);
            fwrite(e->new_data, 1, new_size-1, fp1);
        }
        else 
        {
            //writing the old data into new file
            fwrite(tag, 1, 4, fp1);
            fwrite(&size, 1, 4, fp1);
            fwrite(flag, 1, 3, fp1);
            fwrite(data, 1, n_size-1, fp1);
        }
        i--;
    }

    char ch;

    //copying the remaining data of original file into the new file
    while(fread(&ch, 1, 1, e->fp) == 1)
    {
        fwrite(&ch, 1, 1, fp1);
    }

    printf("Tag changed sucessfully\n");

    fclose(e->fp);
    fclose(fp1);

    remove(e->file_name);//removing the original file
    rename("temp.mp3", e->file_name);//renaming the temporary file into original file 
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
        strcpy(e->file_name, argv[4]);
    }
    else
    {
        printf("The given name is not a mp3 file\n");
        return 0;
    }

    return 1;
}
