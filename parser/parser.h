/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:16:20 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/18 16:06:46 by pemiguel         ###   ########.fr       */
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

inline static t_states	operator_type(char *op)
{
	if (ft_strcmp(op, LIT_PIPE) == 0)
		return (PIPED);
	else if (ft_strcmp(op, LIT_REDIR_APPEND) == 0)
		return (APPEND);
	else if (ft_strcmp(op, LIT_REDIR_DELIMITER) == 0)
		return (DELIMITER);
	else if (ft_strcmp(op, LIT_REDIR_OUT) == 0)
		return (OUT);
	else if (ft_strcmp(op, LIT_REDIR_IN) == 0)
		return (IN);
	assert(0);
}

/*parser.c*/
static inline bool is_operator(char *token)
{
	return (ft_strcmp(token, LIT_PIPE) == 0 || ft_strcmp(token, LIT_REDIR_APPEND) == 0
		|| ft_strcmp(token, LIT_REDIR_DELIMITER) == 0 || ft_strcmp(token, LIT_REDIR_IN) == 0
		|| ft_strcmp(token, LIT_REDIR_OUT) == 0);
}

t_vec			parse(const t_vec *tokens);
t_vec			dumb_shit(t_vec *expressions);
int				check_errors_parser(t_vec *expressions);

/*parser_utils.c*/
int				adicional_args(t_vec *expressions);
t_states		get_state(const t_vec *args, t_states prev_state);
t_vec			cmd_args(t_expression *expr);
t_vec			extra_args(t_expression *expr, t_vec *args);
t_expression	*get_new_expression(t_vec *expressions, size_t *i);
t_expression	*get_file_only(t_expression *expr);

#endif
