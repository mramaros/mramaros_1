*This project has been created as part of the 42 curriculum by mramaros.*

## GET_NEXT_LINE

# Description

<span style="color:green">get_next_line is a project from 42.</span>

The objective is to implement a function that reads a file line by line from a given file descriptor.

Function prototype:
```c
	char *get_next_line(int fd);
```
The function must:

* Read from a file descriptor

* Return one line at a time

* Include the newline character (\n) if present

* Return NULL at end of file or on error

* Work correctly with successive calls

* (Bonus) Handle multiple file descriptors

* This project focuses on memory management, static variables, and file I/O in C.

# Instructions

__Compilation__
Compile with:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

You can change the buffer size during compilation:
```bash
	cc -D BUFFER_SIZE=1000 ...
```
<span style="color:orange">Example usage:</span>

__<span style="color:green">NB:</span>__ you need create the file .txt to make a test, so you need to follow this process:
```bash
	echo "(content)" >> test.txt
```
```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		i++;
		printf("line %d :%s", i, line);
		free(line);
	}
	close(fd);
	return (0);
}
```
# data structure && algorithme

 __1. Static Stash__
```c
	static char	*stash;
```
The stash is a static pointer used to preserve unread data between function calls.

 # <span style="color:red">so..., Why static ? </span>

Because get_next_line() must remember previously read data that has not yet been returned.
Without static, the variable would be reinitialized at every call.

Initialization in the code:
```c
	if (!stash)
		stash = ft_strdup("");
```
This guarantees that stash is always a valid string before reading begins.

 __2. Dynamic Buffer -> inside of get_next_line__
```c
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
```
The buffer is dynamically allocated for each call to ft_get_text.

Purpose:
* Temporarily store data read from read()
* Append it to stash
* Stop reading once a newline (\n) is found

Reading loop:
```c
	while (!ft_strchr(stash, '\n') && read_line > 0)
```
This ensures:

Reading stops as soon as a full line is available

After reading:
```c
	buffer[read_line] = '\0';
	tmp = ft_strjoin(stash, buffer);
	stash = tmp;
```
So your structure is:
```
	[read() → buffer] → append → stash
```
 __3. Line Extraction -> get_stach__

```c
	static char *get_stach(char *stash)
```
This function extracts the next line from stash.

<span style="color:orange">Steps:</span>

* Iterate until ```\n```

* Include ```\n``` if it exists

* Return a substring using ft_substr
```c
	return ((char *)ft_substr(stash, 0, i));
```
This creates a newly allocated string that will be returned to the user.

__4. Stash Cleaning -> clean_stash__
```c
	static char *clean_stash(char *stash)
```
After extracting the line, the remaining content must be preserved for the next call.

<span style="color:orange">Logic:</span>

* Find the newline

* If no newline → free stash and return NULL

* Otherwise:
```c
	new_stach = ft_substr(stash, (i + 1), ft_strlen(stash) - i - 1);
	free(stash);
	return (new_stach);
```
So the stash evolves like this:
```
	Before extraction:
	"Line1\nLine2\nLi"

	After returning "Line1\n":
	"Line2\nLi"
```
__5. Global Execution Flow__

This implementation follows this precise order:

* Initialize stash if needed

* Fill stash using ft_get_text

* Extract line using get_stach

* Clean stash using clean_stash

* Return the extracted line

# Ressources

* <span style="color:red">Youtube</span> : mentor the beginning of get_next_line with tutorials and stash variable understanding
* <span style="color:purple">PEER TO PEER</span> : debugging assistance and facilitates projects


# AI USAGE
* main tester for each function
* It explains some of the tiny errors in my code.
* help with readme layout
