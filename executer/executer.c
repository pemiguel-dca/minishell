/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:11:40 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/18 18:01:57 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static void	set_pipe_channels(t_vec *expressions, size_t i, int *pipe_fd, int input_fd, int output_fd)
{
	if (i + 1 < expressions->len)
	{
		close(pipe_fd[READ_END]);
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[WRITE_END]);
	}
	else
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
	}
}

static void	execute_cmd(t_expression *expr)
{
	char	*path;

	path = bin_path(*expr);
	if (path)
	{
		vec_push(&expr->args, 0);
		execve(path, (char **)expr->args.buf, NULL);
	}
	else
	{
		// TODO: cannot use
		fprintf(stderr, "Command not found: %s\n", (char *)expr->args.buf[0]);
		exit(EXIT_FAILURE);
	}
}


int executer(t_vec *expressions, int input_fd, int output_fd)
{
	int 			pipe_fd[2];
	static size_t	i = 0;
	t_expression	*expr;
	t_files			*files;

	if (pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	expr = expressions->buf[i];
	files = malloc(sizeof(t_files));
	if (files_to_be_created(expressions) && i == 0)
		files->new_files = create_files(expressions);
	if (fork() == 0)
	{
		if (expr->state == CMD)
		{
			if (theres_a_need_to_redir(expressions, i))
			{
				//percorre ate ao last in
				while (!last_in(expressions, i))
				{
					//pode ter ficheiros antes do final que nao existem
					files->read_file = read_fd(((t_expression *)expressions->buf[i + 2])->args.buf[0]);
					i += 2;
				}
				set_pipe_channels(expressions, i, pipe_fd, files->read_file, output_fd);
				execute_cmd(expr);
			}
			else
			{
				i += times_in(expressions, i);
				set_pipe_channels(expressions, i, pipe_fd, input_fd, output_fd);
				execute_cmd(expr);
			}
		}
	}
	else
	{
		// Parent process
		wait(NULL);
		if (i + 1 < expressions->len)
		{
			close(pipe_fd[WRITE_END]);
			if (input_fd != STDIN_FILENO)
				close(input_fd);
			while (i < expressions->len)
			{
				expr = expressions->buf[i];
				/*'ls | ', este exemplo abre heredoc que espera um comando*/
				if (expr->state == PIPED)
				{
					i += 1;
					executer(expressions, pipe_fd[READ_END], output_fd);
					break ;
				}
				else if ((expr->state == OUT || expr->state == APPEND)
					&& last_out_append(expressions, i))
				{
					files->pos_file = get_pos_fd(expressions, i);
					redir_out_append(pipe_fd[READ_END], files->new_files[files->pos_file]);
				}
				i += 1;
			}
		}
		else
		{
			i = 0;
			if (input_fd != STDIN_FILENO)
				close(input_fd);
			if (output_fd != STDOUT_FILENO)
				close(output_fd);
		}
		if (i >= expressions->len) //reset ao i para a próxima vez, talvez uma estrutura faria mais sentido talvez, manda msg quando vires para discutirmos isto
			i = 0;
	}
	return (0);
}
