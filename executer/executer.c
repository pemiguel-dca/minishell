/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:11:40 by pemiguel          #+#    #+#             */
/*   Updated: 2023/04/13 18:24:43 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static void	redir_input(t_vec *expressions, t_executer *params)
{
	static size_t	times = 0;

	while (times < count_delims(expressions))
	{
		params->heredoc_fd = open("heredoc.tmp", O_CREAT
				| O_TRUNC | O_RDWR, 0644);
		times += do_heredoc(expressions, params);
	}
	if (theres_a_need_to_redir(expressions, params->i))
	{
		while (!last_in(expressions, params->i))
		{
			params->input_fd = read_fd(file(expressions, params->i + 2));
			params->i += 2;
		}
	}
	else
		params->i += times_in(expressions, params->i);
}

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

static void	child_process(t_vec *expressions, t_executer *params, t_vec *env)
{
	t_expression	*expr;
	char			*path;

	expr = expressions->buf[params->i];
	if (expr->state == CMD)
	{
		redir_input(expressions, params);
		path = bin_path(expr, env);
		if (path)
		{
			set_pipe_channels(expressions, params);
			execute_cmd(expr, env, path);
		}
		else if (!is_parent_builtin(expr->args.buf[0]))
		{
			printf("%s: command not found\n", (char *)expr->args.buf[0]);
			exit(127);
		}
	}
	else if (expr->state == DELIMITER)
		redir_input(expressions, params);
	exit(EXIT_SUCCESS);
}

static void	run_expressions(t_vec *expressions, t_executer *params, t_vec *env)
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
			executer(expressions, params, env);
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

// TODO: solve random lole shit exit status :D
int	executer(t_vec *expressions, t_executer *params, t_vec *env)
{
	t_expression	*expr;

	if (pipe(params->pipe_fd) < 0)
		exit(EXIT_FAILURE);
	if (fork() == 0)
	{
		g_signals.is_in_child = true;
		child_process(expressions, params, env);
	}
	else
	{
		waitpid(-1, (int *)&g_signals.exit_status, 0);
		g_signals.is_in_child = false;
		if (!WTERMSIG(g_signals.exit_status))
			g_signals.exit_status = WEXITSTATUS(g_signals.exit_status);
		printf("%d\n", 130 >> 8);
		expr = expressions->buf[params->i];
		if (is_parent_builtin(expr->args.buf[0])
			&& expressions->len == 1)
			execute_parent_builtin(expr, env, params);
		else if (params->i + 1 < expressions->len)
			run_expressions(expressions, params, env);
		else
			close_file_descriptors(params);
	}
	return (0);
}
