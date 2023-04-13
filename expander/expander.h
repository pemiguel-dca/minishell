/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:28:20 by pemiguel          #+#    #+#             */
/*   Updated: 2023/04/13 15:37:43 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../globals.h"
# include "../builtins/builtins.h"
# include "../parser/parser.h"
# include "../env_vars/env.h"
# include "../libft/libft.h"
# include "../vector.h"

extern t_signals	g_signals;

static inline void	get_res(size_t equal, char last, bool *res)
{
	if (equal == 0 || (equal == 1 && last == '='))
		*res = false;
	else
		*res = true;
}

static inline bool	is_expand_export(t_expression *expr)
{
	size_t	i;
	size_t	j;
	int		equal;
	bool	res;

	j = 0;
	while (j < expr->args.len)
	{
		equal = 0;
		i = 0;
		if (ft_isalpha(((char *)expr->args.buf[j])[i]))
		{
			while (((char *)expr->args.buf[j])[i])
			{
				if (((char *)expr->args.buf[j])[i] == '=')
					equal += 1;
				i += 1;
			}
			get_res(equal, ((char *)expr->args.buf[j])[i - 1], &res);
		}
		j += 1;
	}
	return (res);
}

static inline bool	is_home(char *arg)
{
	return (ft_strcmp("~", arg) == 0);
}

static inline bool	is_ambiguous_redir(t_states prev_state, int pos)
{
	return (pos == -1 && (prev_state == APPEND
			|| prev_state == IN
			|| prev_state == OUT));
}

size_t	expander(t_vec *expressions, t_vec *env);

#endif
