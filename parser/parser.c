/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:16:01 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/20 16:20:07 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "parser.h"

t_states	get_state(const t_vec *args, t_states prev_state)
{
	t_states	state;

	state = DEFAULT;
	if (prev_state > 3 && prev_state < 8)
		state = FL;
	if (((args->len == 1 && !is_operator(args->buf[0])
				&& !ft_strchr(args->buf[0], '=')) || args->len > 1)
		&& state == DEFAULT)
		state = CMD;
	else if (args->len == 1 && is_operator(args->buf[0]))
		state = operator_type(args->buf[0]);
	else if (args->len == 1 && ft_strchr(args->buf[0], '='))
		state = ENV;
	return (state);
}

static t_expression	*get_next(t_parser *parser)
{
	t_expression	*expr;
	t_vec			args;
	t_states		prev_state;

	expr = NULL;
	args = vec_new();
	prev_state = DEFAULT;
	while (parser->i < parser->tokens->len)
	{
		vec_push(&args, (char *)parser->tokens->buf[parser->i]);
		if (expr)
			prev_state = expr->state;
		if ((parser->tokens->len != parser->i + 1
				&& is_operator((char *)parser->tokens->buf[parser->i + 1]))
			|| is_operator((char *)parser->tokens->buf[parser->i])
			|| parser->tokens->len == parser->i + 1)
		{
			expr = malloc(sizeof(t_expression));
			*expr = (t_expression){.args = args,
				.state = get_state(&args, prev_state)};
			parser->i += 1;
			return (expr);
		}
		parser->i += 1;
	}
	return (NULL);
}

t_vec	construct_expressions(const t_vec *tokens)
{
	t_vec			expressions;
	t_parser		parser;
	t_expression	*expr;

	expressions = vec_new();
	parser = (t_parser){.i = 0, .tokens = tokens};
	while (true)
	{
		expr = get_next(&parser);
		if (expr)
			vec_push(&expressions, expr);
		else
			break ;
	}
	return (expressions);
}

t_vec	parse(t_vec expressions)
{
	size_t			i;
	t_expression	*expr;
	t_expression	*new_expr;
	t_vec			new;

	new = vec_new();
	i = 0;
	while (i < expressions.len)
	{
		expr = expressions.buf[i];
		if (expr->state == CMD && adicional_args(&expressions))
		{
			new_expr = get_new_expression(&expressions, &i);
			vec_push(&new, new_expr);
		}
		else if (expr->state == FL && expr->args.len > 1)
		{
			new_expr = get_file_only(expr);
			vec_push(&new, new_expr);
		}
		else
			vec_push(&new, expr);
		i += 1;
	}
	return (new);
}

int	check_errors_parser(t_vec *expressions)
{
	size_t			i;
	t_expression	*expr;

	i = 0;
	while (i < expressions->len)
	{
		expr = expressions->buf[i];
		if (expr->state > 3 && i + 1 == expressions->len)
		{
			printf("syntax error near unexpected token 'newline'\n");
			return (EXIT_FAILURE);
		}
		i += 1;
	}
	return (EXIT_SUCCESS);
}
