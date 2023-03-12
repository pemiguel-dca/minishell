/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:03:11 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/12 17:12:01 by pemiguel         ###   ########.fr       */
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

int	last_out_append(t_vec *expressions, size_t *i)
{
	size_t			j;
	t_expression	*expr;
	
	j = *i + 1;
	expr = expressions->buf[j];
	while (j < expressions->len && expr->state != PIPED)
	{
		expr = expressions->buf[j];
		if (expr->state == OUT || expr->state == APPEND)
			return (0);
		j += 1;
	}
	return (1);
}

int	last_in(t_vec *expressions, size_t *i)
{
	size_t			j;
	t_expression	*expr;
	
	j = *i + 1;
	expr = expressions->buf[j];
	while (j < expressions->len && expr->state != PIPED)
	{
		expr = expressions->buf[j];
		if (expr->state == IN)
			return (0);
		j += 1;
	}
	return (1);
}

size_t get_pos_fd(t_vec *expressions, size_t *i)
{
	size_t			j;
	size_t			pos_fd;
	t_expression	*expr;
	
	j = 0;
	pos_fd = 0;
	expr = expressions->buf[j];
	while (j < *i + 1)
	{
		expr = expressions->buf[j];
		if (expr->state == OUT || expr->state == APPEND)
			pos_fd++;
		j += 1;
	}
	return (pos_fd - 1);
}

static void	replace_in_out(t_vec *expressions, size_t i, int *pipe_fd, int *input_fd, int *output_fd)
{
	if (i + 1 < expressions->len)
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

static void	execute_cmd(t_expression *expr)
{
	char	*path;

	if (is_valid_args(*expr))
	{
		path = get_cmd_path(*expr);
		execve(path, (char **)expr->args.buf, NULL);
	}
	else
	{
		// TODO: mesma coisa (fazer panic)
		fprintf(stderr, "Command not found: %s\n", (char *)expr->args.buf[0]);
		exit(EXIT_FAILURE);
	}
}

int spawn(t_vec *expressions, int input_fd, int output_fd)
{
	int 			pipe_fd[2];
	char 			*path;
	static size_t	i = 0;
	t_expression	*expr;
	static int		*new_file_descriptors; //tem de ser estático porque se tiveres pipes por exemplo ele vai ao parent 2 vezes
	size_t			pos_fd;

	if (i >= expressions->len) //reset ao i para a próxima vez, talvez uma estrutura faria mais sentido talvez, manda msg quando vires para discutirmos isto
		i = 0;
	if (pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	if (fork() == 0)
	{
		// Child process
		//Algo está errado, às vezes o comando é executado mas dá o msg de erro de longe a longe.
		expr = expressions->buf[i];
		replace_in_out(expressions, i, pipe_fd, &input_fd, &output_fd);
		if (expr->state == CMD)
			execute_cmd(expr);
	}
	else
	{
		// Parent process
		if (i + 1 < expressions->len)
		{
			close(pipe_fd[WRITE_END]);
			if (input_fd != STDIN_FILENO)
				close(input_fd);
			if (files_to_be_created(expressions) && i == 0)
				new_file_descriptors = create_files(expressions);
			while (i < expressions->len)
			{
				expr = expressions->buf[i];
				if (expr->state == PIPED)
				{
					i += 1;
					spawn(expressions, pipe_fd[READ_END], output_fd);
					break ;
				}
				if ((expr->state == OUT || expr->state == APPEND)
					&& last_out_append(expressions, &i))
				{
					pos_fd = get_pos_fd(expressions, &i);
					redir_out_append(pipe_fd[READ_END], new_file_descriptors[pos_fd]);
				}
				if (expr->state == IN)//&& last_in(expressions, &i))
				{
					printf("HEY: %ld", i);
					/*
					expr = expressions->buf[++i];
					printf("ola");
					//redir_in(pipe_fd[READ_END], (char *)expr->args.buf[0]);
					*/
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
		wait(NULL);
	}
	return (0);
}

