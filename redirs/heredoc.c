/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:34:26 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/27 18:58:29 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirs.h"

int	heredoc_tmp(int read_fd)
{
	int	heredoc_fd;

	heredoc_fd = create_specific_file("heredoc.tmp", DELIMETER);
	redir_out_append(read_fd, heredoc_fd);
	return (heredoc_fd);
}

int	theres_a_need_to_heredoc(t_vec *expressions, size_t i)
{
	t_expression	*expr;
	size_t			cmd_as_args;
	size_t			no_operator_before;

	cmd_as_args = 0;
	expr = expressions->buf[i];
	no_operator_before = 0;
	while (i < expressions->len && expr->state != PIPED)
	{
		expr = expressions->buf[i];
		if (expr->state == CMD && expr->args.len > 1)
			cmd_as_args = check_cmd_args(expr);
		else if (expr->state == OUT || expr->state == APPEND)
			no_operator_before = 1;
		else if (expr->state == DELIMITER && !cmd_as_args && !no_operator_before)
			return (1);
		i += 1;
	}
	return (0);
}

int	last_heredoc(t_vec *expressions, size_t i)
{
	size_t			j;
	t_expression	*expr;

	j = i + 1;
	expr = expressions->buf[j];
	while (j < expressions->len && expr->state != PIPED)
	{
		expr = expressions->buf[j];
		if (expr->state == DELIMITER)
			return (0);
		j += 1;
	}
	return (1);
}
