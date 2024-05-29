#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
* main - Entry point of the shell program
* Return: Always 0 on success
*/
int main(void)
{
char *buffer;
size_t bufsize = BUFFER_SIZE;

buffer = (char *)malloc(bufsize * sizeof(char));
if (buffer == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}

while (1)
{
printf("#cisfun$ ");
getline(&buffer, &bufsize, stdin);

if (feof(stdin))
{
printf("\n");
break;
}

if (buffer[strlen(buffer) - 1] == '\n')
buffer[strlen(buffer) - 1] = '\0';

if (fork() == 0)
{
if (execlp(buffer, buffer, (char *)NULL) == -1)
{
perror(buffer);
exit(EXIT_FAILURE);
}
}
else
{
wait(NULL);
}
}

free(buffer);
return (0);
}
