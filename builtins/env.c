/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:09:47 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/19 18:09:22 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	_env(t_expression *expr, t_vec *env)
{
	size_t	i;

	i = 0;
	if (expr->args.len > 1)
	{
		printf("env: no adicional arguments allowed \n");
		exit (EXIT_FAILURE);
	}
	while (i < env->len)
	{
		printf("%s\n", (char *)env->buf[i]);
		i += 1;
	}
	exit (EXIT_SUCCESS);
}
