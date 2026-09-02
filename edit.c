#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

void do_edit(edit *e)
{
    e->fp = fopen(e->file_name, "rb");

    //checking if file is empty
    if(e->fp == NULL)
    {
        printf("file not found\n");
        return;
    }

    //creating temporary file
    FILE *fp1 = fopen("temp.mp3", "wb");
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

            fclose(e->fp);
            fclose(fp1);
            remove("temp.mp3");
            return;
        }

    //Write header into new file
    fwrite(arr, 1, 10, fp1);

    int tag_size = ((unsigned char)arr[6] << 21) |
                   ((unsigned char)arr[7] << 14) |
                   ((unsigned char)arr[8] << 7) |
                   (unsigned char)arr[9];

    int read_byte = 0;

    char tag[5];
    char flag[2];
    int size;

    while(read_byte < tag_size)
    {
        // Read frame ID
        if(fread(tag, 1, 4, e->fp) != 4)
            break;

        tag[4] = '\0';

        if(tag[0] == '\0')
            break;

        // Read frame size
        if(fread(&size, 1, 4, e->fp) != 4)
            break;

        //convert endian
        int n_size = convert_endian(size);

        // Validate frame size
        if(n_size <= 0 || read_byte + 10 + n_size > tag_size)
        {
            printf("Invalid frame size\n");
            break;
        }

        // Read 2 flag bytes
        if(fread(flag, 1, 2, e->fp) != 2)
            break;

        // Read frame data
        char *data = malloc(n_size);
        if(data == NULL)
        {
            printf("Memory allocation failed\n");
            break;
        }
        if(fread(data, 1, n_size, e->fp) != n_size)
        {
            free(data);
            break;
        }

        //add the size to the read_byte
        read_byte += 10 + n_size;

        //comparing tag with the tag given by user 
        if(strcmp(tag, e->tag) == 0)
        {
            // New text frame data
            char *new_data = malloc(strlen(e->new_data) + 1);
            if(new_data == NULL)
            {
                free(data);
                break;
            }

            new_data[0] = data[0];
            strcpy(new_data + 1, e->new_data);

            //writing the new data into the file
            int new_size = strlen(e->new_data) + 1;
            fwrite(tag, 1, 4, fp1);

            int temp_size = convert_endian(new_size);
            fwrite(&temp_size, 1, 4, fp1);
            fwrite(flag, 1, 2, fp1);
            fwrite(new_data, 1, new_size, fp1);
            free(new_data);
        }
        else 
        {
            //writing the old data into new file
            fwrite(tag, 1, 4, fp1);
            fwrite(&size, 1, 4, fp1);
            fwrite(flag, 1, 2, fp1);
            fwrite(data, 1, n_size, fp1);
        }
        free(data);
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
