/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:16:20 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/15 19:21:49 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <assert.h>
# include "../libft/libft.h"
# include "../vector.h"
# include "../globals.h"

typedef enum operator
{
	APPEND,
	DELIMITER,
	OUT,
	IN
}	t_operator;

typedef struct compound
{
	t_operator	type;
	const char	*to;
}	t_compound;

typedef union expression_union
{
	const char	*literal;
	t_compound	compound;
}	t_expression_union;

typedef struct expression
{
	short				union_type;
	t_expression_union	uni;
}	t_expression;

typedef struct parser
{
	size_t		i;
	const t_vec	*tokens;
}	t_parser;

t_vec	parse(const t_vec *tokens);

inline static bool	is_redir(const char *token)
{
	return (ft_strcmp((char *)token, LIT_REDIR_APPEND) == 0
		|| ft_strcmp((char *)token, LIT_REDIR_DELIMITER) == 0
		|| ft_strcmp((char *)token, LIT_REDIR_IN) == 0
		|| ft_strcmp((char *)token, LIT_REDIR_OUT) == 0);
}

inline static t_operator	get_type(const char *s)
{
	if (ft_strcmp((char *)s, LIT_REDIR_APPEND) == 0)
		return (APPEND);
	else if (ft_strcmp((char *)s, LIT_REDIR_DELIMITER) == 0)
		return (DELIMITER);
	else if (ft_strcmp((char *)s, LIT_REDIR_OUT) == 0)
		return (OUT);
	else if (ft_strcmp((char *)s, LIT_REDIR_IN) == 0)
		return (IN);
	assert(0);
}

#endif
