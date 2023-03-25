/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:28:20 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/24 21:41:05 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../builtins/builtins.h"
# include "../parser/parser.h"
# include "../env_vars/env.h"
# include "../libft/libft.h"
# include "../vector.h"

static inline int	is_expand_export(char *arg)
{
	size_t	i;
	int		equal;

	i = 1;
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

static inline int	as_dollar_sign(char *arg)
{
	if (arg[0] == '$')
		return (1);
	return (0);
}

static inline int	is_last_status(char *arg)
{
	if (ft_strcmp("$?", arg) == 0)
		return (1);
	return (0);
}

int	expander(t_vec *expressions, t_vec *env, t_executer *params);

#endif