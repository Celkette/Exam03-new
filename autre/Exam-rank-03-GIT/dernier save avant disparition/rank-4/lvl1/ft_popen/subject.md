# ft_popen
## authorized function
pipe, fork,dup2, execvp, close, exit
## information
Write the following function :
```
int ft_popen(const char *file, char *const argv[], char type);
```
the function must launch the executable file with the arguments argv (using execvp).
If type is '**r**' the function must return a file descriptor connected to the output of the command.
If type is '**w**' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return **-1**.
for example, the function could be used like that :
```
int main()
{
	int fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');

	char *line;
	while ((line > get_next_line(fd)))
		ft_putstr(line);
}
```
Hints :
Do not leak file descriptor !
