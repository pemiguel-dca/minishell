/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:34:26 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/29 17:07:55 by pemiguel         ###   ########.fr       */
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

	delims = malloc((count_delims(expressions) + 1) * sizeof(char*));
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

int	heredoc_on(char *line, t_vec *expressions)
{
	static size_t	finish = 0;
	char	**delims;

	delims = get_delimiters(expressions);
	if (ft_strncmp(line, delims[finish], ft_strlen(line) - 1) == 0)
		finish += 1;
	else
		finish = 0;
	if (finish == count_delims(expressions))
	{
		finish = 0;
		free_delims(delims);
		return (1);
	}
	return (0);
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

int	delete_adicional_delims(int heredoc_fd, t_vec *expressions, size_t total_lines)
{
	int		new_fd;
	size_t	i;
	size_t	lines_to_delete;
	char	*line;

	lines_to_delete = count_delims(expressions);
	i = 0;
	new_fd = open("new.tmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	while (i < total_lines - lines_to_delete)
	{
		line = get_next_line(dup(heredoc_fd));
		write(new_fd, line, ft_strlen(line));
		i += 1;
	}
	write(new_fd, 0, 1);
	new_fd = open("new.tmp", O_RDONLY);
	return (new_fd);
}

void	do_heredoc(t_vec *expressions, t_executer *params)
{
	char	*line;
	size_t	done;
	size_t	lines_in_file;

	done = 0;
	lines_in_file = 1;
	while (true)
	{
		//TODO: Handle crtlD while in heredoc
		line = get_next_line(params->input_fd);
		done = heredoc_on(line, expressions);
		if (done)
		{
			free(line);
			break ;
		}

		if (count_delims(expressions) == 1)
			write(params->heredoc_fd, line, ft_strlen(line));
		lines_in_file += 1;
		free(line);
	}
	params->heredoc_fd = open("heredoc.tmp", O_RDONLY | 0644);
	//if (count_delims(expressions) > 1 && lines_in_file > count_delims(expressions))
		//params->heredoc_fd = delete_adicional_delims(dup(params->heredoc_fd), expressions, lines_in_file);
	params->i += skip_delims(expressions);
	params->input_fd = params->heredoc_fd;
}
