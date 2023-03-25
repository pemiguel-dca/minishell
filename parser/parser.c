/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:16:01 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/25 15:47:31 by pemiguel         ###   ########.fr       */
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
		state = CMD;
	return (state);
}

static t_expression	*get_next(t_parser *parser)
{
	t_vec				args;
	static t_states		prev_state = DEFAULT;

	args = vec_new();
	while (parser->i < parser->tokens->len)
	{
		vec_push(&args, ft_strdup(p_curr(parser, parser->i)));

		if (
			// if there's a next token and it is an operator
			is_operator(p_curr(parser, parser->i + 1))
			// or if this token is an operator
			|| is_operator(p_curr(parser, parser->i))
			// or if there's no more tokens
			|| parser->tokens->len == parser->i + 1
		) {
			t_expression	*expr = malloc(sizeof(t_expression));

			*expr = (t_expression){.args = args,
				.state = get_state(&args, prev_state)};

			prev_state = expr->state;

			parser->i += 1;

			return (expr);
		}

		parser->i += 1;
	}
	vec_free(&args);
	return (NULL);
}

t_vec	parse(const t_vec *tokens)
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

int	check_errors_parser(t_vec *expressions)
{
	size_t			i;
	t_expression	*expr;

	i = 0;
	while (i < expressions->len)
	{
		expr = expressions->buf[i];
		if (expr->state > 2 && i + 1 == expressions->len)
		{
			if (expr->state == PIPED)
				printf("close your pipes!\n");
			else
				printf("syntax error near unexpected token 'newline'\n");
			return (EXIT_FAILURE);
		}
		i += 1;
	}
	return (EXIT_SUCCESS);
}
