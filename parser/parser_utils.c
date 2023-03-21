/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:51:13 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/21 17:25:27 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	adicional_args(t_vec *expressions)
{
	size_t			i;
	t_expression	*expr;

	i = 0;
	while (i < expressions->len)
	{
		expr = expressions->buf[i];
		if (expr->state == FL && expr->args.len > 1)
			return (1);
		i += 1;
	}
	return (0);
}

t_vec	cmd_args(t_expression *expr)
{
	size_t	j;
	t_vec	args;

	j = 0;
	args = vec_new();
	while (j < expr->args.len)
	{
		vec_push(&args, (char *)expr->args.buf[j]);
		j += 1;
	}
	return (args);
}

t_vec	extra_args(t_expression *expr, t_vec *args)
{
	size_t	j;

	j = 1;
	while (j < expr->args.len)
	{
		vec_push(args, (char *)expr->args.buf[j]);
		j += 1;
	}
	return (*args);
}

t_expression	*get_new_expression(t_vec *expressions, size_t i)
{
	size_t			j;
	t_expression	*expr;
	t_expression	*new_expression;
	t_vec			args;

	args = vec_new();
	j = i;
	expr = expressions->buf[i];
	new_expression = malloc(sizeof(t_expression));
	while (j < expressions->len && expr->state != PIPED)
	{
		expr = expressions->buf[j];
		if (expr->state == CMD)
			args = cmd_args(expr);
		if (expr->state == FL && expr->args.len > 1)
			args = extra_args(expr, &args);
		j += 1;
	}
	*new_expression = (t_expression){.args = args, .state = CMD};
	return (new_expression);
}

t_expression	*get_file_only(t_expression *expr)
{
	t_expression	*new_expression;
	t_vec			args;

	args = vec_new();
	new_expression = malloc(sizeof(t_expression));
	vec_push(&args, (char *)expr->args.buf[0]);
	*new_expression = (t_expression){.args = args, .state = FL};
	return (new_expression);
}
