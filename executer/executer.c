/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:11:40 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/19 02:19:43 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static void	set_pipe_channels(t_vec *expressions, t_executer *params)
{
	if (params->i + 1 < expressions->len)
	{
		close(params->pipe_fd[READ_END]);
		if (params->input_fd != STDIN_FILENO)
		{
			dup2(params->input_fd, STDIN_FILENO);
			close(params->input_fd);
		}
		dup2(params->pipe_fd[WRITE_END], STDOUT_FILENO);
		close(params->pipe_fd[WRITE_END]);
	}
	else
	{
		if (params->input_fd != STDIN_FILENO)
		{
			dup2(params->input_fd, STDIN_FILENO);
			close(params->input_fd);
		}
		if (params->output_fd != STDOUT_FILENO)
		{
			dup2(params->output_fd, STDOUT_FILENO);
			close(params->output_fd);
		}
	}
}

static void	child_process(t_vec *expressions, t_executer *params)
{
	t_expression	*expr;

	expr = expressions->buf[params->i];
	if (expr->state == CMD)
	{
		if (theres_a_need_to_redir(expressions, params->i))
		{
			while (!last_in(expressions, params->i))
			{
				params->input_fd = read_fd(file(expressions, params->i + 2));
				params->i += 2;
			}
			set_pipe_channels(expressions, params);
			execute_cmd(expr);
		}
		else
		{
			params->i += times_in(expressions, params->i);
			set_pipe_channels(expressions, params);
			execute_cmd(expr);
		}
	}
}

static void	run_expressions(t_vec *expressions, t_executer *params)
{
	t_expression	*expr;

	close(params->pipe_fd[WRITE_END]);
	if (params->input_fd != STDIN_FILENO)
		close(params->input_fd);
	while (params->i < expressions->len)
	{
		expr = expressions->buf[params->i];
		if (expr->state == PIPED)
		{
			params->i += 1;
			params->input_fd = params->pipe_fd[READ_END];
			executer(expressions, params);
			break ;
		}
		else if ((expr->state == OUT || expr->state == APPEND)
			&& last_out_append(expressions, params->i))
		{
			params->pos_file = get_pos_fd(expressions, params->i);
			redir_out_append(params->pipe_fd[READ_END],
				params->new_files[params->pos_file]);
		}
		params->i += 1;
	}
}

int	executer(t_vec *expressions, t_executer *params)
{
	t_expression	*expr;

	if (pipe(params->pipe_fd) < 0)
		exit(EXIT_FAILURE);
	if (fork() == 0)
		child_process(expressions, params);
	else
	{
		wait(NULL);
		if (params->i + 1 < expressions->len)
			run_expressions(expressions, params);
		else
			close_file_descriptors(params);
		if (params->i >= expressions->len)
			params->i = 0;
	}
	return (0);
}
