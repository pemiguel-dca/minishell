/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:11:40 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/18 20:18:11 by pemiguel         ###   ########.fr       */
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
/*To much arguments passed in function, maybe add a structure (?)*/
static void	child_process(t_vec *expressions, int *pipe_fd, int input_fd, int output_fd, size_t *i, t_files *files)
{
	t_expression	*expr;

	expr = expressions->buf[*i];
	if (expr->state == CMD)
	{
		if (theres_a_need_to_redir(expressions, *i))
		{
			//Run until last_in but at the same time tries to open the files
			while (!last_in(expressions, *i))
			{
				files->read_file = read_fd(((t_expression *)expressions->buf[*i + 2])->args.buf[0]);
				*i += 2;
			}
			set_pipe_channels(expressions, *i, pipe_fd, files->read_file, output_fd);
			execute_cmd(expr);
		}
		else
		{
			*i += times_in(expressions, *i);
			set_pipe_channels(expressions, *i, pipe_fd, input_fd, output_fd);
			execute_cmd(expr);
		}
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
	files = malloc(sizeof(t_files));
	if (files_to_be_created(expressions) && i == 0)
		files->new_files = create_files(expressions);
	if (fork() == 0)
		child_process(expressions, pipe_fd, input_fd, output_fd, &i, files);
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
		if (i >= expressions->len)
			i = 0;
	}
	return (0);
}
