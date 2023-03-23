/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:16:20 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/23 16:50:46 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <assert.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../globals.h"
# include "../vector.h"

typedef enum s_states
{
	ENV,
	FL,
	CMD,
	PIPED,
	APPEND,
	DELIMITER,
	OUT,
	IN,
	DEFAULT
}	t_states;

typedef struct expression
{
	t_vec			args;
	t_states		state;
}	t_expression;

typedef struct parser
{
	size_t		i;
	const t_vec	*tokens;
}	t_parser;

inline static char	*p_curr(const t_parser *parser, size_t i)
{
	if (i < parser->tokens->len) {
		return (parser->tokens->buf[i]);
	} else {
		return (NULL);
	}
}

inline static t_states	operator_type(const char *op)
{
	if (ft_strcmp((char *)op, LIT_PIPE) == 0)
		return (PIPED);
	else if (ft_strcmp((char *)op, LIT_REDIR_APPEND) == 0)
		return (APPEND);
	else if (ft_strcmp((char *)op, LIT_REDIR_DEL) == 0)
		return (DELIMITER);
	else if (ft_strcmp((char *)op, LIT_REDIR_OUT) == 0)
		return (OUT);
	else if (ft_strcmp((char *)op, LIT_REDIR_IN) == 0)
		return (IN);
	assert(0);
}

inline static bool	is_operator(const char *token)
{
	if (!token)
		return (false);
	return (ft_strcmp((char *)token, LIT_PIPE) == 0
		|| ft_strcmp((char *)token, LIT_REDIR_APPEND) == 0
		|| ft_strcmp((char *)token, LIT_REDIR_DEL) == 0
		|| ft_strcmp((char *)token, LIT_REDIR_IN) == 0
		|| ft_strcmp((char *)token, LIT_REDIR_OUT) == 0);
}

/*Divide the tokens in expressions*/
t_vec			construct_expressions(const t_vec *tokens);
/*Check if expressions need to be refatored (any adicional arguments)*/
t_vec			parse(const t_vec *tokens);
/*Checks for any parse errors*/
int				check_errors_parser(t_vec *expressions);
/*Get the state of token*/
t_states		get_state(const t_vec *args, t_states prev_state);

#endif
