/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:34:26 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/27 22:13:23 by pemiguel         ###   ########.fr       */
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
	
	delims = malloc(count_delims(expressions) + 1 * sizeof(char*));
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
	return (delims);
}

int	heredoc_on(char *line, t_vec *expressions)
{
	size_t	finish;
	char	**delims;

	delims = get_delims(expressions);
	finish = 0;
	while (finish < ft_strlen(delims))
	{
		if (ft_strncmp(line, delims[finish], ft_strlen(delims[finish])))
		{
			
		}
		
	}
	return (0);
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
