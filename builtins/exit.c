/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:56:41 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/23 13:06:27 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

size_t	_exit(t_expression *expr, t_executer *params)
{
	size_t	i;

	i = 0;
	if (expr->args.len == 1)
		params->exit_status = 0;
	else
	{
		if (expr->args.len > 2)
		{
			printf("exit: too many arguments\n");
			params->exit_status = 127;
			return (1);
		}
		else
			params->exit_status = ft_atoi((char *)expr->args.buf[1]);
	}
	return (0);
}
