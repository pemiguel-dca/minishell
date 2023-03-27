/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:31:36 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/27 13:19:47 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

size_t	real_value(t_expression *expr, t_vec *env, size_t i, t_states prev_state)
{
	size_t	pos;
	char	*find;
	t_vec	*args;
	void	*temp;

	args = &expr->args;
	find = ft_strdup(expr->args.buf[i]);
	pos = pos_env_var(env, find + 1);
	if (is_expand_export(find))//name=value
	{
		vec_push(&expr->args, ft_strdup("export"));
		temp = expr->args.buf[0];
		expr->args.buf[0] = expr->args.buf[1];
		expr->args.buf[1] = temp;
		//ft_swap(expr->args.buf[0], expr->args.buf[1]);
	}
	else if (is_last_status(find))//$?
	{
		free(expr->args.buf[i]);
		expr->args.buf[i] = ft_itoa(g_signals.exit_status);
	}
	else if (is_ambiguous_redir(prev_state, pos))//ls > $ola, $ola has no value
	{
		printf("%s: ambiguous redirect\n", find);
		free(find);
		return (1);
	}
	else if ((pos >= 0 && (!is_expand_export(find) && prev_state != DELIMITER))//expand to their value
			|| is_home(find))
	{
		if (is_home(find))//~
		{
			free(expr->args.buf[i]);
			expr->args.buf[i] = ft_strdup(get_var_value(env->buf[pos_env_var(env, "HOME")]));
		}
		else
		{
			free(expr->args.buf[i]);
			expr->args.buf[i] = ft_strdup(get_var_value(env->buf[pos]));
		}
	}
	else if (prev_state != DELIMITER)//if not there, delete args, example: "ls $eadadaea", output sera 'ls' normal
		vec_del(&args, i);
	free(find);
	return (0);
}

size_t	change_value(t_expression *expr, t_vec *env)
{
	size_t			i;
	size_t			errors;
	static t_states	prev_state = DEFAULT;

	i = 0;
	errors = 0;
	while (i < expr->args.len)
	{
		if (as_dollar_sign(expr->args.buf[i])
			|| (is_expand_export(expr->args.buf[i]) && expr->args.len == 1)
			|| is_home(expr->args.buf[i]))
			errors = real_value(expr, env, i, prev_state);
			if (is_expand_export(expr->args.buf[i]))
				break ;
		prev_state = expr->state;
		i += 1;
	}
	return (errors);
}

size_t	expander(t_vec *expressions, t_vec *env)
{
	size_t			i;
	size_t			errors;
	t_expression	*expr;

	i = 0;
	errors = 0;
	while (i < expressions->len)
	{
		expr = expressions->buf[i];
		errors = change_value(expr, env);
		i += 1;
	}
	return (errors);
}
