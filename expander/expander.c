/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:31:36 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/24 21:49:13 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/*Change expressions to the actual value of env var*/
/*Especial case: when '<<' the next value never changes*/

int	real_value(t_expression **expr, t_vec *env, size_t i, t_executer *params)
{
	size_t			pos;
	char			*find;
	t_expression	*t_e;
	t_vec			*args;
	
	t_e = *expr;
	args = &t_e->args; 
	find = ft_strdup(t_e->args.buf[0]);
	pos = pos_env_var(env, find + 1);
	if (is_expand_export(find))
	{
		vec_del(&args, i);
		vec_push(&t_e->args, ft_strdup("export"));
		vec_push(&t_e->args, ft_strdup(find));
	}
	else if (pos == -1 && is_last_status(find))
		vec_del(&args, i);
	if (is_last_status(find))
	{
		vec_push(&t_e->args, ft_strdup("echo"));
		//Deal with previous status
		//vec_push(&t_e->args, ft_itoa(params->exit_status));
	}
	else if (!is_expand_export(find))
		((t_expression *)*expr)->args.buf[i] = ft_strdup(get_var_value(env->buf[pos]));
	free(find);
	return (0);
}

int	change_value(t_expression *expr, t_vec *env, t_executer *params)
{
	size_t			i;

	i = 0;
	while (i < expr->args.len)
	{
		if (as_dollar_sign(expr->args.buf[i]) || is_expand_export(expr->args.buf[i]))
			real_value(&expr, env, i, params);
		i += 1;
	}
	return (0);
}

int	expander(t_vec *expressions, t_vec *env, t_executer *params)
{
	size_t			i;
	t_expression	*expr;

	i = 0;
	while (i < expressions->len)
	{
		expr = expressions->buf[i];
		change_value(expr, env, params);
		i += 1;
	}
	return (0);
}