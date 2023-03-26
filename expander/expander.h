/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:28:20 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/26 17:05:35 by pemiguel         ###   ########.fr       */
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

static inline int	is_expand_export(char *arg)
{
	size_t	i;
	int		equal;

	i = 0;
	equal = 0;
	if (ft_isalpha(arg[i]))
	{
		while (arg[i])
		{
			if (arg[i] == '=')
				equal += 1;
			i += 1;
		}
		if (equal == 0 || (equal == 1 && arg[i - 1] == '='))
			return (0);
		else
			return (1);
	}
	return (0);
}

static inline bool	as_dollar_sign(char *arg)
{
	return (arg[0] == '$');
}

static inline bool	is_last_status(char *arg)
{
	return (ft_strcmp("$?", arg) == 0);
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
