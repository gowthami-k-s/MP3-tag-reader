# MP3 Tag Reader & Editor

## Description

MP3 Tag Reader & Editor is a **C programming project** used to read, display, and edit metadata information stored in MP3 files.

The project works with **ID3v2 metadata** and allows users to view and modify common MP3 tags through command-line arguments.

## Features

- Read and display MP3 metadata
- Edit individual metadata tags
- Supports ID3v2 metadata frames
- Command-line based application
- Handles binary MP3 files
- Uses temporary file handling while editing
- Validates user input and file type

## Supported Tags

| Option | ID3 Tag | Description |
|--------|---------|-------------|
| `-t`   | TIT2    | Title       |
| `-y`   | TYER    | Year        |
| `-a`   | TPE1    | Artist      |     
| `-A`   | TALB    | Album       |
| `-g`   | TCON    | Genre       |
| `-c`   | COMM    | Comment     |

## How It Works

### View Operation

The view operation reads the ID3 header and extracts the metadata frames from the MP3 file.
./a.out -v sample.mp3

It displays information such as:

Title   : Sample Song
Artist  : Sample Artist
Album   : Sample Album
Year    : 2026
Genre   : Rock
Comment : Sample Comment

### Edit Operation

The edit operation allows the user to modify a particular tag.
./a.out -e -t "New Title" sample.mp3

Other examples:
./a.out -e -y "2026" sample.mp3
./a.out -e -a "New Artist" sample.mp3
./a.out -e -A "New Album" sample.mp3
./a.out -e -g "Rock" sample.mp3
./a.out -e -c "My Comment" sample.mp3

### Help

./a.out -h

## Technologies Used

* C Programming
* GCC Compiler
* Linux / WSL
* Git & GitHub
* ID3v2
* File Handling

## Concepts Used

* Structures
* Pointers
* Functions
* Dynamic Memory Allocation
* Command-Line Arguments
* String Handling
* File Handling
* Binary File Operations
* Endian Conversion
* Temporary File Handling

## Project Structure

MP3-Tag-Reader
* main.c
* view.c
* edit.c
* header.h
* menu.c
* Makefile
* README.md

## Learning Outcome

-  C file handling
-  Binary data processing
-  Structures
-  Pointers
-  Dynamic memory allocation
-  Command-line arguments
-  ID3 metadata handling.

## Author

**K S Gowthami**
