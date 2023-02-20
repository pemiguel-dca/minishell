#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include "colors.h"
#include "libft/libft.h"

#define READ_END 0
#define WRITE_END 1

int spawn(char **args)
{
	int fd[2];
	char *line;

	pipe(fd);
	if (fork() == 0)
	{
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		dup2(fd[WRITE_END], STDERR_FILENO);
		close(fd[WRITE_END]);
		char *argg[] = {"pwd", 0, 0};
		execve("/bin/pwd", argg, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		char buffer[1024];
		close(fd[WRITE_END]);
		while ((line = get_next_line(fd[READ_END])))
		{
			printf("%s", line);
		}
		wait(NULL);
	}
}

int	main()
{
	char	*input;
	char	**args;
	int		i;

	while (true)
	{
		input = readline("▲ " COLOR_BOLD COLOR_CYAN "msh" COLOR_OFF " ");
		add_history(input);
		args = ft_split(input, ' ');
		spawn(args);
		i = 0;
		while (args[i])
		{
			free(args[i]);
			++i;
		}
		free(args);
		free(input);
	}
}
