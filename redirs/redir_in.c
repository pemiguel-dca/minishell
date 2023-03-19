/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:20:26 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/19 02:24:33 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirs.h"

int	read_fd(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("%s : No such file or directory\n", file_name);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	theres_a_need_to_redir(t_vec *expressions, size_t i)
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
		else if (expr->state == IN && !cmd_as_args && !no_operator_before)
			return (1);
		i += 1;
	}
	return (0);
}

int	times_in(t_vec *expressions, size_t i)
{
	t_expression	*expr;
	size_t			count_in;

	expr = expressions->buf[i];
	count_in = 0;
	while (i < expressions->len && expr->state != PIPED)
	{
		expr = expressions->buf[i];
		if (expr->state == IN)
			count_in++;
		i += 1;
	}
	return (count_in * 2);
}

int	check_cmd_args(t_expression *expr)
{
	size_t	i;

	i = 1;
	while (i < expr->args.len)
	{
		if (!(ft_strchr(expr->args.buf[i], '-')))
			return (1);
		i += 1;
	}
	return (0);
}

int	last_in(t_vec *expressions, size_t i)
{
	size_t			j;
	t_expression	*expr;

	j = i + 1;
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
