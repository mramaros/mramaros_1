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
```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int fd = open("file.txt", O_RDONLY);
	char *line;

	if (fd < 0)
		return (1);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
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

* Reading stops as soon as a full line is available

* Or when EOF is reached

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

