/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:03:11 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/07 21:50:43 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "wait.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line/get_next_line.h"
#include "redirs/redirs.h"

static void	replace_in_out(t_list **nodes, int *pipe_fd, int *input_fd, int *output_fd)
{
	if (((t_list *)*nodes)->next != NULL)
	{
		close(pipe_fd[READ_END]);
		if (*input_fd != STDIN_FILENO)
		{
			dup2(*input_fd, STDIN_FILENO);
			close(*input_fd);
		}
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[WRITE_END]);
	}
	else
	{
		if (*input_fd != STDIN_FILENO)
		{
			dup2(*input_fd, STDIN_FILENO);
			close(*input_fd);
		}
		if (*output_fd != STDOUT_FILENO)
		{
			dup2(*output_fd, STDOUT_FILENO);
			close(*output_fd);
		}
	}
}

static void	execute_cmd(t_list *nodes)
{
	t_expression	*node;
	char	*path;

	node = ((t_expression *)nodes->content);
	if (is_valid_args(*node))
	{
		path = get_cmd_path(*node);
		execve(path, node->args, NULL);
	}
	else
	{
		// TODO: mesma coisa (fazer panic)
		fprintf(stderr, "Command not found: %s\n", node->args[0]);
		exit(EXIT_FAILURE);
	}
}

int spawn(t_list *nodes, int input_fd, int output_fd)
{
	int pipe_fd[2];
	char *path;
	t_list	*head;

	head = nodes;
	if (nodes->next != NULL && pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	if (fork() == 0)
	{
		// Child process
		replace_in_out(&nodes, pipe_fd, &input_fd, &output_fd);
		if (((t_expression *)(nodes->content))->state == CMD)
			execute_cmd(nodes);
	}
	else
	{
		int	*new_file_descriptors;
		int	size;

		size = 0;
		// Parent process
		if (nodes->next != NULL)
		{
			close(pipe_fd[WRITE_END]);
			if (input_fd != STDIN_FILENO)
				close(input_fd);
			if (files_to_be_created(nodes))
				new_file_descriptors = create_files(nodes, &size);
			while (((t_expression *)(nodes->content))->state == CMD)
				nodes = nodes->next;
			t_states action = ((t_expression *)(nodes->content))->state;
			nodes = nodes->next;
			if (action == PIPE)
				spawn(nodes, pipe_fd[READ_END], output_fd);
			/*So para ver o funcionamento*/
			if (files_to_be_created(head))//nodes percorre, head é o inicio e neste caso é preciso o inicio pois quando nodes avançar o resultado desta funçao nao vai ser accurate
				redir_out(pipe_fd[READ_END], new_file_descriptors, size);
		}
		else
		{
			if (input_fd != STDIN_FILENO)
				close(input_fd);
			if (output_fd != STDOUT_FILENO)
				close(output_fd);
		}
		wait(NULL);
	}
	return 0;
}

