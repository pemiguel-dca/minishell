/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:31:36 by pemiguel          #+#    #+#             */
/*   Updated: 2023/04/03 15:38:12 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

size_t	real_value(t_expression *expr, t_vec *env, size_t i, t_states prev_state)
{
	size_t		pos;
	t_vec		*args;
	char		*find;
	void		*temp;

	find = ft_strdup(expr->args.buf[i]);
	pos = pos_env_var(env, find + 1);
	args = &expr->args;
	if (is_expand_export(find))//name=value
	{
		//TODO: do with multiple examples
		vec_push(&expr->args, ft_strdup("export"));
		temp = expr->args.buf[0];
		expr->args.buf[0] = expr->args.buf[1];
		expr->args.buf[1] = temp;
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
	else if ((pos != - 1 && (!is_expand_export(find) && prev_state != DELIMITER))//expand to their value
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
	else if (prev_state != DELIMITER)
		vec_del(&args, i);
	free(find);
	return (0);
}

size_t	change_value(t_expression *expr, t_vec *env)
{
	size_t			i;
	size_t			errors;
	size_t			initial_len;
	static t_states	prev_state = DEFAULT;

	i = 0;
	errors = 0;
	initial_len = expr->args.len;
	while (i < initial_len)
	{
		if (as_dollar_sign(expr->args.buf[i])
			|| (is_expand_export(expr->args.buf[i]))
			|| is_home(expr->args.buf[i]))
			errors = real_value(expr, env, i, prev_state);
			if (expr->args.len == 0)//|| (expr->args.buf[i] && is_expand_export(expr->args.buf[i])))
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
