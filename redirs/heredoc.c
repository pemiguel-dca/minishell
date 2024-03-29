/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:34:26 by pemiguel          #+#    #+#             */
/*   Updated: 2023/04/13 17:40:25 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirs.h"

char	**get_delimiters(t_vec *expressions)
{
	t_expression	*expr;
	t_states		prev_state;
	size_t			i;
	size_t			j;
	char			**delims;

	delims = malloc((count_delims(expressions) + 1) * sizeof(char *));
	i = 0;
	j = 0;
	prev_state = DEFAULT;
	while (i < expressions->len)
	{
		expr = expressions->buf[i];
		if (prev_state == DELIMITER)
		{
			delims[j] = ft_strdup(expr->args.buf[0]);
			j += 1;
		}
		prev_state = expr->state;
		i += 1;
	}
	delims[j] = 0;
	return (delims);
}

size_t	count_delims(t_vec *expressions)
{
	size_t			i;
	size_t			delims;
	t_expression	*expr;

	i = 0;
	delims = 0;
	while (i < expressions->len)
	{
		expr = expressions->buf[i];
		if (expr->state == DELIMITER)
			delims += 1;
		i += 1;
	}
	return (delims);
}

size_t	skip_delims(t_vec *expressions)
{
	t_expression	*expr;
	size_t			count_delims;
	size_t			i;

	count_delims = 0;
	i = 0;
	while (i < expressions->len)
	{
		expr = expressions->buf[i];
		if (expr->state == DELIMITER)
			count_delims += 1;
		i += 1;
	}
	return (count_delims * 2);
}

bool	heredoc_on(char *line, t_executer *params)
{
	static size_t	finish = 0;

	if (!line)
		return (true);
	else if (ft_strcmp(line, "\n") == 0)
		return (false);
	else if (ft_strncmp(line, params->delims[finish], ft_strlen(line) - 1) == 0)
	{
		finish += 1;
		return (true);
	}
	return (false);
}

size_t	do_heredoc(t_vec *expressions, t_executer *params)
{
	char	*rl;
	char	*line;
	size_t	done;

	done = 0;
	while (true)
	{
		rl = readline("> ");
		line = ft_strjoin(rl, "\n");
		free(rl);
		done = heredoc_on(line, params);
		if (done)
		{
			free(line);
			break ;
		}
		write(params->heredoc_fd, line, ft_strlen(line));
		free(line);
	}
	params->heredoc_fd = open("heredoc.tmp", O_RDONLY | 0644);
	params->i += skip_delims(expressions);
	params->input_fd = params->heredoc_fd;
	return (1);
}
