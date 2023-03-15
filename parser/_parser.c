/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:16:01 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/13 14:38:21 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "parser.h"

static t_expression	*get_next(t_parser *parser)
{
	t_expression	*expr;
	t_vec			args;
	t_states		prev_state;//para verificar se e ficheiro, nao pode ser estatico do outro lado, pois se tivermos um erro deste genero '>', o proximo estado vai ser sempre FL

	args = vec_new();
	prev_state = 0;
	while (parser->i < parser->tokens->len)
	{
		vec_push(&args, (char *)parser->tokens->buf[parser->i]);
		prev_state = expr->state;
		if ((parser->tokens->len != parser->i + 1 && is_operator((char *)parser->tokens->buf[parser->i + 1]))
			|| is_operator((char *)parser->tokens->buf[parser->i]) || parser->tokens->len == parser->i + 1)
		{
			expr = malloc(sizeof(t_expression));
			*expr = (t_expression){.args = args, .state = get_state(&args, prev_state)};
			parser->i += 1;
			return (expr);
		}
		parser->i += 1;
	}
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

t_vec	dumb_shit(t_vec *expressions)
{
	size_t			i;
	t_expression	*expr;
	t_expression	*new_expr;
	t_vec			new;

	new = vec_new();
	i = 0;
	while (i < expressions->len)
	{
		expr = expressions->buf[i];
		if (expr->state == CMD && adicional_args(expressions))
		{
			new_expr = get_new_expression(expressions, &i);
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

/*Since we don't have to deal with unclosed quotes I think this is the only case that parser will have any errors*/
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
			printf("syntax error near unexpected token `newline'\n");
			return (EXIT_FAILURE);
		}
		i += 1;
	}
	return (EXIT_SUCCESS);
}
