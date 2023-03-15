/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:10:03 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/03/15 19:44:29 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_vec	*get_next(t_parser *parser)
{
	t_vec	*statement;
	char	*token;

	statement = malloc(sizeof(t_vec));
	*statement = vec_new();
	while (parser->i < parser->tokens->len)
	{
		token = parser->tokens->buf[parser->i];
		if (*token == *LIT_PIPE)
		{
			parser->i += 1;
			break;
		} else {
			t_expression *expr = malloc(sizeof(t_expression));
			if (is_redir(token)) {
				parser->i += 1;
				*expr = (t_expression){
					.union_type = 1,
					.uni = (t_expression_union){
						.compound = (t_compound){
							.type = get_type(token),
							.to = parser->tokens->buf[parser->i]
						}
					}
				};
			} else {
				*expr = (t_expression){
					.union_type = 0,
					.uni = (t_expression_union){
						.literal = token
					}
				};
			}
			vec_push(statement, expr);
		}

		parser->i += 1;
	}
	if (!statement->len)
		return (NULL);
	else
		return (statement);
}

t_vec	parse(const t_vec *tokens)
{
	t_vec			statements;
	t_parser		parser;
	t_vec			*statement;

	statements = vec_new();
	parser = (t_parser){.i = 0, .tokens = tokens};
	while (true)
	{
		statement = get_next(&parser);
		if (statement)
			vec_push(&statements, statement);
		else
			break ;
	}
	return (statements);
}
