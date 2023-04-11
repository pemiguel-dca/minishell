/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:31:36 by pemiguel          #+#    #+#             */
/*   Updated: 2023/04/11 22:14:06 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void add_export(t_expression *expr)
{
	void	*temp;

	vec_push(&expr->args, ft_strdup("export"));
	temp = expr->args.buf[0];
	expr->args.buf[0] = expr->args.buf[expr->args.len - 1];
	expr->args.buf[expr->args.len - 1] = temp;
}

size_t	real_value(t_expression *expr, t_vec *env, size_t i, t_states prev_state)
{
	size_t		pos;
	char		*find;
	void		*temp;

	find = ft_strdup(expr->args.buf[i]);
	pos = pos_env_var(env, find + 1);
	if (is_last_status(find))
	{
		free(expr->args.buf[i]);
		expr->args.buf[i] = ft_itoa(g_signals.exit_status);
	}
	else if (is_ambiguous_redir(prev_state, pos))
	{
		printf("%s: ambiguous redirect\n", find);
		free(find);
		return (1);
	}
	else if (is_home(find))
	{
			free(expr->args.buf[i]);
			expr->args.buf[i] = ft_strdup(get_var_value(env->buf[pos_env_var(env, "HOME")]));
	}
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
			|| is_home(expr->args.buf[i]))
			errors = real_value(expr, env, i, prev_state);
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
		if (is_expand_export(expr))
			add_export(expr);
		else
			errors = change_value(expr, env);
		i += 1;
	}
	return (errors);
}
