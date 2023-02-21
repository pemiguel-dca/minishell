#include "minishell.h"

#define READ_END 0
#define WRITE_END 1

// int spawn(char **args)
// {
// 	int fd[2];
// 	char *line;

// 	pipe(fd);
// 	if (fork() == 0)
// 	{
// 		close(fd[READ_END]);
// 		dup2(fd[WRITE_END], STDOUT_FILENO);
// 		dup2(fd[WRITE_END], STDERR_FILENO);
// 		close(fd[WRITE_END]);
// 		char *argg[] = {"uname", "-a", 0};
// 		char *try[] = {"wc", "-l", 0};
// 		execve("/bin/ls", argg, NULL);
// 		execve("/bin/wc -l", try, NULL);
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		char buffer[1024];
// 		close(fd[WRITE_END]);
// 		while ((line = get_next_line(fd[READ_END])))
// 		{
// 			printf("%s", line);
// 		}
// 		wait(NULL);
// 	}
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	for (int i=0; envp[i] != NULL; ++i)
		printf("%s\n", envp[i]);

	// char	*input;
	// t_info	info;
	// char	**args;
	// int		i;

	// while (true)
	// {
	// 	input = readline("▲ " COLOR_BOLD COLOR_CYAN "msh" COLOR_OFF " ");
	// 	add_history(input);
	// 	args = ft_split(input, ' ');
	// 	spawn(args);
	// 	i = 0;
	// 	while (args[i])
	// 	{
	// 		free(args[i]);
	// 		++i;
	// 	}
	// 	free(args);
	// 	free(input);
	// }
	return (0);
}
