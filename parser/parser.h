/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:16:20 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/19 02:37:23 by pemiguel         ###   ########.fr       */
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
	IN
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
t_vec			parse(t_vec *expressions);
/*Checks for any parse errors*/
int				check_errors_parser(t_vec *expressions);
/*Get the state of token*/
t_states		get_state(const t_vec *args, t_states prev_state);

/*parser_utils.c*/

/*Checks if cmd as adicional args after any redir*/
int				adicional_args(t_vec *expressions);
/*Gets inicial cmd args*/
t_vec			cmd_args(t_expression *expr);
/*Gets extra arguments of cmd*/
t_vec			extra_args(t_expression *expr, t_vec *args);
/*Gets the new expression with the extra arguments for a specific command*/
t_expression	*get_new_expression(t_vec *expressions, size_t *i);
/*Separates file from other expression*/
t_expression	*get_file_only(t_expression *expr);

#endif
