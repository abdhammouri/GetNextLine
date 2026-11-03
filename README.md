*This activity has been created as part of the 42 curriculum by aalhammo.*

# Get Next Line

## Description

`get_next_line` is a C project that implements a function capable of reading a file descriptor one line at a time.

The function prototype is:

```c
char	*get_next_line(int fd);
```

Each call to `get_next_line()` returns the next line available from the given file descriptor.

The returned line includes the terminating newline character `\n` when one is present. If the end of the file is reached and the last line does not end with `\n`, the final line is returned without it.

The function returns `NULL` when there is nothing left to read or when an error occurs.

The project is designed to work with both regular files and standard input.

## Files

The project contains:

```text
get_next_line.c
get_next_line_utils.c
get_next_line.h
README.md
```

## Instructions

The project can be compiled using:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c -o gnl
```

Then run:

```bash
./gnl
```

The `BUFFER_SIZE` value determines how many bytes are read at a time.

Different values can be tested, for example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
get_next_line.c get_next_line_utils.c main.c -o gnl
```

or:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 \
get_next_line.c get_next_line_utils.c main.c -o gnl
```

The implementation also defines a default `BUFFER_SIZE` when the compiler flag is not provided.

## Algorithm

The implementation uses a static variable called `stash` to preserve unread data between calls to `get_next_line()`.

The general algorithm is:

```text
read data
    |
    v
append data to stash
    |
    v
look for '\n'
    |
    +---- not found ----> read again
    |
    +---- found
             |
             v
        extract line
             |
             v
       save remaining data
             |
             v
         return line
```

### Reading

The function reads from the file descriptor using:

```c
read(fd, buffer, BUFFER_SIZE);
```

Data is read in chunks instead of reading the entire file at once.

Reading continues until either:

- a newline character is found;
- the end of the file is reached;
- an error occurs.

### Static Stash

A static variable is used to remember data that was already read but does not belong to the current returned line.

For example, if a read operation returns:

```text
Hello\nWorld
```

the first call should return:

```text
Hello\n
```

while:

```text
World
```

must remain available for the next call.

The static variable allows this data to survive after the current function call finishes.

### Line Extraction

Once a newline is found, memory is allocated for the line.

The line contains all characters from the beginning of the stash up to and including `\n`.

If the end of the file is reached without a final newline, the remaining characters are returned as the final line.

### Remaining Data

After the line is extracted, any characters after the newline are copied into a new allocated string.

This remaining data becomes the new stash and is used during the next call to `get_next_line()`.

If no data remains, the stash is freed and set to `NULL`.

## Memory Management

Memory is dynamically allocated using `malloc()`.

Allocated memory is freed when it is no longer needed.

The implementation must avoid:

- memory leaks;
- double frees;
- invalid memory access.

The caller is responsible for freeing every line returned by `get_next_line()`.

## Edge Cases

The implementation should correctly handle:

```text
empty files
files containing only a newline
files without a final newline
multiple lines
very long lines
BUFFER_SIZE = 1
large BUFFER_SIZE values
invalid file descriptors
read errors
standard input
```

## Allowed Functions

The external functions allowed by the subject are:

```text
read
malloc
free
```

The project does not use Libft.

`lseek()` and global variables are not used.

## Resources

Resources used while working on this project:

- The official 42 Get Next Line subject.
- C documentation for `read()`.
- C documentation for file descriptors.
- C documentation for `malloc()` and `free()`.
- Documentation and learning material about static variables.
- Previous knowledge of strings, pointers, and memory management in C.

### AI Usage

AI was used as a learning and development aid during the project.

It was used to:

- explain file descriptors;
- explain how `read()` works;
- explain `BUFFER_SIZE`;
- explain static variables;
- explain the idea of preserving leftover data between function calls;
- review memory allocation and freeing;
- discuss edge cases and testing;
- review the general structure of the implementation;
- assist in drafting this README.

The implementation was reviewed progressively with the intention of understanding each concept and function used in the project.
