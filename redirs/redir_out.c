/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:24:56 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/21 17:41:14 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirs.h"

void	redir_out_append(int read_fd, int fd)
{
	char	*line;

	while (true)
	{
		line = get_next_line(read_fd);
		if (line)
		{
			write(fd, line, ft_strlen(line));
			free(line);
		}
		else
			break ;
	}
	close(fd);
}

int	last_out_append(t_vec *expressions, size_t i)
{
	size_t			j;
	t_expression	*expr;

	j = i + 1;
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

size_t	get_pos_fd(t_vec *expressions, size_t i)
{
	size_t			j;
	size_t			pos_fd;
	t_expression	*expr;

	j = 0;
	pos_fd = 0;
	expr = expressions->buf[j];
	while (j < i + 1)
	{
		expr = expressions->buf[j];
		if (expr->state == OUT || expr->state == APPEND)
			pos_fd++;
		j += 1;
	}
	return (pos_fd - 1);
}
