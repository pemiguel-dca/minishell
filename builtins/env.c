/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:09:47 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/22 22:18:53 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

size_t	_env(t_expression *expr, t_vec *env)
{
	size_t	i;

	i = 0;
	if (expr->args.len > 1)
	{
		printf("env: no adicional arguments allowed \n");
		return (1);
	}
	while (i < env->len)
	{
		printf("%s\n", (char *)env->buf[i]);
		i += 1;
	}
	return (0);
}
