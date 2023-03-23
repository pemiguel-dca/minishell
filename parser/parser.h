/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:16:20 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/22 22:16:11 by pemiguel         ###   ########.fr       */
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

// TODO: execute relative files
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

/*Gets the operator state*/
inline static t_states	operator_type(char *op)
{
	if (ft_strcmp(op, LIT_PIPE) == 0)
		return (PIPED);
	else if (ft_strcmp(op, LIT_REDIR_APPEND) == 0)
		return (APPEND);
	else if (ft_strcmp(op, LIT_REDIR_DEL) == 0)
		return (DELIMITER);
	else if (ft_strcmp(op, LIT_REDIR_OUT) == 0)
		return (OUT);
	else if (ft_strcmp(op, LIT_REDIR_IN) == 0)
		return (IN);
	assert(0);
}

/*parser.c*/

/*Checks if token is an operator*/
static inline bool	is_operator(char *token)
{
	return (ft_strcmp(token, LIT_PIPE) == 0
		|| ft_strcmp(token, LIT_REDIR_APPEND) == 0
		|| ft_strcmp(token, LIT_REDIR_DEL) == 0
		|| ft_strcmp(token, LIT_REDIR_IN) == 0
		|| ft_strcmp(token, LIT_REDIR_OUT) == 0);
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
