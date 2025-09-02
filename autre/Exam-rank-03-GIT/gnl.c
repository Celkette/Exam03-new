#include "gnl.h"

char *get_next_line(int fd)
{
static char buf[1000000];
static int i = 0, bytes = 0;
char *line;
int j = 0;

if (fd < 0 || BUFFER_SIZE <= 0)
return NULL;
if (!(line = malloc(1000000)))
return (NULL);
while (1)
{
if (i >= bytes)
{
bytes = read(fd, buf, BUFFER_SIZE);
if (bytes <= 0)
return (free(line),NULL);
buf[bytes] = '\0';
i = 0;
}
while (i < bytes && buf[i] != '\n')
line[j++] = buf[i++];
if (i < bytes && buf[i] == '\n')
{
line[j++] = buf[i++];
break;
}
}
line[j] = '\0';
return (line);
}

int main(void)
{
int fd = open("test.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
printf("%s", line);
free(line);
}
close(fd);
return (0);
}
